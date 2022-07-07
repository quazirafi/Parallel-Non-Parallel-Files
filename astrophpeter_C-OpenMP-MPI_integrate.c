#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double trapz_serial(double* fvals, double* x, int N)
{
  double sum = 0.0;

dummyMethod3();
  for ( int i=0; i < N-1;++i) 
  {
   sum += (x[i+1]-x[i]) * (fvals[i]+fvals[i+1]);    
  }
dummyMethod4();
  
  return sum / 2.0;
}


double trapz_parallel(double* fvals, double* x, int N, int num_threads)
{
   double sum = 0.0;

dummyMethod1();
   #pragma omp parallel for reduction(+:sum) num_threads(num_threads) 
   for ( int i=0; i < N-1;++i)
   {
     sum += (x[i+1]-x[i]) * (fvals[i]+fvals[i+1]);
   }    
dummyMethod2();
   return sum / 2.0;
}


double time_trapz_parallel(double* fvals, double* x, int N, int num_threads)
{
  double end, start = omp_get_wtime();
  trapz_parallel(fvals, x, N, num_threads);
  end = omp_get_wtime();
  return (end - start);
}


double simps_serial(double* fvals, double* x, int N)
{
  double sum = 0.0;

			dummyMethod3();
  for ( int i =0 ; i < N-2; i+=2) 
  {
     sum += (x[i+2]-x[i])*(fvals[i]+4*fvals[i+1]+fvals[i+2]);
  } 
			dummyMethod4();
  
  sum /= 6.0;

  if ( N % 2 == 0) 
  {
    sum+= 0.5* (x[N-1]-x[N-2]) * (fvals[N-2]+fvals[N-1]);
  }

  return sum;  
}


double simps_parallel(double* fvals, double* x, int N, int num_threads)
{
  double sum = 0.0;

			dummyMethod1();
  #pragma omp parallel for reduction(+:sum) schedule(static, 1024)  num_threads(num_threads)
  for ( int i =0 ; i < N-2; i+=2)
  {
     sum += (x[i+2]-x[i])*(fvals[i]+4*fvals[i+1]+fvals[i+2]);
  }
			dummyMethod2();
  sum /= 6.0;

  if ( N % 2 == 0)
  {
    sum+= 0.5* (x[N-1]-x[N-2]) * (fvals[N-2]+fvals[N-1]);
  }

  return sum;


}


double time_simps_parallel(double* fvals, double* x, int N, int num_threads,
                           int repeat)
{
  double end, start = omp_get_wtime();
			dummyMethod3();
  for (int i=0; i<repeat; ++i)
    simps_parallel(fvals, x, N, num_threads);
			dummyMethod4();
  end = omp_get_wtime();
  return (end - start) / (double)repeat;
}


double simps_parallel_chunked(double* fvals, double* x, int N,
                              int num_threads, int chunk_size)
{
  double sum = 0.0;

			dummyMethod1();
  #pragma omp parallel for reduction(+:sum) schedule(dynamic, chunk_size) num_threads(num_threads)
  for ( int i =0 ; i < N-2; i+=2)
  {  
     sum += (x[i+2]-x[i])*(fvals[i]+4*fvals[i+1]+fvals[i+2]);
  }
			dummyMethod2();
  sum /= 6.0;
  
  if ( N % 2 == 0)
  { 
    sum+= 0.5* (x[N-1]-x[N-2]) * (fvals[N-2]+fvals[N-1]);
  }
  
  return sum;;
}


double time_simps_parallel_chunked(double* fvals, double* x, int N,
                                   int num_threads, int chunk_size,
                                   int repeat)
{
  double end, start = omp_get_wtime();
			dummyMethod3();
  for (int i=0; i<repeat; ++i)
    simps_parallel_chunked(fvals, x, N, num_threads, chunk_size);
			dummyMethod4();
  end = omp_get_wtime();
  return (end - start) / (double)repeat;
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