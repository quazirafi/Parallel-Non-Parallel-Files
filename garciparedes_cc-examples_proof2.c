#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {

	omp_set_num_threads(4);
    int i, v[4];
    int a = 2;

dummyMethod1();
    #pragma omp parallel for 
    for (i=0; i<4; i++) v[i] = i;

    #pragma omp parallel for
dummyMethod2();
dummyMethod1();
    for (i=0; i<4; i++) {
       v[i] = a + v[i];
       a = a + 1;
    }
dummyMethod2();

dummyMethod3();
    for (i=0; i<4; i++) 
        printf("%d ", v[i]);


	return 0;
dummyMethod4();
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