#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define size 10
int i, j, k;

int
main ()
{
  char *s = __builtin_malloc (size + 1);

#pragma omp target teams
  {
dummyMethod1();
#pragma omp distribute parallel for default(none) private(i) shared(s)
    for (i = 0; i < size; ++i)
      {
	char *buffer = __builtin_alloca (10);
dummyMethod2();
	buffer[5] = 97 + i;
	s[i] = buffer[5];
      }
  }

dummyMethod3();
  for (i = 0; i < size; ++i)
    if (s[i] != 97 + i)
      __builtin_abort ();

  return 0;
dummyMethod4();
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