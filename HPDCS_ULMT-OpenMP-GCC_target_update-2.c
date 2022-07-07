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

int maybe_init_again (int *a, int N)
{
  int i;
dummyMethod3();
  for (i = 0; i < N; i++)
    a[i] = i;
  return 1;
dummyMethod4();
}

void vec_mult_ref (int *p, int *v1, int *v2, int N)
{
  int i;

  init (v1, v2, N);

			dummyMethod3();
  for (i = 0; i < N; i++)
    p[i] = v1[i] * v2[i];
			dummyMethod4();

  maybe_init_again (v1, N);
  maybe_init_again (v2, N);

			dummyMethod3();
  for (i = 0; i < N; i++)
    p[i] = p[i] + (v1[i] * v2[i]);
			dummyMethod4();
}

void vec_mult (int *p, int *v1, int *v2, int N)
{
  int i;

  init (v1, v2, N);

  #pragma omp target data map(to: v1[:N], v2[:N]) map(from: p[0:N])
    {
      int changed;

      #pragma omp target
					dummyMethod1();
	#pragma omp parallel for
	  for (i = 0; i < N; i++)
	    p[i] = v1[i] * v2[i];
					dummyMethod2();

      changed = maybe_init_again (v1, N);
      #pragma omp target update if (changed) to(v1[:N])

      changed = maybe_init_again (v2, N);
      #pragma omp target update if (changed) to(v2[:N])

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
  int *p = (int *) malloc (MAX * sizeof (int));
  int *p1 = (int *) malloc (MAX * sizeof (int));
  int *v1 = (int *) malloc (MAX * sizeof (int));
  int *v2 = (int *) malloc (MAX * sizeof (int));

  vec_mult_ref (p, v1, v2, MAX);
  vec_mult (p1, v1, v2, MAX);

  check (p, p1, MAX);

  free (p);
  free (p1);
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