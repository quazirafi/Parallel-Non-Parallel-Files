#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void init(float*, float*, int);
extern void init_again(float*, float*, int);
extern void output(float*, int);
void vec_mult(float *p, float *v1, float *v2, int N)
{
   int i;
   init(v1, v2, N);
   #pragma omp target data map(from: p[0:N])
   {
      #pragma omp target map(to: v1[:N], v2[:N])
dummyMethod1();
      #pragma omp parallel for
      for (i=0; i<N; i++)
	p[i] = v1[i] * v2[i];
dummyMethod2();
      init_again(v1, v2, N);
      #pragma omp target map(to: v1[:N], v2[:N])
dummyMethod1();
      #pragma omp parallel for
      for (i=0; i<N; i++)
	p[i] = p[i] + (v1[i] * v2[i]);
dummyMethod2();
   }
   output(p, N);
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