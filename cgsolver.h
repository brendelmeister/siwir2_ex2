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


int cgsolve(vector<map<int,double> >* A,vector<double>* x,vector<double>* b,double eps);


#endif
