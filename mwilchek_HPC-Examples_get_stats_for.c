/* Author: Glen MacLachlan, bindatype@gmail.com
 * 
 * Copyright 2010 Glen Alan MacLachlan
 * 
 *     This file is part of wavelet.
 *
 *   make_scalogram is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* Wrap main code into this */

#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
#include "get_data.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (int argc, char **argv)
{

  double *index=NULL,*signal=NULL,*uncert=NULL;
  double meanY = 0.;  
  struct data ts;
  clock_t tOne, tTwo, tThree, tFour, tFive; 
 
  ts = get_data(stdin,ts);

  index = malloc(ts.ROWS*sizeof(double));
  signal = malloc(ts.ROWS*sizeof(double));
  uncert = malloc(ts.ROWS*sizeof(double));
  stack_columns(index,signal,uncert,ts);

    if ( 1 != ts.COLS && 2 != ts.COLS && 3 != ts.COLS ) {
      puts(" ");
      puts("WRONG NUMBER OF COLUMNS!");
      puts("Acceptable formats for input files are 1, 2 or 3 columns."); 
      puts("Try awk if necessary.");
//      puts("For usage use -h or --help.");
      free( index );
      free( signal );  
      free( uncert );  
      free( ts.value ); 
      exit(EXIT_FAILURE);
    }

//
// Parellelize the following using either parallel for pragmas or omp sections
//

/* Get Sum */
/* Parallelize This */
  double sum = 0.;
  tOne = clock();
  
			dummyMethod1();
#pragma omp parallel for reduction(+: sum)
  for ( int i = 0; i < ts.ROWS ; i++)
  {
    sum +=signal[i];
  }
			dummyMethod2();

  tOne = clock() - tOne;
  printf("Sum Y: %g \n", sum );
  double time_takenOne = ((double)tOne)/CLOCKS_PER_SEC; // in seconds
  printf("Total Execution Time for Get SUM(OMP PARALLEL): %f seconds \n", time_takenOne);  

/* Get Mean Value */
/* Parallelize This */
  tTwo = clock();
			dummyMethod1();
#pragma omp parallel for reduction(+: meanY)
  for ( int i = 0; i < ts.ROWS ; i++)
  {
    meanY +=signal[i];
  }
			dummyMethod2();
  
  meanY/=(double)ts.ROWS;
  printf("Mean Y: %g \n", meanY);
  
  tTwo = clock() - tTwo;
  double time_takenTwo = ((double)tTwo)/CLOCKS_PER_SEC; // in seconds
  printf("Total Execution Time for Get MEAN(OMP PARALLEL): %f seconds \n", time_takenTwo);

/* Get Minimum */
/* Parallelize This */
  double Min;
  Min = signal[0];
  tThree = clock();

			dummyMethod1();
#pragma omp parallel for reduction(min: Min)
  for ( int i = 1; i < ts.ROWS ; i++)
  {
    if (signal[i] < Min) {Min = signal[i];}
  }
			dummyMethod2();
  
  printf("Min Y: %g\n",Min);

  tThree = clock() - tThree;
  double time_takenThree = ((double)tThree)/CLOCKS_PER_SEC; // in seconds
  printf("Total Execution Time for Get Min(OMP PARALLEL): %f seconds \n", time_takenThree);

/* Get Max */
/* Parallelize This */
  double Max;
  Max = signal[0];
  tFour = clock();

			dummyMethod1();
#pragma omp parallel for reduction(max: Max)
  for ( int i = 1; i < ts.ROWS ; i++)
  {
    if (signal[i] > Max) {Max = signal[i];}
  }
			dummyMethod2();
  printf("Max: Y %g\n",Max);

  tFour = clock() - tFour;
  double time_takenFour = ((double)tFour)/CLOCKS_PER_SEC; // in seconds
  printf("Total Execution Time for Get Max(OMP PARALLEL): %f seconds \n", time_takenFour);

/* Get Variance */
/* Parallelize This */
  double variance = 0.;
  meanY = 0; // reinitialize meanY
  tFive = clock();

			dummyMethod1();
#pragma omp parallel for reduction(+: meanY)
  for ( int i = 0; i < ts.ROWS ; i++)
  {
    meanY +=signal[i];
  }
			dummyMethod2();
  meanY/=(double)ts.ROWS;

			dummyMethod1();
#pragma omp parallel for reduction(+: variance)
  for ( int i = 0; i < ts.ROWS ; i++)
  {
    variance += (signal[i]-meanY)*(signal[i]-meanY);
  }
			dummyMethod2();
  variance/=(double)(ts.ROWS-1);
  printf("Variance Y %g \n", variance);

  tFive = clock() - tFive;
  double time_takenFive = ((double)tFive)/CLOCKS_PER_SEC; // in seconds
  printf("Total Execution Time for Get Variance(OMP PARALLEL): %f seconds \n", time_takenFive);

 
  free( index );
  free( signal );  
  free( uncert );  
  free( ts.value );  

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