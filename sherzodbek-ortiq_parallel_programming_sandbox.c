#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double integratingFunction(double x);
int main()
{
    int i;//, thread_id;
    int glob_nloops, priv_nloops;
    glob_nloops = 0;
    double time,start_time;
    start_time = omp_get_wtime();
//    clock_t start, end, iterStart, iterEnd;
    double iterCpuTimeUsed;

    omp_set_dynamic(0);// Explicitly disable dynamic teams
    omp_set_num_threads(2);
    // parallelize this chunk of code

//        iterStart = clock();
//        priv_nloops = 0;

dummyMethod1();
    #pragma omp parallel for private(i) schedule(static) //schedule(dynamic, 100000)// private(priv_nloops) //reduction(+:glob_nloops)
        for (i=0; i<100000000; ++i)
        {
//            ++priv_nloops;
dummyMethod2();
            integratingFunction(100000);
        }
/*    
    #pragma omp parallel for private(i) num_threads(1) //schedule(dynamic, 100000)// private(priv_nloops) //reduction(+:glob_nloops)
        for (i=0; i<100000000; ++i)
        {
//            ++priv_nloops;
            integratingFunction(100000);
        }
*/


//        thread_id = 0;//omp_get_thread_num();

        // parallelize this for loop
//        #pragma omp for schedule(static,100000)
        //glob_nloops += priv_nloops;
    

//        iterEnd = clock();
//        iterCpuTimeUsed = ((double)(iterEnd - iterStart)) / CLOCKS_PER_SEC;
          iterCpuTimeUsed =  omp_get_wtime() - start_time;

    printf("Total # loop iterations is %d\nTime spent: %lf\n", glob_nloops, iterCpuTimeUsed);
    return 0;
}

double integratingFunction(double x){
  double retval=exp(-1*pow(x,2));
  return(retval);
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