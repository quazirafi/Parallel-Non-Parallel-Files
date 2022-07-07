#include <math.h>
#include <ctype.h>
#include "get_data.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct data get_data(FILE * stream,struct data this_struct)
{
  char buf[BUFSIZ];
  const char delims[] = " ,\t,\n";
  char *result = NULL;
  int COLS,ROWS,SIZE;
  double *array = NULL;
 
  COLS = ROWS = SIZE = 0;
  while (NULL != fgets(buf,MAXLEN,stream) )
  { COLS = 0;
    remove_trailing_blanks(buf);   
 
    ++ROWS;
    result = strtok( buf, delims ); 
//    remove_trailing_blanks(result);    
 
    while( result != NULL ) {
      ++COLS;
      ++SIZE;
      array = realloc(array,SIZE*sizeof(double)); 
      array [SIZE-1] = atof(result) ;
      result = strtok( NULL, delims );
    }
  }

  this_struct.value = array;
  this_struct.COLS = COLS;
  this_struct.ROWS = ROWS;
  this_struct.SIZE = SIZE;
  return this_struct;
}
void remove_trailing_blanks(char *buf)
{
    char *p;
    p = (buf+strlen(buf));
    while ( 0 != isspace( *(p) ) || '\0' == *p )
    {
        p--;
    }
    *(p+1) = '\0';
}

void stack_columns(double *index, 
		double *signal, 
		double *uncert,
		struct data ts){
    if ( 1 == ts.COLS ) {
											dummyMethod1();
#pragma omp parallel for
      for ( int m = 0; m < ts.ROWS; m++ ) {
        index[m] = m;
        signal[m] = ts.value[m];
        uncert[m] = sqrt(fabs(signal[m]));
      }
											dummyMethod2();
    } else if ( 2 == ts.COLS ) {
											dummyMethod1();
#pragma omp parallel for
      for ( int m = 0; m < ts.ROWS; m++ ) {
        index[m] = ts.value[m*ts.COLS];
        signal[m] = ts.value[m*ts.COLS+1];
        uncert[m] = sqrt(fabs(signal[m]));
      }
											dummyMethod2();
    } else if ( 3 == ts.COLS ) {
											dummyMethod1();
#pragma omp parallel for
      for ( int m = 0; m < ts.ROWS; m++ ) {
        index[m] = ts.value[m*ts.COLS];
        signal[m] = ts.value[m*ts.COLS+1];
        uncert[m] = ts.value[m*ts.COLS+2];
      }
											dummyMethod2();
    }
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