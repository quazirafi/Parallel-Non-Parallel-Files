#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */

extern int omp_get_num_threads (void);
void work (int i);
void
incorrect ()
{
  int np, i;
  np = omp_get_num_threads ();	/* misplaced */
dummyMethod1();
#pragma omp parallel for schedule(static)
  for (i = 0; i < np; i++)
    work (i);
}
dummyMethod2();
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