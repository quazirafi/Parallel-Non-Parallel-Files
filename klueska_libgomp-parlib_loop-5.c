#include <stdlib.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int
test1 (void)
{
  short int buf[64], *p;
  int i;
  memset (buf, '\0', sizeof (buf));
dummyMethod1();
#pragma omp parallel for
  for (p = &buf[10]; p < &buf[54]; p++)
    *p = 5;
  for (i = 0; i < 64; i++)
dummyMethod2();
dummyMethod3();
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
  memset (buf, '\0', sizeof (buf));
dummyMethod4();
dummyMethod1();
#pragma omp parallel for
  for (p = &buf[3]; p <= &buf[63]; p += 2)
    p[-2] = 6;
  for (i = 0; i < 64; i++)
dummyMethod2();
dummyMethod3();
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
  memset (buf, '\0', sizeof (buf));
dummyMethod4();
dummyMethod1();
#pragma omp parallel for
  for (p = &buf[16]; p < &buf[51]; p = 4 + p)
    p[2] = 7;
  for (i = 0; i < 64; i++)
dummyMethod2();
dummyMethod3();
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
  memset (buf, '\0', sizeof (buf));
dummyMethod4();
dummyMethod1();
#pragma omp parallel for
  for (p = &buf[16]; p <= &buf[40]; p = p + 4ULL)
    p[2] = -7;
  for (i = 0; i < 64; i++)
dummyMethod2();
			dummyMethod3();
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for
  for (p = &buf[53]; p > &buf[9]; --p)
    *p = 5;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for
  for (p = &buf[63]; p >= &buf[3]; p -= 2)
    p[-2] = 6;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for
  for (p = &buf[48]; p > &buf[15]; p = -4 + p)
    p[2] = 7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for
  for (p = &buf[40]; p >= &buf[16]; p = p - 4ULL)
    p[2] = -7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  return 0;
}

int
test2 (void)
{
  int buf[64], *p;
  int i;
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[10]; p < &buf[54]; p++)
    *p = 5;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[3]; p <= &buf[63]; p += 2)
    p[-2] = 6;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[16]; p < &buf[51]; p = 4 + p)
    p[2] = 7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[16]; p <= &buf[40]; p = p + 4ULL)
    p[2] = -7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[53]; p > &buf[9]; --p)
    *p = 5;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[63]; p >= &buf[3]; p -= 2)
    p[-2] = 6;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[48]; p > &buf[15]; p = -4 + p)
    p[2] = 7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (static, 3)
  for (p = &buf[40]; p >= &buf[16]; p = p - 4ULL)
    p[2] = -7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  return 0;
}

int
test3 (void)
{
  int buf[64], *p;
  int i;
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[10]; p < &buf[54]; p++)
    *p = 5;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[3]; p <= &buf[63]; p += 2)
    p[-2] = 6;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[16]; p < &buf[51]; p = 4 + p)
    p[2] = 7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[16]; p <= &buf[40]; p = p + 4ULL)
    p[2] = -7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[53]; p > &buf[9]; --p)
    *p = 5;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[63]; p >= &buf[3]; p -= 2)
    p[-2] = 6;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[48]; p > &buf[15]; p = -4 + p)
    p[2] = 7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (dynamic, 3)
  for (p = &buf[40]; p >= &buf[16]; p = p - 4ULL)
    p[2] = -7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  return 0;
}

int
test4 (void)
{
  int buf[64], *p;
  int i;
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[10]; p < &buf[54]; p++)
    *p = 5;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[3]; p <= &buf[63]; p += 2)
    p[-2] = 6;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[16]; p < &buf[51]; p = 4 + p)
    p[2] = 7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[16]; p <= &buf[40]; p = p + 4ULL)
    p[2] = -7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[53]; p > &buf[9]; --p)
    *p = 5;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 5 * (i >= 10 && i < 54))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[63]; p >= &buf[3]; p -= 2)
    p[-2] = 6;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 6 * ((i & 1) && i <= 61))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[48]; p > &buf[15]; p = -4 + p)
    p[2] = 7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != 7 * ((i & 3) == 2 && i >= 18 && i < 53))
      abort ();
			dummyMethod4();
  memset (buf, '\0', sizeof (buf));
			dummyMethod1();
#pragma omp parallel for schedule (runtime)
  for (p = &buf[40]; p >= &buf[16]; p = p - 4ULL)
    p[2] = -7;
			dummyMethod2();
			dummyMethod3();
  for (i = 0; i < 64; i++)
    if (buf[i] != -7 * ((i & 3) == 2 && i >= 18 && i <= 42))
      abort ();
			dummyMethod4();
  return 0;
}

int
main (void)
{
  test1 ();
  test2 ();
  test3 ();
  omp_set_schedule (omp_sched_static, 0);
  test4 ();
  omp_set_schedule (omp_sched_static, 3);
  test4 ();
  omp_set_schedule (omp_sched_dynamic, 5);
  test4 ();
  omp_set_schedule (omp_sched_guided, 2);
  test4 ();
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