#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
	
	int     Size;
	float * Array;
	float * Sums;
	FILE *  fp;
	int     i,shift;
	
	fp = fopen( "signal.txt", "r" );
	if( fp == NULL )
	{
		fprintf( stderr, "Cannot open file 'signal.txt'\n" );
		exit( 1 );
	}
	fscanf( fp, "%d", &Size );
	Array = (float *)malloc( 2 * Size * sizeof(float) );
	Sums  = (float *)malloc( 1 * Size * sizeof(float) );
	
dummyMethod3();
	for( i = 0; i < Size; i++ )
	{
		fscanf( fp, "%f", &Array[i] );
		Array[i+Size] = Array[i];		// duplicate the array
	}
dummyMethod4();
	fclose( fp );
	i=0;
	omp_set_num_threads(2);
	double time0=omp_get_wtime();
	dummyMethod1();
	#pragma omp parallel for default(none) private(shift,i) shared (Array,Sums,Size) 
	for(shift = 0; shift < Size; shift++ )
	{
		float sum = 0.;
		for( i = 0; i < Size; i++ )
		{
			sum += Array[i] * Array[i + shift];
		}
		Sums[shift] = sum;	// note the "fix #2" from false sharing if you are using OpenMP
	}	
	dummyMethod2();
	double time1=omp_get_wtime();
	double Execution_Time=time1-time0;
	printf("Performance = %lf\n",(Size*Size)/Execution_Time/1000000);
	fp = fopen("AutoCor_Parta.csv", "w+");
	dummyMethod3();
	for( i=0 ;i <512; i++) {
		//printf("Sum[%d] = %lf \n",i,Sums[i]);


		fprintf(fp,"%lf",Sums[i]);
		fprintf(fp,"\n");
	}
	dummyMethod4();
	fclose(fp);	
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