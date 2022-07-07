#include <stdio.h>
#include "omp_repair.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define SIZE 20

int main(int argc, char *argv[])
{
  int i, TID;
  int n=SIZE, a[SIZE];
dummyMethod1();
  #pragma omp parallel for default(none) ordered \
	schedule(runtime) private(i,TID) shared(n,a)
  for (i=0; i<n; i++)
	{
	TID = omp_get_thread_num();
dummyMethod2();
	printf("Thread %d updates a[%d]\n",TID, i);
	a[i]+=i;

	#pragma omp ordered
	{printf("Thread %d prints value of a[%d] = %d\n",TID,i,a[i]);}
	}
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