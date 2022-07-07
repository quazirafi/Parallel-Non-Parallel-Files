#include <stdio.h>   
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long MULTIPLIER  = 1366;   
static long ADDEND      = 150889;   
static long PMOD        = 714025;   
long random_last = 0.0;   
double random_low, random_hi;   

/*
Functions used to generate random numbers
*/

double random()   
{   
  long random_next;   
  double ret_val;   
  
  random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;   
  random_last = random_next;   
  
  ret_val = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;   
  return ret_val;   
}   

void seed(double low_in, double hi_in)   
{   
  if(low_in < hi_in)   
  {    
    random_low = low_in;   
    random_hi  = hi_in;   
  }   
  else   
  {   
    random_low = hi_in;   
    random_hi  = low_in;   
  }   
  random_last = PMOD/ADDEND; 
  
}   

//    
// The monte carlo pi program   
// Include the OpenMP directives to transform this sequential program in  a
// parallel one
//   

static long num_trials = 1000000;   

int main ()   
{   
  long i;  long Ncirc = 0;   
  double pi, x, y, test;   
  double r = 1.0;   // radius of circle. Side of squrare is 2*r   
  clock_t t1, t2;
t1=clock();  
  seed(-r, r);  // The circle and square are centered at the origin   
  omp_set_num_threads(2);
			dummyMethod1();
#pragma omp parallel for shared(x, y)  reduction(+:Ncirc )
  
  for(i=0;i<num_trials; i++ )   
  {   
    x = random();    
    y = random();   
    test = x*x + y*y;   
    if (test <= r*r) Ncirc++;   
  }   
			dummyMethod2();
  
  pi = 4.0 * ((double)Ncirc/(double)num_trials);   
  t2=clock();
  printf("\n %d trials, pi is %f \n",num_trials, pi);   
  printf("pi parallel time %f\n", (((float)t2 - (float)t1) / 1000000.0F ) * 1000);
     
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