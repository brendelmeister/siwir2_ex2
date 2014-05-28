


#include "readin.h"

//#include "matrixes.cpp"

//using namespace std;

/*typedef struct Point
{
   int index;
   double x,y;
} Point;

typedef struct Face
{
   Point* vertex0;
   Point* vertex1;
   Point* vertex2;
} Face;*/

//Read the points and faces from the given inputfile
//return true on success
bool readFromFile(string fileName, vector<Point>* points, vector<Face>* faces)
{

   ifstream input;
   input.open(fileName.c_str());
   if (!input.is_open())
      return false;

   int numberOfPoints;
   input >> numberOfPoints;

   input.ignore(100,'\n');
   input.ignore(100,'\n');

   cout<<"start reading points..."<<endl;
   //int idxTmp;
   for (int i=0;i<numberOfPoints;i++)
   {
      Point ptmp;
      input >> ptmp.index >> ptmp.x >> ptmp.y;
      
      points->push_back(ptmp);
   }
   cout<<"finished"<<endl;
   int numberOfFaces;
   input >> numberOfFaces;

   input.ignore(100,'\n');
   input.ignore(100,'\n');

    cout<<"start reading faces..."<<endl;
   int i0,i1,i2;
   for (int i=0;i<numberOfFaces;i++)
   {
      Face ftmp;
      input >> i0 >> i1 >> i2;
      ftmp.vertex0=&points->at(i0);
      ftmp.vertex1=&points->at(i1);
      ftmp.vertex2=&points->at(i2);
      
      faces->push_back(ftmp);
   }
   
    cout<<"finished"<<endl;
   return true;

}

/*

int main(int argc, char* argv[])
{
   vector<Point> points;
   vector<Face> faces;
   readFromFile("./inputs/unit_circle.txt",&points,&faces);

   cout << faces.front().vertex0->x;


   return 0;
}
*/
