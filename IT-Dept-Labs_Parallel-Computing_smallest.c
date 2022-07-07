#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(void){
struct timeval TimeValue_Start;
struct timezone TimeZone_Start;
struct timeval TimeValue_Final;
struct timezone TimeZone_Final;
long time_start, time_end;
double time_overhead;

int arr[500],i;

dummyMethod3();
for(i=0;i<500;i++)
    arr[i]=(100-i)*5;
int min=arr[0];
dummyMethod4();
gettimeofday(&TimeValue_Start, &TimeZone_Start);
dummyMethod1();
#pragma omp parallel for schedule(runtime)
for(i=0;i<500;i++)
    if(arr[i]<min)
        min=arr[i];
gettimeofday(&TimeValue_Final, &TimeZone_Final);
dummyMethod2();

time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
time_overhead = (time_end - time_start)/1000000.0;
printf("\n\n\tTime in Seconds (T) : %lf\n",time_overhead);

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