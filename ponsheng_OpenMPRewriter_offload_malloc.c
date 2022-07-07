#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10
int offload(int *a,int n) {
    long long sum = 0;
    
dummyMethod3();
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
dummyMethod4();

dummyMethod3();
    for (int i =0; i < n; i++) {
        printf("%d ", a[i]);
    }
dummyMethod4();
dummyMethod1();
#pragma omp target teams distribute parallel for
    for (int i = 0; i < n; i++) {
        a[i] = i + a[i];
    }
dummyMethod2();
dummyMethod3();
    for (int i =0; i < n; i++) {
        printf("%d ", a[i]);
        sum += a[i];
    }
dummyMethod4();

    printf("SUM: %lld\n", sum);
    return  0;
}

int main() {
    int *a = (int*)malloc(sizeof(int)*N);
	offload(a,N);
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