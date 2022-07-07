#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	double ts,te,to;
	int k,i,j,n,s;
	FILE *fp;
	struct timeval TimeValue_Start;
	struct timezone Timezone_Start;
	struct timeval TimeValue_Final;
	struct timezone Timezone_Final;
	printf("Enter the dimension\n");
	scanf("%d",&n);
	int a[n][n],b[n][n],c[n][n];
dummyMethod3();
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
		a[i][j]=2;
		b[i][j]=1;		
		}
	}
dummyMethod4();
		fp=fopen("program.txt","w");
   	 	gettimeofday(&TimeValue_Start,&Timezone_Start);
											dummyMethod1();
	   	#pragma omp parallel for private(i,j,k,) shared(n)	
	   	 for(i=0;i<n;i++)
	    	 {
			for(j=0;j<n;j++)
			{
				s=0;
				for(k=0;k<n;k++)
				{
				c[i][j]+=a[j][k]*b[k][j];
			
				}	
			//fprintf(fp,"%d\t",c[i][j]);
			}
			//fprintf(fp,"\n");
	    	}
											dummyMethod2();
	gettimeofday(&TimeValue_Final,&Timezone_Final);
	te=TimeValue_Final.tv_sec*1000000+TimeValue_Final.tv_usec;
	ts=TimeValue_Start.tv_sec*1000000+TimeValue_Start.tv_usec;
	to=(te-ts)/1000000;
	printf("parallel time=%lf\n",to);

	
	FILE *fp1;
	
	gettimeofday(&TimeValue_Start,&Timezone_Start);
	fp1=fopen("program.txt1","w");
	
	dummyMethod3();
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			s=0;
			
				for(k=0;k<n;k++)
				{
				s=a[j][k]*b[k][j]+s;
			
				}
				c[i][j]=s;
			
			
			
			//fprintf(fp1,"%d\t",c[i][j]);
		
			
		}
		//fprintf(fp1,"\n");
	}
	dummyMethod4();
	
	gettimeofday(&TimeValue_Final,&Timezone_Final);
	te=TimeValue_Final.tv_sec*1000000+TimeValue_Final.tv_usec;
	ts=TimeValue_Start.tv_sec*1000000+TimeValue_Start.tv_usec;
	to=(te-ts)/1000000;
	printf("serial time =%lf\n",to);

	
		
	
	
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