#include "omp.h"
#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
	int n;
	printf("Enter Number of Objects:");
	scanf("%d",&n);
	int ar[n];
  	
  	printf("Enter array:");
dummyMethod3();
	for(int i=0; i<n; i++)
  		scanf("%d",&ar[i]);
  
  	int even=0,odd=0;
dummyMethod1();
  	#pragma omp parallel for
  	for(int i=0;i<n;i++)
  	{
  		if(ar[i]%2==0)
  			even=even+ar[i];
  		else
  			odd=odd+ar[i];
  	}
dummyMethod2();
  	printf("\nEven numbers sum: %d",even);
  	printf("\nOdd numbers sum: %d\n",odd);
}
dummyMethod4();
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