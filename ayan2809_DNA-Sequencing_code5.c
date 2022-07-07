#include "omp.h"
#include<stdio.h>
#include <sched.h>
#include <stdbool.h>
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define _GNU_SOURCE

bool isPrime(int n)
{
    // Corner case
    if (n <= 1)
        return false;
 
    // Check from 2 to square root of n
dummyMethod3();
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
 
    return true;
dummyMethod4();
}
int main () 
{
    
    int n=0;
    printf("Enter the value of N : ");
    scanf("%d",&n);
    int c[10000];              //this will store the first n prime numbers
    int i,k=3,d=0;
	   #pragma omp parallel sections
		{
                            
            //generate the first n prime numbers
            #pragma omp section
            {
                
																															dummyMethod1();
                #pragma omp parallel for schedule(guided, 10) // this can be changed with dynamic and guided
                for (i = 1; i <=n*n; i++) 
                {
                    if(isPrime(i))
                    {  
                        if(d<n)
                        {
                            c[d]=i;
                            //printf("Prime : %d\n", i);
                            d++;
                        } 
                         
                    }
                    
            
                }
																															dummyMethod2();
            }
                    
		}
        
        //printing the prime numbers
        printf("The first %d prime numbers are :",n);
															dummyMethod3();
        for (i=0; i < n; i++) 
		{
			printf("%d ",c[i]);
			
		}
															dummyMethod4();
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