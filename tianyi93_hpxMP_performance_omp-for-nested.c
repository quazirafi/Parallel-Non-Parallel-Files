#include <stdio.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i,j;

dummyMethod1();
#pragma omp parallel for
    for(i = 0; i < 5; i++) {
#pragma omp parallel for firstprivate(i)
dummyMethod2();
        for(j = 0; j < 5; j++) {
            printf("Hello World %d, %d\n",i,j);
        }
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