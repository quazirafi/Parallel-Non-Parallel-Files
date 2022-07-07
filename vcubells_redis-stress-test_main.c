//
//  main.c
//  omp_for_reduction
//
//  Created by Vicente Cubells Nonell on 03/11/14.
//  Copyright (c) 2014 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, const char * argv[]) {
    
    int n = 1000000;
    
    int suma = 0;
    
    int i;
    
    int numeros[n];
    
dummyMethod1();
    #pragma omp parallel for default(none) shared(n, numeros) private(i)
    for (i = 0; i < n; ++i) {
        numeros[i] = 1;
    }
dummyMethod2();
    
dummyMethod1();
    #pragma omp parallel for default(none) shared(n, numeros) private(i) reduction(+:suma)
    for (i = 0; i < n; ++i) {
            suma += numeros[i];
    }
dummyMethod2();
    
    printf("La suma total es = %d\n", suma);
    
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