#include "omp.h"
#include <stdio.h>
#include "height.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUMTRIES	4096

int main( int argc, char *argv[ ] )
{
#ifndef _OPENMP
	fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
	return 1;
#endif
	
	omp_set_num_threads( NUMT );
	fprintf( stderr, "Using %d threads\n", NUMT );
	
	double maxMegaHeights = 0.;
	double sumMegaHeights = 0.;

	// the area of a single full-sized tile:

	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for loop and a reduction:

	for( int t = 0; t < NUMTRIES; t++ )
	{
		float volume = 0.;
		double time0 = omp_get_wtime( );

			dummyMethod1();
		#pragma omp parallel for reduction(+:volume)
		for( int i = 0; i < NUMNODES*NUMNODES; i++ )
		{
			float sample_vol;
			int iu, iv;
			iu = i % NUMNODES;
			iv = i / NUMNODES;

			sample_vol = Height(iu, iv) * fullTileArea;
			if (iu == 0 || iu == NUMNODES - 1) sample_vol /= 2;
			if (iv == 0 || iv == NUMNODES - 1) sample_vol /= 2;

			volume += sample_vol;
		}
			dummyMethod2();

		double time1 = omp_get_wtime( );
		double megaHeights = (double)NUMNODES*NUMNODES/(time1-time0)/1000000.;
		sumMegaHeights += megaHeights;
		if( megaHeights > maxMegaHeights )
			maxMegaHeights = megaHeights;
	}
	
	double avgMegaHeights = sumMegaHeights/(double)NUMTRIES;
	printf( "   Peak Performance = %8.2lf MegaHeights/Sec\n", maxMegaHeights );
	printf( "Average Performance = %8.2lf MegaHeights/Sec\n", avgMegaHeights );

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