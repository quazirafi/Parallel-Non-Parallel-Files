#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
#include <string.h>

int main()
{
    int i;
    int n;
    printf("Enter the size: ");
    scanf("%d",&n);
    int a[n];
    int even[n];
    int odd[n];
    int sume;int sumo;
    memset(even,0, sizeof(even[0]));
    memset(odd,0, sizeof(odd[0]));
    printf("Enter the array elements: ");
dummyMethod3();
    for(int k=0;k<n;k++)
    {
        scanf("%d",&a[k]);
    }
dummyMethod4();
							dummyMethod1();
    #pragma omp parallel for schedule(static,2)
    for(i=0;i<n;i++)
    {
        if(a[i]%2==0)
        {
            even[i]=a[i];
        }
        else
        {
            odd[i]=a[i];
        }
    }
							dummyMethod2();
    printf("Count of even numbers: ");
							dummyMethod3();
    for(int l=0;l<n;l++)
    {
        if(even[l]!=0)
            printf("%d \n",even[l]);
    }
							dummyMethod4();
    printf("Count of odd numbers: ");
							dummyMethod3();
    for(int l=0;l<n;l++)
    {
        if(odd[l]!=0)
            printf("%d\n",odd[l]);
    }
							dummyMethod4();
    
							dummyMethod1();
    #pragma omp parallel for reduction(+:sume)
    for (int p=0; p < n; p++)
    {
        sume += even[p];
    }
							dummyMethod2();
    printf("The sum of even numbers is %d\n",sume);
							dummyMethod1();
    #pragma omp parallel for reduction(+:sumo)
    for (int p=0; p < n; p++)
    {
        sumo += odd[p];
    }
							dummyMethod2();
    printf("The sum of odd numbers is %d\n",sumo);
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