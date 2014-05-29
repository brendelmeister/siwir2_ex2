#include "matrixes.h"

static double delta;
static double eps;

int main(int argc, char* argv[])
{
   if (argc != 3 && argc != 4) {
      cerr<<"error: wrong number of arguments"<<endl;
      cout<<"call ./waveguide d e [l] "<<endl;
      cout<<"d: variable for the calculation of the variable coefficient k(x,y) ; e: stopping criterion for the solver"<<endl;
      cout<<"l: number of grid refinement-levels"<<endl;
      exit(EXIT_FAILURE);
   }

   int l=0;
   delta = atof(argv[1]);
   eps = atof(argv[2]);
   if (argc == 4) 
      l = atoi(argv[3]);


   vector<Point> points;
   vector<Face> faces;

   readFromFile("./inputs/unit_circle.txt",&points,&faces);

   vector<Face> finerFaces;

   for (int i=0;i<l;i++)
   {
      finerFaces.clear();
      for (vector<Face>::iterator it = faces.begin() ; it != faces.end(); ++it)
	 refine(&(*it),&points,&finerFaces);

      faces.swap(finerFaces);

      //clear all stored neighbour information
      for (vector<Point>::iterator it = points.begin() ; it != points.end(); ++it)
	 clearNeighbours(&(*it));

      cout << "Refined " << i+1 << " level(s)" <<endl;
   }

   saveK(&points);

   vector<map< int,double> > glob_stiff = get_build_matrix( &points, &faces,"stiffness");
   vector<map< int,double> > glob_mass = get_build_matrix( &points, &faces,"mass");
   save_global_matrix(&glob_stiff,"A.txt");
   save_global_matrix(&glob_mass,"M.txt");

   double lambda, lambda_old;
   vector<double> u (glob_stiff.size(),1.);
   vector<double> f (glob_stiff.size(),0.);
   lambda=1.;

   do {
      lambda_old = lambda;
      matrixVector(&glob_mass,&u,&f);//f=M*u
      //solve A*u=f
      cgsolve( &glob_stiff,&u,&f, eps);

      vectorScalar(&u,1./(euclNorm(&u)));//u=u/norm(u)
      //use f as tmp here;

      matrixVector(&glob_stiff,&u,&f); //lambda=u*A*u/u*M*u
      lambda = vectorVector(&u,&f);
      matrixVector(&glob_mass,&u,&f);
      lambda = lambda/vectorVector(&u,&f);
      //cout<<"Convergence Barrier: "<<fabs((lambda-lambda_old)/lambda_old)<<endl;
      cout<< "Lambda:  " << lambda <<endl;
   } while (fabs((lambda-lambda_old)/lambda_old)>1e-10 );

   cout<<"Final lambda: "<<setprecision(10) << lambda<<endl;
   saveDouble(lambda, "lambda.txt");
   vectorSave(&u, &points,"eigenmode.txt");
   return 0;
}

void add_to_global_matrix(vector<map< int,double> >* glob_matrix,Face element,vector< vector<double> >* my_local_matrix){

   glob_matrix->at(element.vertex0)[element.vertex0]+=my_local_matrix->at(0).at(0);
   glob_matrix->at(element.vertex1)[element.vertex0]+=my_local_matrix->at(1).at(0);
   glob_matrix->at(element.vertex2)[element.vertex0]+=my_local_matrix->at(2).at(0);

   glob_matrix->at(element.vertex0)[element.vertex1]+=my_local_matrix->at(0).at(1);
   glob_matrix->at(element.vertex1)[element.vertex1]+=my_local_matrix->at(1).at(1);
   glob_matrix->at(element.vertex2)[element.vertex1]+=my_local_matrix->at(2).at(1);

   glob_matrix->at(element.vertex0)[element.vertex2]+=my_local_matrix->at(0).at(2);
   glob_matrix->at(element.vertex1)[element.vertex2]+=my_local_matrix->at(1).at(2);
   glob_matrix->at(element.vertex2)[element.vertex2]+=my_local_matrix->at(2).at(2);
}

vector<map< int,double> > create_global_matrix(int n){
   vector<map< int,double> > glob_matrix(n);
   for (int i=0;i<n;++i){
      glob_matrix[i];
   }
   return glob_matrix;
}

vector<map< int,double> > get_build_matrix( vector<Point>* points, vector<Face>* faces,string type){

    ELEMENTS::Triangle my_element;
    vector<map< int,double> > glob_matrix = create_global_matrix(points->size());
    std::vector< std::vector< double > > my_local_matrix;
    std::vector<double> corners(6, 0.0);


    for(unsigned int i=0; i<faces->size();++i){
        // array corners contains the x- and y-coordinates of the
        // triangle corners in the order x0, y0, x1, y1, x2, y2
        corners[0] = points->at(faces->at(i).vertex0).x;
        corners[1] = points->at(faces->at(i).vertex0).y;
        corners[2] = points->at(faces->at(i).vertex1).x;
        corners[3] = points->at(faces->at(i).vertex1).y;
        corners[4] = points->at(faces->at(i).vertex2).x;
        corners[5] = points->at(faces->at(i).vertex2).y;

        // pass the corners to the finite element
        my_element(corners);
        if(type=="stiffness"){
            my_local_matrix = my_element.integrate(grad(v_()) * grad(w_())- func<double>(getKq) * v_()*w_());
        }else if(type=="mass"){
            my_local_matrix = my_element.integrate(v_() * w_());
        }
        add_to_global_matrix(&glob_matrix,faces->at(i),&my_local_matrix);
    }

    return glob_matrix;
}


void save_global_matrix(vector<map< int,double> >* glob_matrix, const char* name)
{ 
   ofstream file; 
   file.open(name, ios::out);
   if(!(file.is_open()))
   { 
      printf(" konnte nicht gespeichert werden\n");
      exit(1);
   }

   map<int,double>::iterator map_iter;

   for(unsigned int i= 0; i < glob_matrix->size(); i++)
   { //durch die verschiedenen maps gehen 
      for(map_iter = (*glob_matrix)[i].begin(); map_iter!= (*glob_matrix)[i].end(); ++map_iter)
      { file<<i<<" "<<(*map_iter).first<<" "<<(*map_iter).second<<endl;

      }
   }
   file.close();
}

void saveK(vector<Point>* points){
    ofstream file;
    file.open("ksq.txt", ios::out);
    if(!(file.is_open())){
        printf("ksq.txt konnte nicht gespeichert werden\n");
        exit(1);
    }
    for(unsigned int i = 0; i < points->size(); i++){
        file << points->at(i).x << ' ' << points->at(i).y << ' ' << getKq(points->at(i).x,  points->at(i).y) << endl;
    }
    file.close();
}

double getKq(double x, double y){
   return (100.0+delta)*exp(-50.0*(x*x+y*y))-100.0;
}
