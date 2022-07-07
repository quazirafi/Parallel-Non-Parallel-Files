#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
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
	double a[n],b[n],max=0.0;
dummyMethod3();
	for(j=0;j<n;j++)
	{
	a[j]=(float)rand()/RAND_MAX;
dummyMethod4();
        printf("%lf\n",a[j]);
	}
		
	gettimeofday(&TimeValue_Start,&Timezone_Start);
	omp_init_lock();
dummyMethod1();
	#pragma omp parallel for
	
		for(i=0;i<n;i++)
		{
			omp_set_lock();
						
				if(a[i]>max)
				max=a[i];
			omp_unset_lock();
		}
dummyMethod2();
	omp_destroy_lock();
	printf("MAXIMUM =%lf\n",max);
	gettimeofday(&TimeValue_Final,&Timezone_Final);
	te=TimeValue_Final.tv_sec*1000000+TimeValue_Final.tv_usec;
	ts=TimeValue_Start.tv_sec*1000000+TimeValue_Start.tv_usec;
	to=(te-ts)/1000000.0;
	printf("parallel time=%lf\n",to);
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