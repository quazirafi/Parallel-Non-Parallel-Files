#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]){
 int i=0;
printf("Print # 1\n");
#pragma omp parallel
{
omp_set_num_threads(100);
printf("Print #2\n");
dummyMethod1();
#pragma omp parallel for
for(int i=0;i<2;i++) {
 	printf("Print #3\n");
 	}
printf("Print #4\n");
dummyMethod2();
}
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