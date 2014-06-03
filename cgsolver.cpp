#include "cgsolver.h"

int cgsolve(vector<map<int,double> >* A,vector<double>* x,vector<double>* b,double eps) {
   int C = 1000000;

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

   matrixVector(A,x, &temp);//g = Ax-b
   vectorSub(&temp,b,&g);

   delta0= vectorVector(&g,&g);// delta0 = (g,g)

   int step=0;

   if (delta0 >= eps) {
      vectorScalar(&g, -1.0, &d);//d = -g

      for ( step= 0; step < C; step++) {
	 matrixVector( A,&d,&h);// h = Ad

	 alpha = delta0 /vectorVector(&d,&h);//a = delta0 / (d,h)

	 vectorScalar(&d,alpha,&temp); vectorAdd(x,&temp,x);//x = x + alpha*d
	 vectorScalar(&h,alpha,&temp); vectorAdd(&g,&temp,&g);// g = g + alpha*h

	 delta1 =vectorVector(&g, &g);//delta1 = (g,g)

	 if (delta1 <= eps){
	    break;
	    cout<<"delta: "<<delta1<<endl;
	 }

	 beta = delta1/delta0; // beta = delta1/delta0
	 vectorScalar(&d,beta,&temp);// d = -g + beta*d
	 vectorSub(&temp,&g,&d);
	 delta0 = delta1;
      }
   }

   //cout<<"Steps:"<<step<<endl;
   return step;
}
 
