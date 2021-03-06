#include "omp.h"
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void insert(float a[], int k){
	int i;
dummyMethod3();
	for(i=0;i<k;i++){
		a[i]=(float)rand()/RAND_MAX;
	}
dummyMethod4();
}
void display(float a[],int k){
	int i;	
dummyMethod3();
	for(i=0;i<k;i++)
		printf(" %f\t",a[i]);
	printf("\n");
dummyMethod4();
}

int main(){
	float *a,*b,*c;
	int i,n,k,m;
	clock_t t_begin,t_end;
	double t_time;
	FILE *fp=fopen("file1.txt","w");
	FILE *fp1=fopen("time.txt","w");
	FILE *fp2=fopen("time1.txt","w");
	for(m=1;m<=128;m=m+3){
	omp_set_num_threads(m);
	//printf("NUMBER OF THREADS :%d\n",m)	;
	fprintf(fp,"%d\n",m);
	fprintf(fp1,"%d\n",m);
	fprintf(fp2,"%d\t",m);
	for(k=10;k<1000;k=k*10){
		a=(float *)malloc(sizeof(float)*k);
		b=(float *)malloc(sizeof(float)*k);
		c=(float *)malloc(sizeof(float)*k);
		insert(a,k);
		insert(b,k);
		t_begin=clock();
			dummyMethod1();
		#pragma omp parallel for private(i) schedule(static)
		for(i=0;i<k;i++)
			c[i]=a[i]+b[i];
			dummyMethod2();
		t_end=clock();
		t_time=(double)(t_end-t_begin)/CLOCKS_PER_SEC;
			fprintf(fp,"%d\n",k);
		for(i=0;i<k;i++){
			fprintf(fp,"%lf\t%lf\t%lf\n",a[i],b[i],c[i]);
		}
		fprintf(fp,"\n\n");
		fprintf(fp1,"k =%d\nTime :%lf\n",k,t_time);
		free(a);
		free(b);
		free(c);
	   }
		fprintf(fp2,"%lf\n",t_time);	
	fprintf(fp1,"\n");
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