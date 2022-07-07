#include <stdio.h>
#include "omp.h"
#include <math.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
float f(float x, float y, float h){
	return -10*(x*x+y*y+5)*h*h;
}

void main()
{
//	FILE *fp = fopen("resultat.dat", "w");
	int i, j, N=400, M=400, id;
	//------------------change overelaxation factor -----------------------------------------------w=[1.0, 1.95, 1.99]---------------------
	float h, k, tolerance=0.1, tol, toll, old, odd_even,                                                  w=1.0;
	float n=400.0, m=400.0, xedge=1.0, yedge=1.0, error=pow(10,-7), a=1/((n-2.0)*(m-2.0));
	float ff[M][N];
dummyMethod3();
	for (i=0; i<M; i++){
		for (j=0; j<N; j++){
			ff[i][j]=0.0;
			if (j==N-1) ff[i][j]=1.0;
		}
	}
dummyMethod4();
	h=xedge/M;
	k=yedge/N;
	printf("h=%f, k=%f\n",h,k);
	omp_set_num_threads(1);
	while (tolerance>error){
		toll=0.0;
			dummyMethod1();
		#pragma omp parallel for schedule(dynamic) shared(ff, N, M, h, k, w) private(i, j, id, old, odd_even) reduction(+:toll) default(none) 
		for (i=1; i<M-1; i++){
			for (j=1; j<N-1; j++){
				odd_even=(i+j)%2;
				if (odd_even==1){
					old=ff[i][j];
					ff[i][j]=(1.0-w)*old + w*0.25*(ff[i+1][j]+ff[i-1][j]+ff[i][j+1]+ff[i][j-1]-f(i*h, j*k, h));
					toll+=ff[i][j]-old;
				}
			}
		}
			dummyMethod2();
			dummyMethod1();
		#pragma omp parallel for schedule(dynamic) shared(ff, N, M, h, k, w) private(i, j, id, old, odd_even) reduction(+:toll) default(none) 
		for (i=1; i<M-1; i++){
			for (j=1; j<N-1; j++){
				odd_even=(i+j)%2;
				if (odd_even==0){
					old=ff[i][j];
					ff[i][j]=(1-w)*old + w*0.25*(ff[i+1][j]+ff[i-1][j]+ff[i][j+1]+ff[i][j-1]-f(i*h, j*k, h));
					toll+=ff[i][j]-old;
				}	
			}
		}
			dummyMethod2();
		tolerance=fabs(toll)*a;
	}
	/*for (i=0; i<M; i++){
		for (j=0; j<N; j++){
				fprintf(fp,"%f  ",ff[i][j]);
			}
		fprintf(fp,"\n");
	}
	fclose(fp);*/
	printf("fcenter=%f\n",ff[N/2][M/2]);
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