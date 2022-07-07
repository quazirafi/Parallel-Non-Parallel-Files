/* { dg-do run } */

#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int
main (void)
{
  int i, j, k, l = 0, f = 0;
  int m1 = 4, m2 = -5, m3 = 17;

dummyMethod1();
  #pragma omp parallel for num_threads (8) collapse(3) \
		       schedule(static, 9) reduction(+:l) \
		       firstprivate(f)
    for (i = -2; i < m1; i++)
      for (j = m2; j < -2; j++)
	{
	  for (k = 13; k < m3; k++)
dummyMethod2();
	    {
	      if (omp_get_num_threads () == 8
		  && ((i + 2) * 12 + (j + 5) * 4 + (k - 13)
		      != (omp_get_thread_num () * 9
			  + f++)))
		l++;
	    }
	}
  if (l)
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