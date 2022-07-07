#include "omp.h"
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ARRAYSIZE       10000000	// you decide
#define NUMTRIES        100	// you decide

float A[ARRAYSIZE];
float B[ARRAYSIZE];
float C[ARRAYSIZE];

int
main( )
{
#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
#endif

        omp_set_num_threads( NUMT );
        fprintf( stderr, "Using %d threads\n", NUMT );

        double maxMegaMults = 0.;
        double sumMegaMults = 0.;
		double time=0.;
        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );

																															dummyMethod1();
                #pragma omp parallel for
                for( int i = 0; i < ARRAYSIZE; i++ )
                {
                        C[i] = A[i] * B[i];
                }
																															dummyMethod2();

                double time1 = omp_get_wtime( );
                double megaMults = (double)ARRAYSIZE/(time1-time0)/1000000.;
                sumMegaMults += megaMults;
                if( megaMults > maxMegaMults )
                        maxMegaMults = megaMults;
				time+=time1-time0;
        }
		
        double avgMegaMults = sumMegaMults/(double)NUMTRIES;
        printf("NUM Tries = %d \nExecution time = %lf\n",NUMT,NUMTRIES,time/NUMTRIES);
		printf( "Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults );
        printf( "Average Performance = %8.2lf MegaMults/Sec\n", avgMegaMults );

	// note: %lf stands for "long float", which is what printf calls a "double"
	//        %d stands for "decimal integer", not "double"

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