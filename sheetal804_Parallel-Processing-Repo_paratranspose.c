#include<stdio.h>
#include "omp.h"
#include<sys/time.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	double ts,te,to;
	struct timeval TimeValue_Start;
	struct timezone Timezone_Start;
	struct timeval TimeValue_Final;
	struct timezone Timezone_Final;
	int i,j,n;
	printf("ENTER DIMENSION OF ARRAY\n");
	scanf("%d",&n);
	float a[n][n],b[n][n];

dummyMethod3();
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=(float)rand()/RAND_MAX;
			
			
		}
		
	}
dummyMethod4();

	gettimeofday(&TimeValue_Start,&Timezone_Start);
	dummyMethod1();
	#pragma omp parallel for private(i,j)
	for(i=0;i<n;i++)
	{
		
		#pragma omp parallel for private(j)
		for(j=0;j<n;j++)
		{
			b[i][j]=a[j][i];
		}
			
	}
	dummyMethod2();
	gettimeofday(&TimeValue_Final,&Timezone_Final);
	te=TimeValue_Final.tv_sec*1000000+TimeValue_Final.tv_usec;
	ts=TimeValue_Start.tv_sec*1000000+TimeValue_Start.tv_usec;
	to=(te-ts)/1000000.0;
	printf("parallel time=%lf\n",to);



	gettimeofday(&TimeValue_Start,&Timezone_Start);
	dummyMethod3();
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		if(omp_in_parallel())
		printf("parallel code\n");
			b[i][j]=a[j][i];
		}	
	}
	dummyMethod4();
	gettimeofday(&TimeValue_Final,&Timezone_Final);
	te=TimeValue_Final.tv_sec*1000000+TimeValue_Final.tv_usec;
	ts=TimeValue_Start.tv_sec*1000000+TimeValue_Start.tv_usec;
	to=(te-ts)/1000000.0;
	printf("serial time=%lf\n",to);
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