#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(int argc, char const *argv[])
{
	struct timeval TimeValue_Start;
	struct timezone TimeZone_Start;
	struct timeval TimeValue_Final;
	struct timezone TimeZone_Final;
	long time_start,time_end;
	double time_overhead;
	double pi,x;
	int i,N;
	pi=0.0;
	N=1000;
	gettimeofday(&TimeValue_Start, &TimeZone_Start);
dummyMethod1();
	#pragma omp parallel for private(x) reduction(+:pi)
	for(i=0;i<=N;i++){
		x=(double)i/N;
		pi+=4/(1+x*x);
	}
dummyMethod2();
	gettimeofday(&TimeValue_Final, &TimeZone_Final);
	time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
	time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
	time_overhead = (time_end - time_start)/1000000.0;
	printf("\n\n\tTime in Seconds (T) : %lf\n",time_overhead);
	pi=pi/N;
	printf("\n \tPi is %f\n\n",pi);


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