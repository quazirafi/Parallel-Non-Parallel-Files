/*****************************************************************

 NAME:
	work

 FUNCTION:
	do some work

 SYNTAX:
	work(int, int, float);

 ON INPUT:
	nbeg:	starting index (cols)	int
	nfin:	finisching index (cols)	int
	mbeg:	starting index (rows)	int
	mfin:	finisching index (rows)	int
	u:	initial guess		float
	rhs:	right hand side		float

 ON OUTPUT:
	u:	solution		float

 CALLS:

 COMMENTS:
	work does a red-black gauss-seidel relaxation. Iterations are
	controled via a global variable in "global.h"

 LIBRARIES:

 REFERENCES:

 VERSION(S):
	1. original version		j. behrens	3/99

*****************************************************************/

#include <math.h>
#include <stdio.h>
#include "global.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void work(int nbeg, int nfin, int mbeg, int mfin, float **u, float **rhs)
{
	int it, i, j, toggl;
	float tmp1, tmp2;

/* initialize constants */
	tmp1= DX*DX;
	tmp2= 1./4.;

/* main iteration loop */
	for(it=1; it<=ITER; it++){

/* do the red relaxation step */
	dummyMethod1();
#pragma omp parallel for shared( u, rhs ) private( i, j, toggl ) num_threads(numprocs)
	for(i=nbeg+1; i<nfin; i++) {
		if(fmod(i,2) == 0)
	  		toggl=1;
		else
	  		toggl=2;
		for(j=mbeg+toggl; j<mfin; j+=2) {
			u[i][j]= tmp2* (tmp1* rhs[i][j]+ u[i-1][j]+ u[i+1][j]+ u[i][j-1]+ u[i][j+1]);
		}
	}
	dummyMethod2();

/* do the black relaxation step */
	dummyMethod1();
#pragma omp parallel for shared( u, rhs ) private( i, j, toggl ) num_threads(numprocs)
	for(i=nbeg+1; i<nfin; i++) {
		if(fmod(i,2) == 0)
	  		toggl=2;
		else
	  		toggl=1;
		for(j=mbeg+toggl; j<mfin; j+=2) {
			u[i][j]= tmp2* (tmp1* rhs[i][j]+ u[i-1][j]+ u[i+1][j]+ u[i][j-1]+ u[i][j+1]);
		}
	}
	dummyMethod2();
	} /* end of iteration loop */

} /* end of work */
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