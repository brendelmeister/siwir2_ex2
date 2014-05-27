#ifndef CGSOLVER_H
#define CGSOLVER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include "iteration.h"
/*
extern "C" {
  #include <cblas.h>
}*/

using namespace std;

static double EPS;// epsilon
static int C;// number of iterations
static int NX;//number if intervalls in x direction
static int NY;//number if intervalls in i direction




int cgsolve(vector<map<int,double> >* A,vector<double>* x,vector<double>* b,double eps);


#endif
