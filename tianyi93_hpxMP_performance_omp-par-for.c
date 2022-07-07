#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i = 0;
dummyMethod1();
#pragma omp parallel for
    for(i = 0; i < 10; i++)
    {
        printf("Hello World #%d\n", i );
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