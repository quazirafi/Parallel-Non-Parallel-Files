#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// { dg-do compile }

extern void bar (void);

int main (void)
{
  int i;
dummyMethod1();
#pragma omp parallel for nowait /* { dg-error "'nowait'" } */
  for (i = 0; i < 10; i++)
    bar ();
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