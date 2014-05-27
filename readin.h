#ifndef READIN_H
#define READIN_H
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>


using namespace std;

typedef struct Point
{
   int index;
   double x,y;
} Point;

typedef struct Face
{
   Point* vertex0;
   Point* vertex1;
   Point* vertex2;
} Face;

//Read the points and faces from the given inputfile
//return true on success
bool readFromFile(string fileName, vector<Point>* points, vector<Face>* faces);

#endif
