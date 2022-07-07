#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

main()
{
  int i;
  int x = 0; 
  omp_set_num_threads(6);
  
dummyMethod1();
  #pragma omp parallel for private(i) shared(x)
  for (i=0;i<10;i++)
  {
    printf("OMP Thread# %d, i++=%d, x++=%d\n", omp_get_thread_num(), i++, x++);
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