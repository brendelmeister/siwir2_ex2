


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
   int idxTmp;
   for (int i=0;i<numberOfPoints;i++)
   {
      Point ptmp;
      input >> idxTmp >> ptmp.x >> ptmp.y;
      //ptmp.midToNb;
      
      points->push_back(ptmp);
   }
   cout<<"finished"<<endl;
   int numberOfFaces;
   input >> numberOfFaces;

   input.ignore(100,'\n');
   input.ignore(100,'\n');

    cout<<"start reading faces..."<<endl;
   for (int i=0;i<numberOfFaces;i++)
   {
      Face ftmp;
      input >> ftmp.vertex0 >> ftmp.vertex1 >> ftmp.vertex2 ;

      //add neighbours
      points->at(ftmp.vertex0).midToNb[ftmp.vertex1]=-1;
      points->at(ftmp.vertex0).midToNb[ftmp.vertex2]=-1;

      points->at(ftmp.vertex1).midToNb[ftmp.vertex0]=-1;
      points->at(ftmp.vertex1).midToNb[ftmp.vertex2]=-1;

      points->at(ftmp.vertex2).midToNb[ftmp.vertex0]=-1;
      points->at(ftmp.vertex2).midToNb[ftmp.vertex1]=-1;


      faces->push_back(ftmp);
   }
   
    cout<<"finished"<<endl;
   return true;

}

/*
void refine(Face* face,vector<Point>* points)
{
   //the mid-Points to be created;
   int i01,i02,i12;
   Point m01,m02,m12;

   //if the midPoint between vertex 0 and 1 does not exist
   //create it; add it to the vertex list; and update all neighbours
   if (points->at(face->vertex0).midToNb.at(face->vertex1) == -1)
   {
      m01.x = (points->at(face->vertex1).x - points->at(face->vertex0).x)/2.;
      m01.y = (points->at(face->vertex1).y - points->at(face->vertex0).y)/2.;

      m01.midToNb[face->vertex0]=-1;
      m01.midToNb[face->vertex1]=-1;

      points->push_back(m01);

	//remove and set new neighbours of face->vertex0 and vertex1
	

   }
   else
      m01 = points->at(points->at(face->vertex0).midToNb.at(face->vertex1));


   m01.midToNb[i02]=-1;
   m01.midToNb[i12]=-1;


//add four faces

}
*/

/*
bool readFromFileRefine(string fileName, vector<Point>* points, vector<Face>* faces,int lvl){
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
*/



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
