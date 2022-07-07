#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR middle-end/35196 */
/* { dg-do run } */

extern void abort (void);
extern void omp_set_dynamic (int);

int
main (void)
{
  int i, j;
  omp_set_dynamic (0);
dummyMethod1();
#pragma omp parallel for lastprivate (i, j) num_threads (8) schedule (static)
  for (i = 0; i < 5; i++)
    j = i;
  if (i != 5 || j != 4)
dummyMethod2();
    abort ();
dummyMethod1();
#pragma omp parallel for lastprivate (i, j) num_threads (8) schedule (static, 2)
  for (i = 0; i < 5; i++)
    j = i;
  if (i != 5 || j != 4)
dummyMethod2();
    abort ();
dummyMethod1();
#pragma omp parallel for lastprivate (i, j) num_threads (8) schedule (dynamic)
  for (i = 0; i < 5; i++)
    j = i;
  if (i != 5 || j != 4)
dummyMethod2();
    abort ();
dummyMethod1();
#pragma omp parallel for lastprivate (i, j) num_threads (8) schedule (static)
  for (i = -12; i < 21; i += 3)
    j = i;
  if (i != 21 || j != 18)
dummyMethod2();
    abort ();
			dummyMethod1();
#pragma omp parallel for lastprivate (i, j) num_threads (8) schedule (static, 2)
  for (i = -12; i < 21; i += 3)
    j = i;
			dummyMethod2();
  if (i != 21 || j != 18)
    abort ();
			dummyMethod1();
#pragma omp parallel for lastprivate (i, j) num_threads (8) schedule (dynamic, 3)
  for (i = -12; i < 21; i += 3)
    j = i;
			dummyMethod2();
  if (i != 21 || j != 18)
    abort ();
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