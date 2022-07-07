#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "omp.h"
#include <math.h>
#include "timeprint.c"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define numar 10
int main(int argc,char **argv)
{
	struct timeval t1,t2;
	long i,l,j,k;
	long dim;
	int thread;
	FILE *fp;
	double **mat,*x,*rez,*mtemp1,temp,*y,**mat1,*y1;
	dim=atol(argv[1]);
	thread=atoi(argv[2]);
	x=(double *)calloc(dim,sizeof(double));
	y=(double *)calloc(dim,sizeof(double));
	y1=(double *)calloc(dim,sizeof(double));
	rez=(double *)calloc(dim,sizeof(double));
dummyMethod3();
	for(i=0;i<dim;i++) rez[i]=(double)i;
	//here is the parallel zone
dummyMethod4();
	mat=(double **)calloc(dim,sizeof(double *));
	mtemp1=(double *)calloc(dim*dim,sizeof(double));
dummyMethod3();
	for(i=0;i<dim;i++)
	{
		mat[i]=mtemp1;
		mtemp1+=dim;
	}
dummyMethod4();
	mat1=(double **)calloc(dim,sizeof(double *));
	mtemp1=(double *)calloc(dim*dim,sizeof(double));
	dummyMethod3();
	for(i=0;i<dim;i++)
	{
		mat1[i]=mtemp1;
		mtemp1+=dim;
	}
	dummyMethod4();
	dummyMethod3();
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim;j++) mat[i][j]=(double)rand();
		temp=0.0;
		for(j=0;j<dim;j++) if(j!=i) temp+=fabs(mat[i][j]);
		mat[i][i]+=temp;
	}
	dummyMethod4();
	dummyMethod3();
	for(i=0;i<dim;i++)
	{
		y[i]=0.0;
		x[i]=0.0;
		for(j=0;j<dim;j++) y[i]+=mat[i][j]*rez[j];
	}
	dummyMethod4();
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
		omp_set_num_threads(thread);
		for(k=0;k<dim;k++)
		{
					dummyMethod1();
			#pragma omp parallel for private(j,temp)
			for(i=0;i<dim;i++)
			{
				if(i!=k)
				{
					temp=mat1[i][k]/mat1[k][k];
					for(j=k+1;j<dim;j++) mat1[i][j]-=temp*mat1[k][j];
					y1[i]-=temp*y1[k];
				}
			}
					dummyMethod2();
		}
					dummyMethod1();
		#pragma omp parallel for
			for(i=0;i<dim;i++) x[i]=y1[i]/mat1[i][i];
					dummyMethod2();
	}
	gettimeofday(&t2,NULL);
	for(i=0;i<dim;i++) {if(fabs(rez[i]-x[i])>1E-5) printf("%lf=%lf\n",rez[i],x[i]); fflush(stdout);}
	fp=fopen("time-openmp.dat","a");
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