#ifndef READIN_H
#define READIN_H
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <string.h>


using namespace std;

typedef struct Point
{
   //int index;
   double x,y;
   //contains the indices to all neighbouring points as keys.
   //value is either -1 if the path to the according neighbour
   //was not yet subdivided, otherwise the index of the midPoint
   map<int,int> midToNb;
} Point;

typedef struct Face
{
   int vertex0;
   int vertex1;
   int vertex2;
} Face;

//Read the points and faces from the given inputfile
//return true on success
bool readFromFile(string fileName, vector<Point>* points, vector<Face>* faces);

#endif
