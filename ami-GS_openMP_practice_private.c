#include <stdio.h>
#include "omp.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

main(int argc, char *argv[]) {

  int nthreads, threadID;

  int ans = 0;
  int i , j;
  // this can avoid inner loop index to be shared
dummyMethod1();
#pragma omp parallel for private(j) num_threads(3)
  for (i = 0; i < 10; i++) {
    for(j = 0; j < 10; j++) {
      ans = i + j;
    }
  }
dummyMethod2();

#pragma omp parallel private(threadID)
  {
    threadID = omp_get_thread_num();
    usleep(10000);
    printf("this is thread ID = %d\n", threadID);

    if (threadID == 0) 
      {
	nthreads = omp_get_num_threads();
	printf("Number of threads = %d\n", nthreads);
      }
  }

  printf("\n\n");
  int t_ID;
#pragma omp parallel
  {
    t_ID = omp_get_thread_num();
    usleep(10000);
    printf("this is thread ID = %d\n", t_ID);

    if (t_ID == 0) 
      {
	nthreads = omp_get_num_threads();
	printf("Number of threads = %d\n", nthreads);
      }
  }

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