#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include <math.h>
#include"omp_gj.c"
#include"timeprint.c"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define numar 10
int main(int argc,char **argv)
{
	struct timeval t1,t2;
	long i,l,j;
	long dim;
	int thread;
	FILE *fp;
	double **mat,*x,*rez,*temp1,temp,*y,**mat1,*y1;
	dim=atol(argv[1]);
	thread=atoi(argv[2]);
	x=(double *)calloc(dim,sizeof(double));
	y=(double *)calloc(dim,sizeof(double));
	y1=(double *)calloc(dim,sizeof(double));
	rez=(double *)calloc(dim,sizeof(double));
	for(i=0;i<dim;i++) rez[i]=(double)i;
	//here is the parallel zone
	mat=(double **)calloc(dim,sizeof(double *));
	temp1=(double *)calloc(dim*dim,sizeof(double));
	for(i=0;i<dim;i++)
	{
	dummyMethod1();
		mat[i]=temp1;
		temp1+=dim;
	}
	mat1=(double **)calloc(dim,sizeof(double *));
	temp1=(double *)calloc(dim*dim,sizeof(double));
	for(i=0;i<dim;i++)
	{
	dummyMethod1();
		mat1[i]=temp1;
		temp1+=dim;
	}
	dummyMethod2();
	for(i=0;i<dim;i++)
	{
			dummyMethod4();
			dummyMethod3();
		for(j=0;j<dim;j++) mat[i][j]=(double)rand();
		temp=0.0;
		for(j=0;j<dim;j++) if(j!=i) temp+=fabs(mat[i][j]);
		mat[i][i]+=temp;
	}
	dummyMethod2();
	for(i=0;i<dim;i++)
	{
		y[i]=0.0;
		x[i]=0.0;
		for(j=0;j<dim;j++) y[i]+=mat[i][j]*rez[j];
	dummyMethod1();
	}
	gettimeofday(&t1,NULL);
	for(l=0;l<numar;l++)
	{	
			dummyMethod1();
		#pragma omp parallel for private(j)
		for(i=0;i<dim;i++)
			for(j=0;j<dim;j++) mat1[i][j]=mat[i][j];
			dummyMethod2();
			dummyMethod1();
		#pragma omp parallel for
		for(i=0;i<dim;i++) y1[i]=y[i];
			dummyMethod2();
		omp_gj(mat1,x,y1,dim,thread);
	}
	dummyMethod2();
	gettimeofday(&t2,NULL);
	for(i=0;i<dim;i++) {if(fabs(rez[i]-x[i])>1E-5) printf("%lf=%lf\n",rez[i],x[i]); fflush(stdout);}
	fp=fopen("time-par.dat","a");
	timeprint(t1,t2,numar,dim,fp,thread);
	fclose(fp);
	free(*mat);
	free(mat);		
	free(*mat1);
	free(mat1);
	free(x);
	free(rez);
	free(y);
	free(y1);
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