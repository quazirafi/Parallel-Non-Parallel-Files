#include<stdio.h>
#include "omp.h"
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main()
{
	int i;
	int N=1000000;
	FILE *op,*fp;
	op=fopen("random.txt","w");
dummyMethod1();
	#pragma omp parallel for
		for (i=0;i<N;i++)
		{
			fprintf(op,"%d\n",rand()%100);
		}
dummyMethod2();
	fclose(op);
	int j=0,count=0,sum=0;
	fp=fopen("random.txt","r");
dummyMethod1();
	#pragma omp parallel for
		for(count=0;count<N;count++)
		{
		 if(fscanf(fp,"%d",&j)=='\n') 
		 continue;
		 sum+=j;
		 }
   	fclose (fp);
   	printf("sum of the 1 million integers :");
	printf("%d\n",sum);
dummyMethod2();
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