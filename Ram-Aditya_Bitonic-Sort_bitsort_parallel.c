//This program sorts a bitonic sequence of n elements(where n is power of 2) 

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();



void comp_swap(int a[], int i, int j, int asc)
{
    if (asc==(a[i]>a[j]))
      {  int temp;
	 temp=a[i];
	 a[i]=a[j];
	 a[j]=temp;
      }
}


void bit_merge(int a[], int low, int n, int asc)
{
        int k=n/2;
	omp_set_num_threads(omp_get_max_threads());
dummyMethod1();
	#pragma omp parallel for
        for (int i=low; i<low+k; i++)
            comp_swap(a, i, i+k, asc);
}
dummyMethod2();





int main()
{
    
    int a[256],loop,n,asc,merge_calls,low,i,n1;
    printf("Enter number of elements(Power of 2)\n");
    scanf("%d",&n);
    n1=n;	
    printf("Enter the  elements of bitonic sequence\n");
							dummyMethod3();
    for(loop=0;loop<n;loop++)
       scanf("%d",&a[loop]);
							dummyMethod4();
    printf("Enter 1.Ascending(1) or 2.Descending(0)\n");
	scanf("%d",&asc);
   

    merge_calls=1;

    while(n>1)
    {   
	omp_set_num_threads(omp_get_max_threads());
	dummyMethod1();
	#pragma omp parallel for
	for(i=0;i<merge_calls;i++)
	{	low=(n)*i;
		bit_merge(a,low,n,asc);
	}	
	dummyMethod2();
	
	merge_calls=2*merge_calls;
	n=n/2;
    }	
   
    printf("Sorted array: \n");
							dummyMethod3();
    for (loop=0; loop<n1; loop++)
        printf("%d ", a[loop]);
							dummyMethod4();
   
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