/**
 * This file focuses on the Jacobi algorithm
 * Loops in thie file are modified to be paralleled by OpenMP because all these loops are balance and the default schedule way is applied.
 * The work is split evenly and assigned to each thread.
 * The variable i and j is to calculate the number of iterations. Each thread has a copy of them.
 * The variable psi(zet), psitmp(zettmp), lm, m and re is set to shared. All threads is able to see it.
 * The variable dsq is set to reduction to avoid the race between threads.
 **/

#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "jacobi.h"

void jacobistep(double **psinew, double **psi, int m, int n)
{
  int i, j;

dummyMethod1();
#pragma omp parallel for default(none), private(i,j), shared(psi,psinew,m,n)
  for(i=1;i<=m;i++)
    {
      for(j=1;j<=n;j++)
	{
	  psinew[i][j]=0.25*(psi[i-1][j]+psi[i+1][j]+psi[i][j-1]+psi[i][j+1]);
        }
    }
}
dummyMethod2();

void jacobistepvort(double **zetnew, double **psinew,
		    double **zet, double **psi,
		    int m, int n, double re)
{
  int i, j;

			dummyMethod1();
#pragma omp parallel for default(none), private(i,j), shared(psi,psinew,zet,m,n)
  for(i=1;i<=m;i++)
    {
      for(j=1;j<=n;j++)
	{
	  psinew[i][j]=0.25*(  psi[i-1][j]+psi[i+1][j]+psi[i][j-1]+psi[i][j+1]
			     - zet[i][j] );
	}
    }
			dummyMethod2();

			dummyMethod1();
#pragma omp parallel for default(none), private(i,j), shared(zet,zetnew,psi,m,n,re)
  for(i=1;i<=m;i++)
    {
      for(j=1;j<=n;j++)
	{
	  zetnew[i][j]=0.25*(zet[i-1][j]+zet[i+1][j]+zet[i][j-1]+zet[i][j+1])
	    - re/16.0*(
		       (  psi[i][j+1]-psi[i][j-1])*(zet[i+1][j]-zet[i-1][j])
		       - (psi[i+1][j]-psi[i-1][j])*(zet[i][j+1]-zet[i][j-1])
		       );
	}
    }
			dummyMethod2();
}

double deltasq(double **newarr, double **oldarr, int m, int n)
{
  int i, j;

  double dsq=0.0;
  double tmp;

			dummyMethod1();
#pragma omp parallel for default(none), private(i,j,tmp), shared(newarr,oldarr,m,n), reduction(+:dsq)
  for(i=1;i<=m;i++)
    {
      for(j=1;j<=n;j++)
	{
	  tmp = newarr[i][j]-oldarr[i][j];
	  dsq += tmp*tmp;
        }
    }
			dummyMethod2();

  return dsq;
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