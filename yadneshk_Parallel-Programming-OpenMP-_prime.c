#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
    int prime[100000],i,j,n;
    printf("\nIn order to find prime numbers from 1 to n, enter the value of n:");
    scanf("%d",&n);
dummyMethod3();
    for(i=1;i<=n;i++)
    {
        prime[i]=1;
    }
dummyMethod4();
    prime[1]=0;
    for(i=2;i*i<=n;i++)
    {
             /* multi-threading to remove multiples of prime number i from the list (array) */

dummyMethod1();
            #pragma omp parallel for
            for(j=i*i;j<=n;j=j+i)
              {
                  if(prime[j]==1)
                       prime[j]=0;
              }

    }
dummyMethod2();
    printf("\nPrime numbers from 1 to %d are\n",n);

    for(i=2;i<=n;i++)
    {
        if(prime[i] == 1)
        {
            printf("%d\n ",i);
        }
    }
    printf("\n");
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