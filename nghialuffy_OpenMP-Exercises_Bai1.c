// OpenMP header 
#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
  
int main(int argc, char* argv[]) 
{ 
dummyMethod1();
    #pragma omp parallel for
    for(int i=0;i<10;i++){
        printf("%i\n",i);
    }
dummyMethod2();
    printf("Hello world");
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