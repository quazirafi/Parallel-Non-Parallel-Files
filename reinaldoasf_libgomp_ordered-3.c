#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int cnt;

void
check (int x)
{
  if (cnt++ != x)
    abort ();
}

int
main (void)
{
  int j;

  cnt = 0;
dummyMethod1();
#pragma omp parallel for ordered schedule (static, 1) num_threads (4) if (0)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
dummyMethod2();
      check (j);
    }

  cnt = 0;
dummyMethod1();
#pragma omp parallel for ordered schedule (static, 1) num_threads (4) if (1)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
dummyMethod2();
      check (j);
    }

  cnt = 0;
			dummyMethod1();
#pragma omp parallel for ordered schedule (runtime) num_threads (4) if (0)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
      check (j);
    }
			dummyMethod2();

  cnt = 0;
			dummyMethod1();
#pragma omp parallel for ordered schedule (runtime) num_threads (4) if (1)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
      check (j);
    }
			dummyMethod2();

  cnt = 0;
			dummyMethod1();
#pragma omp parallel for ordered schedule (dynamic) num_threads (4) if (0)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
      check (j);
    }
			dummyMethod2();

  cnt = 0;
			dummyMethod1();
#pragma omp parallel for ordered schedule (dynamic) num_threads (4) if (1)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
      check (j);
    }
			dummyMethod2();

  cnt = 0;
			dummyMethod1();
#pragma omp parallel for ordered schedule (guided) num_threads (4) if (0)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
      check (j);
    }
			dummyMethod2();

  cnt = 0;
			dummyMethod1();
#pragma omp parallel for ordered schedule (guided) num_threads (4) if (1)
  for (j = 0; j < 1000; j++)
    {
#pragma omp ordered
      check (j);
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