#include<stdio.h> 
#include<stdlib.h>
#include<time.h>
#include<math.h> 
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() 
{
	int i,j, ele,left,right,n, s[20],arr[20],interval,index,tid; 
	int k=2, flag=0;
	printf("Enter the length of array\n");
	scanf("%d",&n);
	printf("Enter the elements of the sorted array in ascending order\n");
dummyMethod3();
	for(i=0;i<n;i++) 
	{
		scanf("%d",&arr[i]); 
	}
dummyMethod4();
	printf("Enter the element to be searched\n"); 
	scanf("%d",&ele);

	left=0; right=n-1;
	double start_time = clock();
	#pragma omp parallel num_threads(2) private(i) 
	{
		tid = omp_get_thread_num(); 
		#pragma omp for
dummyMethod3();
			for(i=0; i<n; i++)
			if(arr[i] == ele) 
dummyMethod4();
			{
				printf("LINEAR SEARCH:\nElement found at position = %d by thread %d \n", i+1, tid); 
			}
	}
	double end_time = clock();
	double result_time = (end_time - start_time) / CLOCKS_PER_SEC; 
	printf("Time for linear search: %f\n", result_time);
	
	printf("\nBINARY SEARCH:");
	start_time = clock();
	if(ele>=arr[left] && ele<=arr[right])
	{ 
		while(left!=right) 
		{
			if(n<=k)
			{
							dummyMethod1();
				#pragma omp parallel for num_threads(n) 
				for(i=0;i<n;i++)
				{
					s[i]=left+i;
					tid=omp_get_thread_num();
					printf("Thread number %d allocated s[%d]=%d\n",tid,i,s[i]);
				}
							dummyMethod2();
			 }
	else
	{
		s[0]=left; 
		interval=ceil((float)n/(float)k);
			dummyMethod1();
		#pragma omp parallel for num_threads(k-1) 
		for(i=1;i<=k-1;i++)
		{
			s[i]=left+interval*i-1;
			tid=omp_get_thread_num();
			printf("Thread number %d allocated s[%d]=%d\n",tid,i,s[i]);
		}
			dummyMethod2();
		s[n]=right; 
	}
	dummyMethod3();
	for(i=0;i<=n;i++) 
	{
		if(ele==arr[s[i]]) 
		{
			index=s[i];
			printf("Element found at position %d\n",index+1); 
			flag=1;
			break;
		} 
		if(ele<arr[s[i]])
		{ 
			right=s[i]; 
			if(i!=0)
			{
				left=1+s[i-1]; 
			}
		n=right-left+1;
		break; 
		}
	}
	dummyMethod4();

	if(flag==1) 
	break;
	} 
	}
if(left==right || !(ele>=arr[left] && ele<=arr[right])) 
printf("Element is not present in the list\n");
end_time = clock();
result_time = (end_time - start_time) / CLOCKS_PER_SEC; 
printf("Time for binary search: %f\n", result_time);
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