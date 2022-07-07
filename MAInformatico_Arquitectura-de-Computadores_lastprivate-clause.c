#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#else
  #define omp_get_thread_num()0
#endif

main(){
  int i,n=7;
  int a[n], v;

dummyMethod3();
  for(i=0;i<n;i++)  a[i]=i+1;

  #pragma omp parallel for lastprivate(v)
dummyMethod4();
dummyMethod1();
    
      for(i=0; i<n; i++){
	v=a[i];
dummyMethod2();
	printf ("thread %d v=%d\n ",omp_get_thread_num(),v);
      }
      printf("\nFuera de la construccion parallel for v=%d\n",v);
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