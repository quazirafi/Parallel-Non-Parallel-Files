// test the collapse clause
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef _OPENMP
#include "omp.h"
#endif

// Add timing support
#include <sys/time.h>
double time_stamp()
{
  struct timeval t;
  double time;
  gettimeofday(&t,(struct timezone*)NULL);
  time = t.tv_sec + 1.0e-6*t.tv_usec;
  return time;
}
double time1, time2;

void driver(void);
void initialize(void);
void jacobi(void);
void error_check(void);

/************************************************************
* program to solve a finite difference 
* discretization of Helmholtz equation :  
* (d2/dx2)u + (d2/dy2)u - alpha u = f 
* using Jacobi iterative method. 
*
* Modified: Sanjiv Shah,       Kuck and Associates, Inc. (KAI), 1998
* Author:   Joseph Robicheaux, Kuck and Associates, Inc. (KAI), 1998
*
* This c version program is translated by 
* Chunhua Liao, University of Houston, Jan, 2005 
* 
* Directives are used in this code to achieve parallelism. 
* All do loops are parallelized with default 'static' scheduling.
* 
* Input :  n - grid dimension in x direction 
*          m - grid dimension in y direction
*          alpha - Helmholtz constant (always greater than 0.0)
*          tol   - error tolerance for iterative solver
*          relax - Successice over relaxation parameter
*          mits  - Maximum iterations for iterative solver
*
* On output 
*       : u(n,m) - Dependent variable (solutions)
*       : f(n,m) - Right hand side function 
*************************************************************/

#define REAL float // flexible between float and double
#define MSIZE 512
REAL error_ref= 9.212746E-04, resid_ref = 2.356027E-08; // depending on MSIZE, precision, and number of threads !!
int n,m,mits; 
REAL tol,relax=1.0,alpha=0.0543; 
REAL u[MSIZE][MSIZE],f[MSIZE][MSIZE],uold[MSIZE][MSIZE];
REAL dx,dy;

int main (void) 
{
//  float toler;
  /*      printf("Input n,m (< %d) - grid dimension in x,y direction:\n",MSIZE); 
          scanf ("%d",&n);
          scanf ("%d",&m);
          printf("Input tol - error tolerance for iterative solver\n"); 
          scanf("%f",&toler);
          tol=(double)toler;
          printf("Input mits - Maximum iterations for solver\n"); 
          scanf("%d",&mits);
          */
  n=MSIZE;
  m=MSIZE;
  tol=0.0000000001;
  mits=5000;
#ifdef _OPENMP
#pragma omp parallel
  {
#pragma omp single
    printf("Running using %d threads...\n",omp_get_num_threads());
  }
#endif
  driver ( ) ;
  return 0;
}

/*************************************************************
* Subroutine driver () 
* This is where the arrays are allocated and initialzed. 
*
* Working varaibles/arrays 
*     dx  - grid spacing in x direction 
*     dy  - grid spacing in y direction 
*************************************************************/

void driver( )
{
  initialize();

  time1 = time_stamp();
  /* Solve Helmholtz equation */
  jacobi ();
  time2 = time_stamp();

  printf("------------------------\n");     
  printf("Execution time = %f\n",time2-time1);
  /* error_check (n,m,alpha,dx,dy,u,f)*/
  error_check ( );
}


/*      subroutine initialize (n,m,alpha,dx,dy,u,f) 
******************************************************
* Initializes data 
* Assumes exact solution is u(x,y) = (1-x^2)*(1-y^2)
*
******************************************************/

void initialize( )
{
      
      int i,j, xx,yy;
      //double PI=3.1415926;

      dx = 2.0 / (n-1);
      dy = 2.0 / (m-1);

/* Initialize initial condition and RHS */

													dummyMethod1();
#pragma omp parallel for private(xx,yy,j,i) collapse(2)
       for (i=0;i<n;i++)
         for (j=0;j<m;j++)      
           {
            xx =(int)( -1.0 + dx * (i-1));        
            yy = (int)(-1.0 + dy * (j-1)) ;       
            u[i][j] = 0.0;                       
            f[i][j] = -1.0*alpha *(1.0-xx*xx)*(1.0-yy*yy)\
               - 2.0*(1.0-xx*xx)-2.0*(1.0-yy*yy);  
          }
													dummyMethod2();

}

