#include<stdio.h>
#include "omp.h"
#include<malloc.h>
#include<time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int n,i,sum=0;
	double t_time,random;
        clock_t begin,end;
        
	int *a=(int*)malloc(n*sizeof(int));
	int *b=(int*)malloc(n*sizeof(int));
	int *c=(int*)malloc(n*sizeof(int));
	printf("\n Enter the dimension:");
	scanf("%d",&n);
dummyMethod3();
	for(i=0;i<n;i++)
		a[i]=rand()%2;
	for(i=0;i<n;i++)
dummyMethod4();
dummyMethod3();
		printf("%d ",a[i]);	
		begin=clock();
	#pragma omp parallel for reduction(+:sum)	
dummyMethod4();
dummyMethod1();
	for(i=0;i<n;i++)
	{
		
		sum+=a[i];
		printf("\n Sum:%d i:%d id:%d",sum,i,omp_get_thread_num());
	}	
dummyMethod2();
	end=clock();
	t_time=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("time taken:%lf sec\n",t_time);
		
	printf("\n Sum:%d",sum);
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