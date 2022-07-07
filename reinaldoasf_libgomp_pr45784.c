#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* PR c/45784 */
/* { dg-do run } */

void
foo (int n)
{
  char *p, vla[2 * n];
  int i;
dummyMethod1();
  #pragma omp parallel for
  for (p = vla; p < vla + (sizeof (vla) / sizeof (vla[0])); p++)
    *p = ' ';
  #pragma omp parallel for
dummyMethod2();
dummyMethod1();
  for (i = 0; i < 2 * n; i++)
    if (vla[i] != ' ')
      __builtin_abort ();
}
dummyMethod2();

void
bar (int n)
{
  char *p, vla1[n], vla2[n * 2], vla3[n * 3], vla4[n * 4];
  int i;
  __builtin_memset (vla4, ' ', n * 4);
dummyMethod1();
  #pragma omp parallel for
  for (p = vla4 + sizeof (vla1); p < vla4 + sizeof (vla3) - sizeof (vla2) + sizeof (vla1); p += sizeof (vla4) / sizeof (vla4))
    p[0] = '!';
  #pragma omp parallel for
dummyMethod2();
dummyMethod1();
  for (i = 0; i < n * 4; i++)
    if (vla4[i] != ((i >= n && i < 2 * n) ? '!' : ' '))
      __builtin_abort ();
}
dummyMethod2();

int
main ()
{
  volatile int n;
  n = 128;
  foo (n);
  bar (n);
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