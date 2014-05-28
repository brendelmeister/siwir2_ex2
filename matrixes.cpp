
/*#include <map>
#include <vector>
#include "myColsamm/Source/Colsamm.h"
#include "readin.h"*/
#include "matrixes.h"

//using namespace ::_COLSAMM_;
//using namespace std;
static double delta;
static double eps;


void add_to_global_matrix(vector<map< int,double> >* glob_matrix,Face element,vector< vector<double> >* my_local_matrix){

   //glob_matrix->at(1)=1.0;



            glob_matrix->at(element.vertex0->index)[element.vertex0->index]+=my_local_matrix->at(0).at(0);
            glob_matrix->at(element.vertex1->index)[element.vertex0->index]+=my_local_matrix->at(1).at(0);
            glob_matrix->at(element.vertex2->index)[element.vertex0->index]+=my_local_matrix->at(2).at(0);

            glob_matrix->at(element.vertex0->index)[element.vertex1->index]+=my_local_matrix->at(0).at(1);
            glob_matrix->at(element.vertex1->index)[element.vertex1->index]+=my_local_matrix->at(1).at(1);
            glob_matrix->at(element.vertex2->index)[element.vertex1->index]+=my_local_matrix->at(2).at(1);

            glob_matrix->at(element.vertex0->index)[element.vertex2->index]+=my_local_matrix->at(0).at(2);
            glob_matrix->at(element.vertex1->index)[element.vertex2->index]+=my_local_matrix->at(1).at(2);
            glob_matrix->at(element.vertex2->index)[element.vertex2->index]+=my_local_matrix->at(2).at(2);




    //vector<map< int,double> > glob_matrix = new vector<map< int,double > >(n);
    /*for (int i=0;i<n;++n){
for(int j=0;j<vertices.num_neighbours;++j){
glob_matrix[i][vertices.neighbours[j]]= vertices[]


}
}*/
}

vector<map< int,double> > create_global_matrix(int n){
    vector<map< int,double> > glob_matrix(n);//=new vector<map< int,double> >(n);
    for (int i=0;i<n;++i){
        glob_matrix[i];//=new map< int,double> ();
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
        corners[0] = faces->at(i).vertex0->x;
        corners[1] = faces->at(i).vertex0->y;
        corners[2] = faces->at(i).vertex1->x;
        corners[3] = faces->at(i).vertex1->y;
        corners[4] = faces->at(i).vertex2->x;
        corners[5] = faces->at(i).vertex2->y;

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



bool save_global_matrix(vector<map< int,double> >* glob_matrix, const char* name){
    ofstream file;
    file.open(name, ios::out);
      if(!(file.is_open())){
          printf(" konnte nicht gespeichert werden\n");
          return false;
      }
      for(unsigned int j = 0;j<glob_matrix->size();++j){
          for(unsigned int i = 0; i < glob_matrix->size(); i++){
              if(glob_matrix->at(j).count(i)==1){
                  file <<j<<" "<<i<<" "<<glob_matrix->at(j)[i]  << endl;
                }
          }

       }

          file.close();
     return true;
}


bool save_global_matrix_with_zeroes(vector<map< int,double> >* glob_matrix, const char* name){
    ofstream file;
    file.open(name, ios::out);
      if(!(file.is_open())){
          printf(" konnte nicht gespeichert werden\n");
          return false;
      }
      for(unsigned int j = 0;j<glob_matrix->size();++j){
          for(unsigned int i = 0; i < glob_matrix->size(); i++){
              if(glob_matrix->at(j).count(i)==1){
                  file <<glob_matrix->at(j)[i]  << ' ';
              }else{
                   file <<0.0  << ' ';
              }
          }
          file << endl;
       }

          file.close();
     return true;
}


double getKq(double x, double y){
    return (100.0+delta)*exp(-50.0*(x*x+y*y))-100.0;
}

int main(int argc, char* argv[])
{
   if (argc != 3) {
      cerr<<"error: wrong number of arguments"<<endl;
      cout<<"call ./waveguide d e "<<endl;
      cout<<"d: variable for the calculation of the variable coefficient k(x,y) ; e: stopping criterion for the solver"<<endl;
      exit(EXIT_FAILURE);
   }
   delta = atof(argv[1]);
   eps = atof(argv[2]);



   vector<Point> points;
   vector<Face> faces;

   bool success =readFromFile("./inputs/unit_circle.txt",&points,&faces);
   cout<<success<<endl;



   vector<map< int,double> > glob_stiff=get_build_matrix( &points, &faces,"stiffness");
   vector<map< int,double> > glob_mass=get_build_matrix( &points, &faces,"mass");
   save_global_matrix(&glob_stiff,"stiffness.txt");
   save_global_matrix(&glob_mass,"mass.txt");

   double lambda, lambda_old;
   vector<double> u (glob_stiff.size(),1.);
   vector<double> f (glob_stiff.size(),1.);
   lambda=1.;

   do {
      lambda_old = lambda;
      matrixVector(&glob_mass,&u,&f);//f=M*u
      //solve A*u=f
      int steps =cgsolve( &glob_stiff,&u,&f, eps);
      cout<<"cgiter: "<<steps<<endl;

      vectorScalar(&u,1./(euclNorm(&u)));
      //use f as tmp here;
      matrixVector(&glob_stiff,&u,&f);

      lambda = vectorVector(&u,&f);
      matrixVector(&glob_mass,&u,&f);
      lambda = lambda/vectorVector(&u,&f);
       cout<<"lambdaborder: "<<fabs((lambda-lambda_old)/lambda_old)<<endl;
   } while (fabs((lambda-lambda_old)/lambda_old)>1e-10 );


   return 0;
}
