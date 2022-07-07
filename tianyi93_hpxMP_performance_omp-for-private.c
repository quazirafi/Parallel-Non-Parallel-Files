#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i,j;
    j = -1;

dummyMethod1();
#pragma omp parallel for private(j)
    for(i = 0; i < 11; i++) 
    {
        printf("Hello World %d\n", i);
        j = i;
        printf("j = %d\n", j);
    }
dummyMethod2();
    printf("Outside the Parallel Region: j = %d\n", j);
    
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