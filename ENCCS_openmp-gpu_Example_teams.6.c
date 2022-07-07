#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void init(float *, float *, int);
extern void output(float *, int);
void vec_mult(float *p, float *v1, float *v2, int N)
{
   int i;
   init(v1, v2, N);
   #pragma omp target teams map(to: v1[0:N], v2[:N]) map(from: p[0:N])
dummyMethod1();
   #pragma omp distribute parallel for simd
   for (i=0; i<N; i++)
     p[i] = v1[i] * v2[i];
   output(p, N);
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