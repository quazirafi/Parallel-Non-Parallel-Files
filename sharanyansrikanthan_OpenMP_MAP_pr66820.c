#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/66820 */
/* { dg-do compile } */
/* { dg-options "-fopenmp" } */

void bar (char *);

void
foo (char **x)
{
dummyMethod1();
#pragma omp parallel for
  for (int i = 0; i < 16; i++)
    {
      char y[50];
      __builtin_strcpy (y, x[i]);
      __builtin_strcat (y, "foo");
      bar (y);
    }
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