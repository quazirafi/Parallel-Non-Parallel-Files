// RUN: %libomp-compile-and-run
#include <stdio.h>
#include <math.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DOUBLE_DIGITS 20    /* dt^DOUBLE_DIGITS */
#define MAX_FACTOR 10
#define KNOWN_PRODUCT 3628800  /* 10! */

int test_omp_parallel_reduction()
{
  int sum;
  int known_sum;
  double dsum;
  double dknown_sum;
  double dt=0.5; /* base of geometric row for + and - test*/
  double rounding_error= 1.E-9;
  int diff;
  double ddiff;
  int product;
  int known_product;
  int logic_and;
  int logic_or;
  int bit_and;
  int bit_or;
  int exclusiv_bit_or;
  int logics[LOOPCOUNT];
  int i;
  double dpt;
  int result;

  sum =0;
  dsum=0;
  product=1;
  logic_and=1;
  logic_or=0;
  bit_and=1;
  bit_or=0;
  exclusiv_bit_or=0;
  result=0;
  dt = 1./3.;
  known_sum = (LOOPCOUNT*(LOOPCOUNT+1))/2;

  /* Tests for integers */
			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(+:sum)
  for (i=1;i<=LOOPCOUNT;i++) {
    sum=sum+i;
  }
			dummyMethod2();

  if(known_sum!=sum) {
    result++;
    fprintf(stderr,"Error in sum with integers: Result was %d instead of %d\n",sum,known_sum);
  }

  diff = (LOOPCOUNT*(LOOPCOUNT+1))/2;
			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(-:diff)
  for (i=1;i<=LOOPCOUNT;++i) {
    diff=diff-i;
  }
			dummyMethod2();

  if(diff != 0) {
    result++;
    fprintf(stderr,"Error in difference with integers: Result was %d instead of 0.\n",diff);
  }

  /* Tests for doubles */
  dsum=0;
  dpt=1;
			dummyMethod3();
  for (i=0;i<DOUBLE_DIGITS;++i) {
    dpt*=dt;
  }
			dummyMethod4();
  dknown_sum = (1-dpt)/(1-dt);
			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(+:dsum)
  for (i=0;i<DOUBLE_DIGITS;++i) {
    dsum += pow(dt,i);
  }
			dummyMethod2();

  if( fabs(dsum-dknown_sum) > rounding_error ) {
    result++;
    fprintf(stderr,"Error in sum with doubles: Result was %f instead of %f (Difference: %E)\n",dsum,dknown_sum, dsum-dknown_sum);
  }

  dpt=1;

			dummyMethod3();
  for (i=0;i<DOUBLE_DIGITS;++i) {
    dpt*=dt;
  }
			dummyMethod4();
  fprintf(stderr,"\n");
  ddiff = (1-dpt)/(1-dt);
			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(-:ddiff)
  for (i=0;i<DOUBLE_DIGITS;++i) {
    ddiff -= pow(dt,i);
  }
			dummyMethod2();
  if( fabs(ddiff) > rounding_error) {
    result++;
    fprintf(stderr,"Error in Difference with doubles: Result was %E instead of 0.0\n",ddiff);
  }

  /* Tests for product of integers */
			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(*:product)
  for(i=1;i<=MAX_FACTOR;i++) {
    product *= i;
  }
			dummyMethod2();

  known_product = KNOWN_PRODUCT;
  if(known_product != product) {
    result++;
    fprintf(stderr,"Error in Product with integers: Result was %d instead of %d\n\n",product,known_product);
  }

  /* Tests for logical and */
			dummyMethod3();
  for(i=0;i<LOOPCOUNT;i++) {
    logics[i]=1;
  }
			dummyMethod4();

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(&&:logic_and)
  for(i=0;i<LOOPCOUNT;++i) {
    logic_and = (logic_and && logics[i]);
  }
			dummyMethod2();
  if(!logic_and) {
    result++;
    fprintf(stderr,"Error in logic AND part 1.\n");
  }

  logic_and = 1;
  logics[LOOPCOUNT/2]=0;

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(&&:logic_and)
  for(i=0;i<LOOPCOUNT;++i) {
    logic_and = logic_and && logics[i];
  }
			dummyMethod2();
  if(logic_and) {
    result++;
    fprintf(stderr,"Error in logic AND part 2.\n");
  }

  /* Tests for logical or */
			dummyMethod3();
  for(i=0;i<LOOPCOUNT;i++) {
    logics[i]=0;
  }
			dummyMethod4();

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(||:logic_or)
  for(i=0;i<LOOPCOUNT;++i) {
    logic_or = logic_or || logics[i];
  }
			dummyMethod2();
  if(logic_or) {
    result++;
    fprintf(stderr,"Error in logic OR part 1.\n");
  }
  logic_or = 0;
  logics[LOOPCOUNT/2]=1;

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(||:logic_or)
  for(i=0;i<LOOPCOUNT;++i) {
    logic_or = logic_or || logics[i];
  }
			dummyMethod2();
  if(!logic_or) {
    result++;
    fprintf(stderr,"Error in logic OR part 2.\n");
  }

  /* Tests for bitwise and */
			dummyMethod3();
  for(i=0;i<LOOPCOUNT;++i) {
    logics[i]=1;
  }
			dummyMethod4();

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(&:bit_and)
  for(i=0;i<LOOPCOUNT;++i) {
    bit_and = (bit_and & logics[i]);
  }
			dummyMethod2();
  if(!bit_and) {
    result++;
    fprintf(stderr,"Error in BIT AND part 1.\n");
  }

  bit_and = 1;
  logics[LOOPCOUNT/2]=0;

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(&:bit_and)
  for(i=0;i<LOOPCOUNT;++i) {
    bit_and = bit_and & logics[i];
  }
			dummyMethod2();
  if(bit_and) {
    result++;
    fprintf(stderr,"Error in BIT AND part 2.\n");
  }

			dummyMethod3();
  for(i=0;i<LOOPCOUNT;i++) {
    logics[i]=0;
  }
			dummyMethod4();

  /* Tests for bitwise or */
			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(|:bit_or)
  for(i=0;i<LOOPCOUNT;++i) {
    bit_or = bit_or | logics[i];
  }
			dummyMethod2();
  if(bit_or) {
    result++;
    fprintf(stderr,"Error in BIT OR part 1\n");
  }
  bit_or = 0;
  logics[LOOPCOUNT/2]=1;

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(|:bit_or)
  for(i=0;i<LOOPCOUNT;++i) {
    bit_or = bit_or | logics[i];
  }
			dummyMethod2();
  if(!bit_or) {
    result++;
    fprintf(stderr,"Error in BIT OR part 2\n");
  }

			dummyMethod3();
  for(i=0;i<LOOPCOUNT;i++) {
    logics[i]=0;
  }
			dummyMethod4();

  /* Tests for bitwise xor */
			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(^:exclusiv_bit_or)
  for(i=0;i<LOOPCOUNT;++i) {
    exclusiv_bit_or = exclusiv_bit_or ^ logics[i];
  }
			dummyMethod2();
  if(exclusiv_bit_or) {
    result++;
    fprintf(stderr,"Error in EXCLUSIV BIT OR part 1\n");
  }

  exclusiv_bit_or = 0;
  logics[LOOPCOUNT/2]=1;

			dummyMethod1();
  #pragma omp parallel for schedule(dynamic,1) private(i) reduction(^:exclusiv_bit_or)
  for(i=0;i<LOOPCOUNT;++i) {
    exclusiv_bit_or = exclusiv_bit_or ^ logics[i];
  }
			dummyMethod2();
  if(!exclusiv_bit_or) {
    result++;
    fprintf(stderr,"Error in EXCLUSIV BIT OR part 2\n");
  }

  /*printf("\nResult:%d\n",result);*/
  return (result==0);
}

int main()
{
  int i;
  int num_failed=0;

			dummyMethod3();
  for(i = 0; i < REPETITIONS; i++) {
    if(!test_omp_parallel_reduction()) {
      num_failed++;
    }
  }
			dummyMethod4();
  return num_failed;
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