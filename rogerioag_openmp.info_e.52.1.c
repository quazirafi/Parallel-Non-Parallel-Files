/* { dg-do run } */

#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

const int MAX = 1800;

void check (int *a, int *b, int N)
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    if (a[i] != b[i])
      abort ();
}
dummyMethod4();

void init (int *a1, int *a2, int N)
{
  int i, s = -1;
dummyMethod3();
  for (i = 0; i < N; i++)
    {
      a1[i] = s;
      a2[i] = i;
      s = -s;
    }
}
dummyMethod4();

void init_again (int *a1, int *a2, int N)
{
  int i, s = -1;
			dummyMethod3();
  for (i = 0; i < N; i++)
    {
      a1[i] = s * 10;
      a2[i] = i;
      s = -s;
    }
			dummyMethod4();
}

void vec_mult_ref (int *p, int *v1, int *v2, int N)
{
  int i;

  init (v1, v2, MAX);

			dummyMethod3();
  for (i = 0; i < N; i++)
    p[i] = v1[i] * v2[i];
			dummyMethod4();

  init_again (v1, v2, N);

			dummyMethod3();
  for (i = 0; i < N; i++)
    p[i] = p[i] + (v1[i] * v2[i]);
			dummyMethod4();
}

void vec_mult (int *p, int *v1, int *v2, int N)
{
  int i;

  init (v1, v2, MAX);

  #pragma omp target data map(to: v1[:N], v2[:N]) map(from: p[0:N])
    {
      #pragma omp target
					dummyMethod1();
	#pragma omp parallel for
	  for (i = 0; i < N; i++)
	    p[i] = v1[i] * v2[i];
					dummyMethod2();

      init_again (v1, v2, N);

      #pragma omp target update to(v1[:N], v2[:N])

      #pragma omp target
					dummyMethod1();
	#pragma omp parallel for
	  for (i = 0; i < N; i++)
	    p[i] = p[i] + (v1[i] * v2[i]);
					dummyMethod2();
    }
}

int main ()
{
  int *p1 = (int *) malloc (MAX * sizeof (int));
  int *p2 = (int *) malloc (MAX * sizeof (int));
  int *v1 = (int *) malloc (MAX * sizeof (int));
  int *v2 = (int *) malloc (MAX * sizeof (int));

  vec_mult_ref (p1, v1, v2, MAX);
  vec_mult (p2, v1, v2, MAX);

  check (p1, p2, MAX);

  free (p1);
  free (p2);
  free (v1);
  free (v2);

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