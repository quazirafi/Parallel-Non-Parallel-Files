#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern void abort (void);

int
main()
{
  int i, a;

  a = 30;

dummyMethod1();
#pragma omp parallel for firstprivate (a) lastprivate (a) \
	num_threads (2) schedule(static)
  for (i = 0; i < 10; i++)
    a = a + i;

  /* The thread that owns the last iteration will have computed
dummyMethod2();
     30 + 5 + 6 + 7 + 8 + 9 = 65.  */
  if (a != 65)
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