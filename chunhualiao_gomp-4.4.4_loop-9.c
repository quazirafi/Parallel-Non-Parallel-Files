#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void abort (void);

char buf[8] = "01234567";
char buf2[8] = "23456789";

int
main (void)
{
  char *p, *q;
  int sum = 0;
dummyMethod1();
  #pragma omp parallel for collapse (2) reduction (+:sum) lastprivate (p, q)
  for (p = buf; p < &buf[8]; p++)
    for (q = &buf2[0]; q <= buf2 + 7; q++)
      sum += (*p - '0') + (*q - '0');
  if (p != &buf[8] || q != buf2 + 8 || sum != 576)
dummyMethod2();
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