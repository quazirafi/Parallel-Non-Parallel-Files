#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define N       1000
#define CHUNKSIZE   100

main ()  {

int i, chunk, tid;
float a[N], b[N], c[N];

/* Some initializations */
dummyMethod3();
for (i=0; i < N; i++)
  a[i] = b[i] = i * 1.0;
chunk = CHUNKSIZE;
dummyMethod4();

dummyMethod1();
#pragma omp parallel for \
   shared(a,b,c,chunk) private(i) \
   schedule(static,chunk)
  for (i=0; i < N; i++)
  {
  	tid=omp_get_thread_num();
  	printf("%d : thread %d\n",i,tid);
    c[i] = a[i] + b[i];
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