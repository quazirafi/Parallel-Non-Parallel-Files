#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int omp_gj(double **mat,double *x,double *y,long dim,long threads)
{
	long k,i,j;
	double temp;
	omp_set_num_threads(threads);
	for(k=0;k<dim;k++)
	{
dummyMethod1();
#pragma omp parallel for private(j,temp)
		for(i=0;i<dim;i++)
		{
			if(i!=k)
			{
				temp=mat[i][k]/mat[k][k];
				for(j=k+1;j<dim;j++) mat[i][j]-=temp*mat[k][j];
				y[i]-=temp*y[k];
			}
		}
dummyMethod2();
	}
dummyMethod1();
#pragma omp parallel for
	for(i=0;i<dim;i++) x[i]=y[i]/mat[i][i];
	return 0;
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