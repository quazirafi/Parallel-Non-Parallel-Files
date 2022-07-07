#include <stdio.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
    double a[10],maximum=0.0,avg,minimum=10000.0;
int i,sum=0;
printf("SRUTI VERMA 18BCE1005:\n");
dummyMethod3();
    for( i=0; i<10; i++)
        scanf("%lf",&a[i]);
    #pragma omp parallel for reduction(+:sum)
dummyMethod4();
dummyMethod1();
    for(i=0;i<10;i++){
    sum=sum+a[i];
dummyMethod2();
	}
    avg=sum/10;
printf("THE CLASS AVERAGE IS = %f\n",avg);

dummyMethod1();
    #pragma omp parallel for reduction(max : maximum)
    for( i=0;i<10; i++)
    {
        printf("thread id = %d and i = %d\n", omp_get_thread_num(), i);
        if(a[i] > maximum)
        {
            maximum = a[i];  
        }
    }
dummyMethod2();
  
    printf("\nTHE MAXIMUM MARKS IS = %f\n", maximum);
    minimum = maximum;
							dummyMethod1();
    #pragma omp parallel for reduction(min : minimum)
    for( i=0;i<10; i++)
    {
        printf("thread id = %d and i = %d\n", omp_get_thread_num(), i);
        if(a[i] < minimum)
        {
            minimum = a[i];  
        }
    }
							dummyMethod2();
  
    printf("\nTHE MINIMUM MARKS IS = %f\n", minimum);
    double d=0;
							dummyMethod1();
    #pragma omp parallel for reduction(+ : d)
    for( i=0;i<10; i++)
    {
		d = d + ((a[i]-avg)*(a[i]-avg));
    }
							dummyMethod2();
	double stadev = sqrt(d/10);
	printf("THE STANDARD DEVIATION OF MARKS IS =  %f\n",stadev);
   
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