// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
/* Calcualte the dot product of two vectors*/

/* Include OpenMPheader file */

#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARR_SIZE 1000000000

double a[ARR_SIZE];
double b[ARR_SIZE];
/* Main function */

int main(int *argc, char *argv[] )
{
    
    int i = 0,tid,numt;
    double dot =0;
    double t1,t2;
dummyMethod3();
    for (i=0;i<ARR_SIZE;i++)
    {
        a[i] = i;
        b[i] = i;
    }
dummyMethod4();
    
    
    t1 =omp_get_wtime();
							dummyMethod1();
    #pragma omp parallel for schedule(dynamic,1000) reduction(+:dot)
    for (i=0;i<ARR_SIZE;i++)
    {
        dot +=a[i]*b[i] ;
    }
							dummyMethod2();
    
    
    t2 = omp_get_wtime();
    printf("Dot product of the 2 arrays is : %g. It is calculated in %g s\n",dot, t2-t1);
  
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