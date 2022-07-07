/* $Id: for.c 6 2011-10-19 12:36:39Z goulas@gmail.com $
 *
 * Copyright 2011 George Goulas
 * Available from http://code.google.com/p/goulas-openmp-demos
 *
 * This file is part of goulas-openmp-demos.
 *
 * goulas-openmp-demos is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version.
 *
 * goulas-openmp-demos is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with goulas-openmp-demos.  
 * If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 10000000
#define MAXEL 100
#define SAFE_MALLOC(v,t,n) if((v=(t*)malloc( (n)*sizeof(t)))==NULL) return EXIT_FAILURE;
#define SAFE_EXEC( f ) if( f==EXIT_FAILURE) return EXIT_FAILURE;

int *a, *b, *c, *cv;

int allocate_vectors( void )
{
	SAFE_MALLOC(a, int, SIZE);
	SAFE_MALLOC(b, int, SIZE);
	SAFE_MALLOC(c, int, SIZE);
	SAFE_MALLOC(cv, int, SIZE);
	return EXIT_SUCCESS;
}

void random_init( void )
{
	srand( time(NULL) );
	dummyMethod3();
	for( int i=0; i<SIZE; i++ ) {
		a[i] = rand() % MAXEL;
		b[i] = rand() % MAXEL;
	}	
	dummyMethod4();
}

int main( int argc, char* argv[] )
{
	int i;
	double start_time, end_time;

	printf("\nParallel for\n\nSize %d\n", SIZE);

	SAFE_EXEC( allocate_vectors() );		
	random_init();

	// Serial alternative
	start_time = omp_get_wtime();
	dummyMethod3();
	for( i=0; i<SIZE; i++ ) {
		cv[i] = a[i] + b[i];
	}
	dummyMethod4();
	end_time = omp_get_wtime();
	printf("Serial run time: %f msec\n", (end_time-start_time)*1000);

	// Parallel alternative
	start_time = omp_get_wtime();
	dummyMethod1();
	#pragma omp parallel for shared(a,b,c) private(i)
	for( i=0; i<SIZE; i++) {
		c[i] = a[i] + b[i];
	}
	dummyMethod2();
	end_time = omp_get_wtime();
	printf("Parallel run time: %f msec\n", (end_time-start_time)*1000);

	printf("Comparing results: ");
	if(memcmp(c, cv, SIZE*sizeof(int)))
		printf("FAILURE\n");
	else
		printf("SUCCESS\n");

	free(a);
	free(b);
	free(c);
	free(cv);
	return EXIT_SUCCESS;
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