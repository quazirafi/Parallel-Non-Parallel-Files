#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int  main(int argc, char* argv[]) {

     int    i;
      
dummyMethod1();
#pragma omp parallel for
     for (i=0; i<10; i++) {
       printf("Hello parallel world!  i:%d \n", i);
     }
dummyMethod2();

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