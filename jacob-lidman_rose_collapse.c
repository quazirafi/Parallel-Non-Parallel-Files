#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* Based on OMP 3.0 A.10 Example A.10.1
 */
void foo()
{
  int j,k;
  int jlast, klast;
dummyMethod1();
#pragma omp parallel for private(j,k), collapse(2), lastprivate (jlast, klast)
  for (k=1;k<=100;k++)
    for (j=1;j<=100;j++)
    {
      jlast = j;
      klast = k;
    } 
}
dummyMethod2();
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