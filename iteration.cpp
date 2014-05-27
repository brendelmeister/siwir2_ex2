#include "iteration.h"

double euclNorm(vector<double>* u)
{
   double norm = 0.;
   for (vector<double>::iterator it = u->begin() ; it != u->end(); ++it)
      norm += (*it)*(*it);

   return sqrt(norm);
}


void vectorScalar(vector<double>* u,double scalar)
{
   for (unsigned int i=0; i<u->size(); ++i)
      (*u)[i] = u->at(i)*scalar;
}


void vectorScalar(vector<double>* u,double scalar,vector<double>* ret)
{
   for (unsigned int i=0; i<u->size(); ++i)
      (*ret)[i] = u->at(i)*scalar;
}

void vectorAdd(vector<double>* u,vector<double>* v,vector<double>* ret)
{
   for (unsigned int i=0; i<u->size(); ++i)
      (*ret)[i] = u->at(i)+v->at(i);
}

void vectorSub(vector<double>* u,vector<double>* v,vector<double>* ret)
{
   for (unsigned int i=0; i<u->size(); ++i)
      (*ret)[i] = u->at(i)-v->at(i);
}


double vectorVector(vector<double>* u,vector<double>* v)
{
   double ret=0.; 

   if (u->size()!=v->size())
      return ret;

   for (unsigned int i=0; i<u->size(); ++i)
      ret=u->at(i)*v->at(i);

   return ret;
}

void matrixVector(vector<map<int,double> >* mat,vector<double>* vec,vector<double>* ret)
{
   if (mat->size()!=vec->size())
      return;

   for(unsigned int j = 0;j<mat->size();++j){
      double value=0.;

      for(unsigned int i = 0; i < mat->size(); i++){
	 if(mat->at(j).count(i)==1){
	    value += mat->at(j).at(i)*vec->at(i);
	 }
      }
      (*ret)[j]=value;
   }
}

