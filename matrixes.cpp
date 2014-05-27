
/*#include <map>
#include <vector>
#include "myColsamm/Source/Colsamm.h"
#include "readin.h"*/
#include "matrixes.h"

//using namespace ::_COLSAMM_;
//using namespace std;




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


vector<map< int,double> > get_build_matrix( vector<Point>* points, vector<Face>* faces){

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

        my_local_matrix = my_element.integrate(grad(v_()) * grad(w_()));

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








int main(int argc, char* argv[])
{
   vector<Point> points;
   vector<Face> faces;

   bool success =readFromFile("./inputs/unit_circle.txt",&points,&faces);
  cout<<success<<endl;
   cout<<"sizefaces:"<<faces.size()<<endl;
   //cout << faces.front().vertex0->x;
   vector<map< int,double> > glob_matrix=get_build_matrix( &points, &faces);
   save_global_matrix(&glob_matrix,"matrix.txt");



   return 0;
}
