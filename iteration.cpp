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

    for (vector<double>::iterator it = u->begin() ; it != u->end(); ++it)
        (*it) = (*it)*scalar;

}

void vectorScalar(vector<double>* u,double scalar,vector<double>* ret)
{


    for (std::pair<vector<double>::iterator, vector<double>::iterator> it(u->begin(), ret->begin()) ; 
            it.first!= u->end() && it.second!= ret->end(); ++it.first, ++it.second)
        (*it.second) = (*it.first)*scalar;
}

void vectorAdd(vector<double>* u,vector<double>* v,vector<double>* ret)
{
    if (u->size()!=v->size())
        return;

    vector<double>::iterator itu;
    vector<double>::iterator itv;
    vector<double>::iterator itret ;
    for (itu  = u->begin(), itv = v->begin(), itret= ret->begin();
            itu != u->end() && itv!= v->end() && itret != ret->end();
            ++itu, ++itv, ++itret)
    {
        (*itret) = (*itu)+(*itv);
    }
}



void vectorSub(vector<double>* u,vector<double>* v,vector<double>* ret)
{
    if (u->size()!=v->size())
        return;


    vector<double>::iterator itu;
    vector<double>::iterator itv;
    vector<double>::iterator itret ;
    for (itu  = u->begin(), itv = v->begin(), itret= ret->begin();
            itu != u->end() && itv!= v->end() && itret != ret->end();
            ++itu, ++itv, ++itret)
    {
        (*itret) = (*itu)-(*itv);
    }



}


double vectorVector(vector<double>* u,vector<double>* v)
{
    double ret=0.; 

    if (u->size()!=v->size())
        return ret;
    for (std::pair<vector<double>::iterator, vector<double>::iterator> it(u->begin(),v->begin()) ; 
            it.first!= u->end() && it.second!= v->end(); ++it.first, ++it.second)

        ret+=(*it.first)*(*it.second);

    return ret;
}

void matrixVector(vector<map<int,double> >* mat,vector<double>* vec,vector<double>* ret)
{
    if (mat->size()!=vec->size())
        return;

    vector<double>::iterator itvec = vec->begin();


    map<int,double>::iterator map_iter;
    for(unsigned int i= 0; i < mat->size(); i++){ //durch die verschiedenen maps gehen
        double value = 0.0; 
        for(map_iter = (*mat)[i].begin(); map_iter!= (*mat)[i].end(); ++map_iter){
        
            value += (*map_iter).second*(vec->at((*map_iter).first));

        }
        (*ret)[i]=value;
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

    cout<<"vecscalar 3 test1"<<endl;
    vectorScalar(&res,3.,&test1);
    vectorPrint(&test1);



    // cout<<"vecvec test1 abc "<<endl;
    cout<<vectorVector(&test1,&abc)<<endl;
    vector<map< int,double> > testmat(2);//=new vector<map< int,double> >(n);
    for (int i=0;i<2;++i){
        testmat[i];//=new map< int,double> ();
    }

    testmat[0][0]= 1;
    testmat[0][1]= 1;
    testmat[1][0]= 1;
    //testmat[1][1]= 1;


    cout<<"matrixVector"<<endl;
    vector<double> vec(2,9.0);
    vector<double> ret(3);
    matrixVector(&testmat,&vec,&ret);
    vectorPrint(&ret);

    cout<<"matrixVector1"<<endl;
    vector<double> vec1(2,9.0);
    vector<double> ret1(3);
    matrixVector(&testmat,&vec1,&ret1);
    vectorPrint(&ret1);


}

bool saveDouble(double d,const char* name){
    ofstream file;
    file.open(name, ios::out);
      if(!(file.is_open())){
          printf(" konnte nicht gespeichert werden\n");
          return false;
      }

     file <<setprecision(10)<<d<<endl;
     file.close();
     return true;
}

