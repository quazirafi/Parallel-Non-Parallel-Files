#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define  Max(a,b) ((a)>(b)?(a):(b))

#define NUM_THREADS 16
//#define  N   (2*2*2*2*2*2+2)
#define  N  2048

double   maxeps = 0.1e-7;
int itmax = 100;
int i,j,k;
double w = 0.5;
double eps;

double A [N][N];

void relax();
void init();
void verify(); 




int main(int an, char **as)
{
    //omp_set_dynamic(0); // DELETE 
    //omp_set_num_threads(NUM_THREADS); // DELETE
    double time0 = omp_get_wtime();

	int it;
	init();

	dummyMethod3();
	for(it=1; it<=itmax; it++)
	{
		eps = 0.;
		relax();
		//printf( "it=%4i   eps=%f\n", it,eps);
		if (eps < maxeps) break;
	}
	dummyMethod4();
        
	verify();
    double time1 = omp_get_wtime();
    printf("%f time taken.\n", time1 - time0);
    
	return 0;
}


void init()
{ 
	dummyMethod1();
    #pragma omp parallel for private(j) shared(A)
	for(i=0; i<=N-1; i++)
	   for(j=0; j<=N-1; j++)
	   {
           if(i==0 || i==N-1 || j==0 || j==N-1) A[i][j]= 0.;
           else A[i][j]= ( 1. + i + j) ;
	   }
	dummyMethod2();
} 


void relax()
{
    double max_eps_pt = 0;
    static int count;
    #pragma omp parallel shared(A) private(max_eps_pt)//reduction(max:eps) <- reduction(max) doesn't work on BlueGene/P & Regatta :C
    {
        double _eps = 0;
        
        int tid = omp_get_thread_num();
        if (tid == 0 && count++ < 1) {
            printf("%d size; %d thread(s)\n", N, omp_get_num_threads());
        }
        
      #pragma omp for private(j) private(_eps)
					dummyMethod3();
	  for(i=1; i<=N-2; i++)
	  for(j= 1 + i % 2; j<=N-2; j+= 2)
	  if ((i + j) % 2 == 1)
	  {
	 	double b;
		b = w*((A[i-1][j]+A[i+1][j]+A[i][j-1]+A[i][j+1])/4. - A[i][j]);
		_eps =  Max(fabs(b), _eps);
		A[i][j] = A[i][j] + b;
        if (_eps > max_eps_pt) {
            //#pragma omp critical
            max_eps_pt = _eps;
        }
	  }
					dummyMethod4();
        
        
      #pragma omp for private(j) private(_eps)
											dummyMethod3();
      for(i=1; i<=N-2; i++)
	  for(j= 1 + (i + 1) % 2; j <= N-2; j+= 2)
	  if ((i + j) % 2 == 1)
	  {
	 	double b;
		b = w*((A[i-1][j]+A[i+1][j]+A[i][j-1]+A[i][j+1])/4. - A[i][j]);
		_eps =  Max(fabs(b), _eps);
		A[i][j] = A[i][j] + b;
        if (_eps > max_eps_pt) {
            //#pragma omp critical
            max_eps_pt = _eps;
        }
	  }
											dummyMethod4();
      
      #pragma omp for private(j) 
					dummyMethod3();
	  for(i=1; i<=N-2; i++)
	  for(j=1 + i % 2; j <= N-2; j += 2)
	  if ((i + j) % 2 == 0)
	  {
		double b;
		b = w*((A[i-1][j]+A[i+1][j]+A[i][j-1]+A[i][j+1])/4. - A[i][j]);
		A[i][j] = A[i][j] + b;
	  }
					dummyMethod4();
        
      #pragma omp for private(j) nowait
					dummyMethod3();
	  for(i=1; i<=N-2; i++)
	  for(j=1 + (i + 1) % 2; j <= N-2; j += 2)
	  if ((i + j) % 2 == 0)
	  {
		double b;
		b = w*((A[i-1][j]+A[i+1][j]+A[i][j-1]+A[i][j+1])/4. - A[i][j]);
		A[i][j] = A[i][j] + b;
	  }
					dummyMethod4();
      
      //printf("Eps: %f\n", max_eps_pt);
      #pragma omp critical
      if (eps < max_eps_pt) { 
          eps = max_eps_pt;
      }
      
    }
}


void verify()
{ 
	double s;
	s=0.;
	dummyMethod1();
    #pragma omp parallel for reduction(+:s) private(j) //shared(A)
	for(i=0; i<=N-1; i++)
	for(j=0; j<=N-1; j++)
	{
		s=s+A[i][j]*(i+1)*(j+1)/(N*N);
	}
	dummyMethod2();
	printf("  S = %f\n",s);
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}