#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i,j;

    printf("loop 1: stride of -1, 10 - 0\n");
dummyMethod1();
#pragma omp parallel for 
    for(i = 10; i > 0; i--) 
    {
        printf("Hello world %d\n",i);
    }
dummyMethod2();

    printf("loop 2: stride of -1, 10 - -1\n");
dummyMethod1();
#pragma omp parallel for 
    for(i = 10; i > -1; i--) 
    {
        printf("Hello world %d\n",i);
    }
dummyMethod2();

    printf("loop 3: stride of -2, 10 - 0\n");
dummyMethod1();
#pragma omp parallel for 
    for(i = 10; i > 0; i -= 2) 
    {
        printf("Hello world %d\n",i);
    }
dummyMethod2();

    printf("loop 4: stride of -2, 10 - -1\n");
dummyMethod1();
#pragma omp parallel for 
    for(i = 10; i > -1; i -= 2) 
    {
        printf("Hello world %d\n",i);
    }
dummyMethod2();

    //stride larger than range
    //range less than num_threads
    //
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