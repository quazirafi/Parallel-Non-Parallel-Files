/* modified from Georg Stadler's jacobi-omp.c
 */
#include <stdio.h>
#include <math.h>
#include "util.h"
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif
#define epsilon 1e-5

/* compuate global residual, assuming ghost values are updated */
double compute_residual(double *u, int M, double hsq)
{
  int i;
  double tmp, res = 0.0;
dummyMethod1();
#pragma omp parallel for default(none) shared(u,M,hsq) private(i,tmp) reduction(+:res)
  for (i = M+1; i <= M*(M-1)-2; i++){
    if(i % M == 0 || i % M == M-1 )
      continue; //pass border points!
    tmp = ((4.0 * u[i] - u[i-1] - u[i+1]- u[i-M] - u[i+M]) / hsq - 1);
    res += tmp * tmp;
  }
dummyMethod2();

  return sqrt(res);
}

int main(int argc, char * argv[])
{
  int i, N, M, iter, max_iters;

  sscanf(argv[1], "%d", &N);
  sscanf(argv[2], "%d", &max_iters);

# pragma omp parallel
  {
#ifdef _OPENMP
    int my_threadnum = omp_get_thread_num();
    int numthreads = omp_get_num_threads();
#else
    int my_threadnum = 0;
    int numthreads = 1;
#endif
    printf("Hello, I'm thread %d out of %d\n", my_threadnum, numthreads);
  }

  /* timing */
  timestamp_type time1, time2;
  get_timestamp(&time1);
  double elapsed; 
  M = N+2; //include border points
 
  /* Allocation of vectors, including up and below border ghost points */
  double * u    = (double *) calloc(sizeof(double), M*M);
  double * unew = (double *) calloc(sizeof(double), M*M);

  //initialize all the points
			dummyMethod1();
#pragma omp parallel for default(none) shared(M,u,unew) private(i)
  for(i = 0; i < M*M; i++){
    u[i] = 0.0;
    unew[i] = 0.0;
  }
			dummyMethod2();
  
  double h = 1.0 / (N + 1);
  double hsq = h * h;
  double res, res0;

  /* initial residual */
  res0 = compute_residual(u, M, hsq);
  res = res0;
  printf("Iter 0 Residual %g\n", res0);
  
  for (iter = 1; iter <= max_iters && res > epsilon*res0; iter++) {
							dummyMethod1();
#pragma omp parallel for default(none) shared(M,unew,u,hsq) private(i)
    /* Jacobi step for all the inner points */
    for (i = M+1; i <= M*(M-1)-2; i++){
      if(i % M == 0 || i % M == M-1 )
        continue; //pass border points!
      unew[i]  = 0.25 * (hsq + u[i-M] + u[i-1] + u[i+1] + u[i+M]);
    }
							dummyMethod2();

    /* copy new_u onto u */
    double *utemp;
    utemp = u;
    u = unew;
    unew = utemp;
    //memcpy(u, unew, (N+2)*(N+2)*sizeof(double));
    if (0 == (iter % 10)) {
      res = compute_residual(u, M, hsq);
      get_timestamp(&time2);
      elapsed = timestamp_diff_in_seconds(time1,time2);
      printf("Iter %d Res %g Time %f\n", iter, res,elapsed);
    }
  }

  /* Clean up */
  free(u);
  free(unew);

  /* timing */
  get_timestamp(&time2);
  elapsed = timestamp_diff_in_seconds(time1,time2);
  printf("Time elapsed is %f seconds.\n", elapsed);
  return 0;
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