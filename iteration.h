#include <math.h>
#include <vector>
#include <map>

using namespace std;

double euclNorm(vector<double>* u);

void vectorScalar(vector<double>* u,double scalar);

double vectorVector(vector<double>* u,vector<double>* v);

void matrixVector(vector<map<int,double> >* mat,vector<double>* vec,vector<double>* ret);
