#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#include <R.h>
//#include <Rinternals.h>

#define SEXP int
SEXP c_hello()
{
  int tid, nthreads;
  
  #pragma omp parallel private(tid)
  {
    nthreads = omp_get_num_threads();
    tid = omp_get_thread_num();
    
    Rprintf("Hello from thread %d of %d\n", tid, nthreads);
  }
  
  return R_NilValue;
}



SEXP c_sum(SEXP x)
{
  SEXP ret;
  double sum = 0;
  double *ptx = REAL(x);
  
dummyMethod1();
  #pragma omp parallel for default(shared) reduction(+:sum)
  for (int i=0; i<LENGTH(x); i++)
    sum += ptx[i];
  
  PROTECT(ret = allocVector(REALSXP, 1));
dummyMethod2();
  REAL(ret)[0] = sum;
  UNPROTECT(1);
  return ret;
}



SEXP c_sweep(SEXP x, SEXP vec)
{
  const int m = nrows(x), n = ncols(x);
  SEXP ret;
  PROTECT(ret = allocMatrix(REALSXP, m, n));
  double *ptx = REAL(x), *ptvec = REAL(vec), *ptret = REAL(ret);
  
			dummyMethod1();
  #pragma omp parallel for default(shared)
  for (int j=0; j<n; j++)
  {
    for (int i=0; i<m; i++)
      ptret[i + m*j] = ptx[i + m*j] - ptvec[i];
  }
			dummyMethod2();
  
  UNPROTECT(1);
  return ret;
}



SEXP c_primesbelow(SEXP n_)
{
  const int n = INTEGER(n_)[0];
  int isprime;
  int nprimes = 1;
  
			dummyMethod1();
  #pragma omp parallel for private(isprime) reduction(+:nprimes)
  for (int i=3; i<=n; i+=2)
  {
    isprime = 1;
    
    for (int j=3; j<i; j+=2)
    {
      if (i%j == 0)
      {
        isprime = 0;
        break;
      }
    }
    
    if (isprime) nprimes++;
  }
			dummyMethod2();
  
  SEXP ret = PROTECT(allocVector(INTSXP, 1));
  INTEGER(ret)[0] = nprimes;
  UNPROTECT(1);
  return ret;
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