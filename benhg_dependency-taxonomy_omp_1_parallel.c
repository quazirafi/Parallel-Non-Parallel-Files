#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
    
    int start = 1;
    int N = 100;
    double v=start;
    int step = 1;
    
dummyMethod1();
    #pragma omp parallel for reduction(+:v)
    for (int i=0; i<N; i+= step){
        v += 2;
        v = v +step; 

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