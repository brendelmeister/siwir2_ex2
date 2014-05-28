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
    if (u->size()!=v->size())
       return;

   for (unsigned int i=0; i<u->size(); ++i){
      (*ret)[i] = u->at(i)+v->at(i);
   }
}

void vectorSub(vector<double>* u,vector<double>* v,vector<double>* ret)
{
    if (u->size()!=v->size())
       return;

    for (unsigned int i=0; i<u->size(); ++i)
      (*ret)[i] = u->at(i)-v->at(i);
}


double vectorVector(vector<double>* u,vector<double>* v)
{
   double ret=0.; 

   if (u->size()!=v->size())
      return ret;

   for (unsigned int i=0; i<u->size(); ++i)
      ret+=u->at(i)*v->at(i);

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


void vectorPrint(vector<double>* vec){
    for(unsigned int i =0;i<vec->size();++i){
        cout<<vec->at(i)<<endl;
    }
}

bool vectorSave(vector<double>* vec,vector<Point>* points,const char* name){
    ofstream file;
    file.open(name, ios::out);
      if(!(file.is_open())){
          printf(" konnte nicht gespeichert werden\n");
          return false;
      }
      for(unsigned int i = 0; i < vec->size(); ++i){
          file <<points->at(i).x<<" "<<points->at(i).y<<" "<<vec->at(i)<<endl;
      }

     file.close();
     return true;

}


void testVectors(){
    vector<double> test1(10,8.0);
    vector<double> abc(10,7.);
    vector<double> res(10);

    cout<<"vecadd test1+abc "<<endl;
    vectorAdd(&test1,&abc,&res);
    vectorPrint(&res);

    cout<<"vecsub res-abc "<<endl;
    vectorSub(&res,&abc,&res);
    vectorPrint(&res);

    cout<<"vecscalar 3 "<<endl;
    vectorScalar(&res,3.);
    vectorPrint(&res);

     cout<<"vecscalar 3 "<<endl;
    vectorScalar(&res,3.,&test1);
    vectorPrint(&test1);

    cout<<"vecvec test1 abc "<<endl;
    cout<<vectorVector(&test1,&abc)<<endl;
    vector<map< int,double> > testmat(2);//=new vector<map< int,double> >(n);
    for (int i=0;i<2;++i){
        testmat[i];//=new map< int,double> ();
    }

    testmat[0][0]= 1;
    testmat[0][1]= 1;
    testmat[1][0]= 1;
    //testmat[1][1]= 1;

    vector<double> vec(2,8.0);
    vector<double> ret(2);
    matrixVector(&testmat,&vec,&ret);
    vectorPrint(&ret);

}

