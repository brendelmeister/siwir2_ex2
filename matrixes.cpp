#include <map>
#include <vector>

using namespace ::_COLSAMM_;
using namespace std;

void add_global_matrix(vector<map< int,double> > glob_matrix,Face element,vector< vector< double > > my_local_matrix
){
    for (int j=0;j<3;++j){
        for (int i=0;i<3;++i){
            glob_matrix[element.vertex[j]][element.vertex[i]]+=my_local_matrix[j][i];
        }
    }

    //vector<map< int,double> > glob_matrix = new vector<map< int,double > >(n);
    /*for (int i=0;i<n;++n){
        for(int j=0;j<vertices.num_neighbours;++j){
            glob_matrix[i][vertices.neighbours[j]]= vertices[]


        }
    }*/
}

vector<map< int,double> > create_global_matrix(int n){
    vector<map< int,double> > glob_matrix=new vector<map< int,double> >(n);
    for (int i=0;i<n;++n){
        glob_matrix[i]=new map< int,double> ();
    }
}
