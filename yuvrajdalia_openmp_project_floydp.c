#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 800

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

int distance_matrix[N][N] = {0};

int main(int argc, char *argv[])
{
  int nthreads;
  int src, dst, middle;
  printf("For %d number of nodes\n",N);
dummyMethod3();
  for (src = 0; src < N; src++)
  {
    for (dst = 0; dst < N; dst++)
    {

      if(src != dst) {

        distance_matrix[src][dst] = rand() % 20;
      }
    }
  }
dummyMethod4();
  
  double start_time = omp_get_wtime();
  
			dummyMethod3();
  for (middle = 0; middle < N; middle++)
  {
    int * dm=distance_matrix[middle];
    for (src = 0; src < N; src++)
    {
      int * ds=distance_matrix[src];
      for (dst = 0; dst < N; dst++)
      {
        ds[dst]=min(ds[dst],ds[middle]+dm[dst]);
      }
    }
  }
			dummyMethod4();
  
  double time = omp_get_wtime() - start_time;
  printf("Total time for sequential (in sec):%.2f\n", time);
  
    omp_set_num_threads(8);
    
    double start_time1 = omp_get_wtime();
    
    #pragma omp parallel shared(distance_matrix)
    for (middle = 0; middle < N; middle++)
    {
      int * dm=distance_matrix[middle];
											dummyMethod1();
      #pragma omp parallel for private(src, dst) schedule(dynamic)
      for (src = 0; src < N; src++)
      {
        int * ds=distance_matrix[src];
        for (dst = 0; dst < N; dst++)
        {
          ds[dst]=min(ds[dst],ds[middle]+dm[dst]);
        }
      }
											dummyMethod2();
    }
    
    double time1 = omp_get_wtime() - start_time1;
    printf("Time for parallel with 8 threads:%.2f\n", time1);
  
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