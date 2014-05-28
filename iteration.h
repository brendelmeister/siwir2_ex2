#ifndef ITERATION_H
#define ITERATION_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>

#include "readin.h"


using namespace std;

double euclNorm(vector<double>* u);

void vectorScalar(vector<double>* u, double scalar, vector<double> *ret);

void vectorScalar(vector<double>* u, double scalar);

double vectorVector(vector<double>* u,vector<double>* v);

void vectorAdd(vector<double>* u,vector<double>* v,vector<double>* ret);

void vectorSub(vector<double>* u,vector<double>* v,vector<double>* ret);

void matrixVector(vector<map<int,double> >* mat,vector<double>* vec,vector<double>* ret);

void vectorPrint(vector<double>* vec);

bool vectorSave(vector<double>* vec,vector<Point>* points,const char* name);

void testVectors();

#endif
