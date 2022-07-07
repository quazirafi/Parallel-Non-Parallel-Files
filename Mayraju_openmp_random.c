#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int lower = 50,upper = 500;
	int count = 10;
	int arr[10];
dummyMethod1();
  #pragma omp  parallel for
  
		for(int i=0;i<10;i++)
		{
			printf(" the thread executing random number %d and index %d\n", omp_get_thread_num(),i);
			int num = (rand() % (upper-lower+1)) + lower;
			arr[i] = num;
			printf("%d and thread number %d \n",arr[i],omp_get_thread_num());
		}
dummyMethod2();
   
dummyMethod3();
		for(int i=0;i<10;i++)
		{
			printf("%d  ",arr[i]);
		}
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