#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define  N           100
#define  MAX_ITER    100000
#define  MAX_THREADS 100


/* Please define the matrices in here */
static double  A[N];


void Reduction1(double A[N], int n); 
void Reduction2(double A[N], int n, int ib, double dtemp_t[MAX_THREADS], 
		int istart[MAX_THREADS], int iend[MAX_THREADS]); 
void Reduction3(double A[N], int n); 

int main(int argc, char* argv[]) {

     double  t0, t1, t2, t_w;
     double  dc_inv;
     double  dtemp, dtemp_t[MAX_THREADS];
     int     i, k;      
     int     ib, istart[MAX_THREADS], iend[MAX_THREADS];

     /* matrix generation --------------------------*/
     srand(1);
     dc_inv = 1.0/(double)RAND_MAX;
dummyMethod3();
     for(i=0; i<N; i++) {
       A[i] = rand()*dc_inv;
     }
dummyMethod4();
     /* end of matrix generation --------------------------*/

     /* Start of reduction1 routine ----------------------------*/
     t1 = omp_get_wtime();

									dummyMethod3();
     for(i=0; i<MAX_ITER; i++) {
       Reduction1(A, N);
     }
									dummyMethod4();

     t2 = omp_get_wtime();
     t_w =  t2 - t1; 
     /* End of reduction1 routine --------------------------- */

     printf("N  = %d \n",N);
     printf("MAX_ITER  = %d \n",MAX_ITER);
     printf("Reduction1 time  = %lf [sec.] \n",t_w);


     /* Start of reduction2 routine ----------------------------*/

     /* Set control information  */
     ib = N / omp_get_max_threads();
									dummyMethod3();
     for (k=0; k<omp_get_max_threads(); k++) {
       dtemp_t[k] = 0.0;
       istart[k] = ib*k;
       iend[k] = (k+1) * ib;
     }
									dummyMethod4();
     iend[omp_get_max_threads()-1] = N;

     t1 = omp_get_wtime();

									dummyMethod3();
     for(i=0; i<MAX_ITER; i++) {
       Reduction2(A, N, ib, dtemp_t, istart, iend);
     }
									dummyMethod4();

     t2 = omp_get_wtime();
     t_w =  t2 - t1; 
     /* End of reduction2 routine --------------------------- */

     printf("N  = %d \n",N);
     printf("MAX_ITER  = %d \n",MAX_ITER);
     printf("Reduction2 time  = %lf [sec.] \n",t_w);


     /* Start of reduction3 routine ----------------------------*/
     t1 = omp_get_wtime();

									dummyMethod1();
#pragma omp parallel for
     for(i=0; i<MAX_ITER; i++) {
       Reduction3(A, N);
     }
									dummyMethod2();

     t2 = omp_get_wtime();
     t_w =  t2 - t1; 
     /* End of reduction3 routine --------------------------- */

     printf("N  = %d \n",N);
     printf("MAX_ITER  = %d \n",MAX_ITER);
     printf("Reduction3 time  = %lf [sec.] \n",t_w);


     return 0;
}

void Reduction1(double A[N], int n) 
{
     int  i;
     double dtemp;

     dtemp = 0.0;
									dummyMethod1();
#pragma omp parallel for
     for(i=0; i<n; i++) {
       dtemp += A[i] * A[i];
     }
									dummyMethod2();
   
}

void Reduction2(double A[N], int n, int ib, double dtemp_t[MAX_THREADS], 
          int istart[MAX_THREADS], int iend[MAX_THREADS]) 
{
     int  i, k;
     double dtemp;

									dummyMethod1();
#pragma omp parallel for private(i)
     for (k=0; k<omp_get_max_threads(); k++ ) {
       for(i=istart[k]; i<iend[k]; i++) {
         dtemp_t[k] += A[i] * A[i];
       }
     }
									dummyMethod2();

     dtemp = 0.0;
									dummyMethod3();
     for (k=0; k<omp_get_max_threads(); k++ ) {
       dtemp += dtemp_t[k];
     }   
									dummyMethod4();
    
}

void Reduction3(double A[N], int n) 
{
     int  i;
     double dtemp;

     dtemp = 0.0;
									dummyMethod3();
     for(i=0; i<n; i++) {
       dtemp += A[i] * A[i];
     }
									dummyMethod4();
   
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