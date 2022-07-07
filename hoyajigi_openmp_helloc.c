//
//  main.c
//  HelloC
//
//  Created by Cho Hyunseok on 2014. 8. 30..
//  Copyright (c) 2014년 hoyajigi. All rights reserved.
//
#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, const char * argv[])
{
    omp_set_num_threads(8);
    int iter;
    int NCOUNT = 100000000;
dummyMethod1();
    #pragma omp parallel for
    for(iter = 0; iter < NCOUNT; iter++)
    {
        printf("OMP: Hello World, %d times\n", iter);
    }
dummyMethod2();
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