#include <stdio.h> 
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() 
{
int high, low, i, j, flag;
printf("Enter lower limit ");
scanf("%d", &low);
printf("\nEnter upper limit ");
scanf("%d", &high);
printf("\nPrime numbers between %d and %d are: ", low, high); 
double stime = omp_get_wtime();
dummyMethod1();
#pragma omp parallel for reduction(+:flag) 
for (i = low; i <= high; i++) 
{
if (i == 1 || i == 0) 
dummyMethod2();
continue;
flag = 1;
for (j = 2; j <= i / 2; ++j) 
{
if (i % j == 0) 
{ 
	flag = 0;
	break; 
}
}
double etime = omp_get_wtime() - stime; 
if (flag == 1) 
printf("\n%d\ttime for tid number %d: %f ", i,omp_get_thread_num(), etime);
}
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