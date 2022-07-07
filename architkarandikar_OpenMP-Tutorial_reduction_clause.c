#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

main ()  {

int   i, n, chunk, tid;
float a[100], b[100], result;

/* Some initializations */
n = 100;
chunk = 10;
result = 0.0;
dummyMethod3();
for (i=0; i < n; i++)
  {
  a[i] = i * 1.0;
  b[i] = i * 2.0;
  }

#pragma omp parallel for      \
dummyMethod4();
dummyMethod1();
  default(shared) private(i,tid)  \
  schedule(static,chunk)      \
  reduction(+:result)  

  for (i=0; i < n; i++)
  {
    result = result + (a[i] * b[i]);
    tid = omp_get_thread_num();
    printf("%d %d : %f\n",i,tid,result);
  }
dummyMethod2();

printf("Final result= %f\n",result);

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