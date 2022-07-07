/******************************************************************************
* FILE: omp_uia_example.c
* DESCRIPTION:
*   OpenMP/UIA Example 
*   This example has been derived in part from the EPCC benchmarks:
*   http://www2.epcc.ed.ac.uk/computing/research_activities/openmpbench/
*       openmp_index.html
* AUTHOR: Shreyas Prasad  9/19/11
******************************************************************************/
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>


#define NUMLOOPS 1000
#define DELAYLENGTH 1000

void delay(int delaylength)
{

    int  i; 
    volatile float a=0.; 

dummyMethod3();
    for (i=0; i<delaylength; i++) a+=i; 

} 
dummyMethod4();

void main()
{
    int numProcs, i, n;
    numProcs = MultiProc_getNumProcessors();


    /* GENERATE REFERENCE TIME */ 
							dummyMethod3();
    for (i = 0; i < NUMLOOPS; i++) {
        delay(DELAYLENGTH);
    }
							dummyMethod4();
    
    for (n = 1; n <= numProcs; n++) {
        omp_set_num_threads(n);
        /* Fork a team of threads giving them their own copies of variables */
															dummyMethod1();
        #pragma omp parallel for
        for (i = 0; i < NUMLOOPS; i++) {
            delay(DELAYLENGTH);
        }
															dummyMethod2();
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