#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
/**
 * @brief Illustrates the OpenMP lastprivate policy.
 * @details This example shows that when a lastprivate variable is passed to a
 * parallelised for loop, threads work on uninitialised copies but, at the end
 * of the parallelised for loop, the thread in charge of the last iteration
 * sets the value of the original variable to that of its own copy.
 **/
int main(int argc, char* argv[])
{
    // Use 4 OpenMP threads
    omp_set_num_threads(4);
 
    // Variable that will be lastprivate
    int val = 123456789;
 
    printf("Value of \"val\" before the OpenMP parallel region: %d.\n", val);
 
dummyMethod1();
    #pragma omp parallel for lastprivate(val)
    for(int i = 0; i < (omp_get_num_threads()*2); i++)
    {
  
        val = omp_get_thread_num();
       
    }
dummyMethod2();
 
    // Value after the parallel region; unchanged.
    printf("Value of \"val\" after the OpenMP parallel region: %d. Thread %d was therefore the last one to modify it.\n", val, val);
 
    return EXIT_SUCCESS;
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