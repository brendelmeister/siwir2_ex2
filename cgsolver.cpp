#include "cgsolver.h"




int cgsolve(vector<map<int,double> >* A,vector<double>* x,vector<double>* b,double eps) {

    NX = A->size();
     NY = A->size();
     //int rows = NY - 1;
     //int columns = NX - 1;
     C = 100;


     

      

      
      // variables for the cg algorithm
      vector<double> temp(x->size());
      vector<double> temp2(x->size());
      vector<double> g(x->size());
      double delta0 = 0.0;
      double delta1 = 0.0;
      double alpha = 0.0;
      double beta;
      vector<double> d(x->size());
      vector<double> h(x->size());
      
      // cg algorithm
      //x = x0
      matrixVector(A,x, &temp);

      vectorSub(&temp,b,&g);
      //matmult(rows*columns, 1, rows*columns, A, rows*columns, x, 1, temp, 1); sub(temp,b,g,rows*columns);  //g = Ax-b

      //delta0 = scalar(g,g,rows*columns); // delta0 = (g,g)
      delta0= vectorVector(&g,&g);
      cout<<"norm"<< euclNorm(&g)<<endl;
      cout<<"delta0 :"<<delta0<<endl;
      int step=0;

      if (delta0 >= eps) {
          vectorScalar(&g, -1.0, &d);

        //factor(g,-1,d, rows*columns); //d = -g

          for ( step= 0; step < C; step++) {
               matrixVector( A,&d,&h);
              //matmult(rows*columns, 1, rows*columns, A, rows*columns, d, 1, h, 1); // h = Ad
             alpha = delta0 /vectorVector(&d,&h);
               // alpha = delta0 / scalar(d,h, rows*columns);//a = delta0 / (d,h)

             vectorScalar(&d,alpha,&temp); vectorAdd(x,&temp,x);
             vectorScalar(&h,alpha,&temp); vectorAdd(&g,&temp,&g);
              //factor(d,alpha,temp, rows*columns); add(x, temp, x, rows*columns); //x = x + alpha*d
              //factor(h,alpha,temp, rows*columns); add(g, temp, g, rows*columns); // g = g + alpha*h

               delta1 =vectorVector(&g, &g);
              //delta1 = scalar(g,g,rows*columns); //delta1 = (g,g)
             cout<<"delta1 :"<<delta1<< "> " << eps<<endl;
              if (delta1 <= eps){
                break;
                cout<<"delta: "<<delta1<<endl;
              }

              beta = delta1/delta0; // beta = delta1/delta0
              vectorScalar(&d,beta,&temp);
              vectorScalar(&g,-1.0,&temp);
              vectorAdd(&temp,&temp2,&d);
              //factor(d,beta,temp, rows*columns); factor(g,-1,temp2, rows*columns); add(temp,temp2,d,rows*columns);   // d = -g + beta*d
              delta0 = delta1;
           }
      }
     cout<<"Steps:"<<step<<endl;
     //print(x, rows, columns, rows);
     return step;
}
 
