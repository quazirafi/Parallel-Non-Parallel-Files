// This program demonstrates "Data parallel computation and Loops"
// Refer: William Gropp, Illinois.

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

main()
{
  int i;
  omp_set_num_threads(6);
dummyMethod1();
  #pragma omp parallel for
  for (i=0;i<(omp_get_num_threads());i++)
  {
    int id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    printf("Hi. I'm thread %d of %d \n", id, nt);
  }
dummyMethod2();
  #pragma omp master
  {
    printf("Hey... I print once only.. \n");
  }
}

// Compare the results from above code (parallel for) with the code given below (parallel).
// One can notice that the task given with in the parallel region is simply repeated by each threads (in below code)
// But if we use (given above) "parallel for", each thread split up the task among themselves and execute it.
// ALso, one can notice that "no. of (times) task executed is not equal to no. of threads". This can be noticed by printing results.


////////////// SERIAL Version //////////////////////
// main()
// {
//   int i;
//   omp_set_num_threads(6);
//   #pragma omp parallel //for
//   // for (i=0;i<(omp_get_num_threads());i++)
//   {
//     int id = omp_get_thread_num();
//     int nt = omp_get_num_threads();
//     printf("Hi. I'm thread %d of %d \n", id, nt);
//     #pragma omp master
//     {
//       printf("Hey... I print once only.. \n");
//     }
//   }
// }
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