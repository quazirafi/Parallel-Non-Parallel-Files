#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int mult_sq_mat_striped_omp(int mat,double **a,double **b,double **c)
/*
	mat c'est la dimension de matrice
	a et b sount la matrice de entre
	c c'est la matrice resoudre
*/
{
int i,j,k;
dummyMethod1();
#pragma omp parallel for private(i,j,k,tid)
	for(i=0;i<mat;i++)
		for(j=0;j<mat;j++)
		{
				c[i][j]=0.0;
				for(k=0;k<mat;k++)
					c[i][j]+=a[i][k]*b[k][j];
		}
	return omp_get_num_threads();
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