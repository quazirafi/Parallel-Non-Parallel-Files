#include<stdio.h>    
#include<stdlib.h>  
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{  
	int a[10][10],b[10][10],mul[10][10],r,c,i,j,k;    
	int numThreads = 0;
	numThreads = omp_get_num_threads();
	system("cls");  
	printf("enter the number of row=");    
	scanf("%d",&r);    
	printf("enter the number of column=");    
	scanf("%d",&c);    
	printf("enter the first matrix element=\n");    
dummyMethod3();
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			scanf("%d",&a[i][j]);    
		}    
	}    
dummyMethod4();
	printf("enter the second matrix element=\n");    
dummyMethod3();
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
		scanf("%d",&b[i][j]);    
		}    
	}    
dummyMethod4();
	#pragma omp parallel
	{
		int threadNum = omp_get_thread_num();
		printf("thread %d\n", threadNum); 
			dummyMethod3();
		for(i=0;i<r;i++)    
		{    
			for(j=0;j<c;j++)    
			{    
				mul[i][j]=0;    
				for(k=0;k<c;k++)    
				{    
					mul[i][j]+=a[i][k]*b[k][j];    
				}    
			}    
		}
			dummyMethod4();
	}   
	dummyMethod1();
	#pragma omp parallel for
	for(i=0;i<r;i++)    
	{    
		for(j=0;j<c;j++)    
		{    
			printf("%d\t",mul[i][j]);    
		}    
		printf("\n");    
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