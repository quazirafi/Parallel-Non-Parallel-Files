#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>

int main ( int argc, char *argv[] );
double test01 ( int n, double x[], double y[] );
double test02 ( int n, double x[], double y[] );

/******************************************************************************/

int main ( int argc, char *argv[] )
{
  double factor;
  int i;
  int n;
  double wtime;
  double *x;
  double xdoty;
  double *y;

  n = 10;

  while ( n < 10000000 )
  {
    n = n * 10;

    x = ( double * ) malloc ( n * sizeof ( double ) );
    y = ( double * ) malloc ( n * sizeof ( double ) );

    factor = ( double ) ( n );
    factor = 1.0 / sqrt ( 2.0 * factor * factor + 3 * factor + 1.0 );

							dummyMethod3();
    for ( i = 0; i < n; i++ )
    {
      x[i] = ( i + 1 ) * factor;
    }
							dummyMethod4();

							dummyMethod3();
    for ( i = 0; i < n; i++ )
    {
      y[i] = ( i + 1 ) * 6 * factor;
    }
							dummyMethod4();

    printf ( "\n" );
/*
  Test #1
*/
    //...YOU NEED TO FILL HERE ...
    wtime = omp_get_wtime();
    xdoty = test01(n, x, y);
    wtime = omp_get_wtime() - wtime;
    printf ( "  Sequential  %8d  %14.6e  %15.10f\n", n, xdoty, wtime );
/*
  Test #2
*/
    //...YOU NEED TO FILL HERE ...
    wtime = omp_get_wtime();
    xdoty = test02(n, x, y);
    wtime = omp_get_wtime() - wtime;

    printf ( "  Parallel    %8d  %14.6e  %15.10f\n", n, xdoty, wtime );
  
    free ( x );
    free ( y );
  }
/*
  Terminate.
*/
  printf ( "\n" );
  printf ( "DOT_PRODUCT\n" );
  printf ( "  Normal end of execution.\n" );

  return 0;
}

//Sequential version
double test01 ( int n, double x[], double y[] )

{
  int i;
  double xdoty;

  xdoty = 0.0;

  //...YOU NEED TO FILL HERE...
			dummyMethod3();
  for (i = 0; i < n; i++) 
  {
    xdoty += x[i] * y[i];
  }
			dummyMethod4();

  return xdoty;
}

//Parallel version
double test02 ( int n, double x[], double y[] )

{
  int i;
  double xdoty;

  xdoty = 0.0;

  //...YOU NEED TO FILL HERE...
			dummyMethod1();
  #pragma omp parallel for reduction(+:xdoty)
  for (i = 0; i < n; i++)
    {
      xdoty += x[i] * y[i];
    }
			dummyMethod2();
   
  return xdoty;
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