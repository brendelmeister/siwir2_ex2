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
   //contains the indices of existing midpoints to (former) neighbouring points as keys.
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

void refine(Face* face,vector<Point>* points,vector<Face>* newFaces);

void clearNeighbours(Point* point);
#endif