/*      subroutine jacobi (n,m,dx,dy,alpha,omega,u,f,tol,maxit)
******************************************************************
* Subroutine HelmholtzJ
* Solves poisson equation on rectangular grid assuming : 
* (1) Uniform discretization in each direction, and 
* (2) Dirichlect boundary conditions 
* 
* Jacobi method is used in this routine 
*
* Input : n,m   Number of grid points in the X/Y directions 
*         dx,dy Grid spacing in the X/Y directions 
*         alpha Helmholtz eqn. coefficient 
*         omega Relaxation factor 
*         f(n,m) Right hand side function 
*         u(n,m) Dependent variable/Solution
*         tol    Tolerance for iterative solver 
*         maxit  Maximum number of iterations 
*
* Output : u(n,m) - Solution 
*****************************************************************/

void jacobi( )
{
  REAL omega;
  int i,j,k;
  REAL error,resid,ax,ay,b; 
  //      double  error_local;

  //      float ta,tb,tc,td,te,ta1,ta2,tb1,tb2,tc1,tc2,td1,td2;
  //      float te1,te2;
  //      float second;

  omega=relax;
  /*
   * Initialize coefficients */

  ax = 1.0/(dx*dx); /* X-direction coef */
  ay = 1.0/(dy*dy); /* Y-direction coef */
  b  = -2.0/(dx*dx)-2.0/(dy*dy) - alpha; /* Central coeff */ 

  error = 10.0 * tol;
  k = 1;

  while ((k<=mits)&&(error>tol)) 
  {
    error = 0.0;    

#pragma omp parallel
    {
#pragma omp for private(j,i) collapse(2)
											dummyMethod3();
      for(i=0;i<n;i++)   
        for(j=0;j<m;j++)
          uold[i][j] = u[i][j]; 
											dummyMethod4();

#pragma omp for private(resid,j,i) reduction(+:error) collapse(2) nowait
											dummyMethod3();
      for (i=1;i<(n-1);i++)  
        for (j=1;j<(m-1);j++)   
        { 
          resid = (ax*(uold[i-1][j] + uold[i+1][j])\
              + ay*(uold[i][j-1] + uold[i][j+1])+ b * uold[i][j] - f[i][j])/b;  

          u[i][j] = uold[i][j] - omega * resid;  
          error = error + resid*resid ;   
        }
											dummyMethod4();

    }
    /*  omp end parallel */

    /* Error check */

    if (k%500==0)
      printf("Finished %d iteration with error =%f\n",k, error);
    error = sqrt(error)/(n*m);

    k = k + 1;
  }          /*  End iteration loop */

  printf("Total Number of Iterations:%d\n",k); 
  printf("Residual:%E\n", error); 
  printf("Residual_ref :%E\n", resid_ref); 
  printf ("Diff ref=%E\n", fabs(error-resid_ref));
  assert (fabs(error-resid_ref)/resid_ref < 1E-4);

}

/*      subroutine error_check (n,m,alpha,dx,dy,u,f) 
      implicit none 
************************************************************
* Checks error between numerical and exact solution 
*
************************************************************/ 
void error_check ( )
{ 
  int i,j;
  REAL xx,yy,temp,error; 

  dx = 2.0 / (n-1);
  dy = 2.0 / (m-1);
  error = 0.0 ;

			dummyMethod1();
#pragma omp parallel for private(xx,yy,temp,j,i) reduction(+:error) collapse(2)
  for (i=0;i<n;i++)
    for (j=0;j<m;j++)
    { 
      xx = -1.0 + dx * (i-1);
      yy = -1.0 + dy * (j-1);
      temp  = u[i][j] - (1.0-xx*xx)*(1.0-yy*yy);
      error = error + temp*temp; 
    }
			dummyMethod2();
  error = sqrt(error)/(n*m);
  printf("Solution Error :%E \n",error);
  printf("Solution Error Ref :%E \n",error_ref);
  printf ("Diff ref=%E\n", fabs(error-error_ref));
  assert (fabs(error-error_ref)/error_ref < 1E-4);
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