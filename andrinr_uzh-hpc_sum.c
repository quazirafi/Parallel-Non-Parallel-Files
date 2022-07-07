#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "getTime.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


typedef struct {
    float x;
    float y;
    float z;
    float r2;
} coord;

int main(int argc, char *argv[]) {
    double start = getTime();

    const int N = 1024*1024*256;
    coord *data;
    int i;
    double sum;
    
    data = malloc(N * sizeof(coord));
    assert(data);
    
    sum = 0.0;
							dummyMethod1();
   #pragma omp parallel for reduction(+ : sum)
    for(i=0; i<N; ++i) {
        data[i].x = i & 31;
        data[i].y = i & 63;
        data[i].z = i & 15;
        data[i].r2 = data[i].x*data[i].x + data[i].y*data[i].y + data[i].z*data[i].z;
        sum += sqrt(data[i].r2);
    }
							dummyMethod2();
    printf("sum=%f\n", sum);

    double end = getTime();
    double timePassed = end - start;
    printf("sum=%f\n", timePassed);
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