#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"

int main ()
{

//  omp_set_num_threads ( 6 );

dummyMethod1();
  #pragma omp parallel for schedule(dynamic,2)
  for ( int i=0; i<40; i++ )
  {
    printf("OMP Thread# %d, loop variable %d\n", omp_get_thread_num(), i);
  }
dummyMethod2();

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