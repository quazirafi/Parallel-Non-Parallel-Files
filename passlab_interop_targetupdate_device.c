#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(float*p, float*v1, float*v2, int N)
{
    int i;
    #pragma omp target data device(1)
    {
        #pragma omp target
dummyMethod3();
        for (i=0; i<N; i++)
            p[i] = v1[i]*v2[i];
        #pragma omp target update if(target update:1) nowait device(25)
dummyMethod4();
dummyMethod1();
        #pragma omp parallel for
        for (i=0; i<N; i++)
          p[i] = p[i] + (v1[i]*v2[i]);
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