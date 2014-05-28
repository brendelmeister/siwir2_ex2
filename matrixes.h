#ifndef MATRIXES_H
#define MATRIXES_H
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include "myColsamm/Source/Colsamm.h"
#include "readin.h"
#include "iteration.h"
#include "cgsolver.h"

using namespace ::_COLSAMM_;
using namespace std;




void add_to_global_matrix(vector<map< int,double> >* glob_matrix,Face element,vector< vector<double> >* my_local_matrix);

vector<map< int,double> > create_global_matrix(int n);

vector<map< int,double> > get_build_matrix( vector<Point>* points, vector<Face>* faces,string type);
bool save_global_matrix(vector<map< int,double> >* glob_matrix, const char* name);
bool save_global_matrix_with_zeroes(vector<map< int,double> >* glob_matrix, const char* name);
double getKq(double x, double y);


#endif
