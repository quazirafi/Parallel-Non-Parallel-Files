#include <stdio.h>
#include <math.h>
#include "omp_testsuite.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int
check_parallel_for_reduction (FILE * logFile)
{
  int sum = 0;
  int known_sum;
  double dsum = 0;
  double dknown_sum;
  double dt = 0.5;		/* base of geometric row for + and - test */
  double rounding_error = 1.E-9;
#define DOUBLE_DIGITS 20	/* dt^DOUBLE_DIGITS */
  int diff;
  double ddiff;
  int product = 1;
  int known_product;
#define MAX_FACTOR 10
#define KNOWN_PRODUCT 3628800	/* 10! */
  int logic_and = 1;
  int logic_or = 0;
  int bit_and = 1;
  int bit_or = 0;
  int exclusiv_bit_or = 0;
  int logics[LOOPCOUNT];
  int i;
  double dpt;
  int result = 0;

  dt = 1. / 3.;
  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(+:sum)
  for (i = 1; i <= LOOPCOUNT; i++)
    {
      sum = sum + i;
    }
			dummyMethod2();

  if (known_sum != sum)
    {
      result++;
      fprintf (logFile,
               "Error in sum with integers: Result was %d instead of %d\n",
	       sum, known_sum);
    }

  diff = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(-:diff)
  for (i = 1; i <= LOOPCOUNT; ++i)
    {
      diff = diff - i;
    }
			dummyMethod2();

  if (diff != 0)
    {
      result++;
      fprintf (logFile,
               "Error in difference with integers: Result was %d instead of 0.\n",
	       diff);
    }

  /* Tests for doubles */
  dsum = 0;
  dpt = 1;
			dummyMethod3();
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      dpt *= dt;
    }
			dummyMethod4();
  dknown_sum = (1 - dpt) / (1 - dt);
			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(+:dsum)
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      dsum += pow (dt, i);
    }
			dummyMethod2();

  if (fabs (dsum - dknown_sum) > rounding_error)
    {
      result++;
      fprintf (logFile,
               "Error in sum with doubles: Result was %f instead of %f (Difference: %E)\n",
	       dsum, dknown_sum, dsum - dknown_sum);
    }

  dpt = 1;

			dummyMethod3();
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      dpt *= dt;
    }
			dummyMethod4();
  fprintf (logFile, "\n");
  ddiff = (1 - dpt) / (1 - dt);
			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(-:ddiff)
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      ddiff -= pow (dt, i);
    }
			dummyMethod2();
  if (fabs (ddiff) > rounding_error)
    {
      result++;
      fprintf (logFile,
               "Error in Difference with doubles: Result was %E instead of 0.0\n",
	       ddiff);
    }

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(*:product)
  for (i = 1; i <= MAX_FACTOR; i++)
    {
      product *= i;
    }
			dummyMethod2();

  known_product = KNOWN_PRODUCT;
  if (known_product != product)
    {
      result++;
      fprintf (logFile,
               "Error in Product with integers: Result was %d instead of %d\n\n",
	       product, known_product);
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 1;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(&&:logic_and)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_and = (logic_and && logics[i]);
    }
			dummyMethod2();
  if (!logic_and)
    {
      result++;
      fprintf (logFile, "Error in logic AND part 1.\n");
    }

  logic_and = 1;
  logics[LOOPCOUNT / 2] = 0;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(&&:logic_and)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_and = logic_and && logics[i];
    }
			dummyMethod2();
  if (logic_and)
    {
      result++;
      fprintf (logFile, "Error in logic AND part 2.\n");
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 0;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(||:logic_or)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_or = logic_or || logics[i];
    }
			dummyMethod2();
  if (logic_or)
    {
      result++;
      fprintf (logFile, "Error in logic OR part 1.\n");
    }
  logic_or = 0;
  logics[LOOPCOUNT / 2] = 1;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(||:logic_or)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_or = logic_or || logics[i];
    }
			dummyMethod2();
  if (!logic_or)
    {
      result++;
      fprintf (logFile, "Error in logic OR part 2.\n");
    }


			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logics[i] = 1;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(&:bit_and)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_and = (bit_and & logics[i]);
    }
			dummyMethod2();
  if (!bit_and)
    {
      result++;
      fprintf (logFile, "Error in BIT AND part 1.\n");
    }

  bit_and = 1;
  logics[LOOPCOUNT / 2] = 0;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(&:bit_and)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_and = bit_and & logics[i];
    }
			dummyMethod2();
  if (bit_and)
    {
      result++;
      fprintf (logFile, "Error in BIT AND part 2.\n");
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 0;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(|:bit_or)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_or = bit_or | logics[i];
    }
			dummyMethod2();
  if (bit_or)
    {
      result++;
      fprintf (logFile, "Error in BIT OR part 1\n");
    }
  bit_or = 0;
  logics[LOOPCOUNT / 2] = 1;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(|:bit_or)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_or = bit_or | logics[i];
    }
			dummyMethod2();
  if (!bit_or)
    {
      result++;
      fprintf (logFile, "Error in BIT OR part 2\n");
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 0;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(^:exclusiv_bit_or)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      exclusiv_bit_or = exclusiv_bit_or ^ logics[i];
    }
			dummyMethod2();
  if (exclusiv_bit_or)
    {
      result++;
      fprintf (logFile, "Error in EXCLUSIV BIT OR part 1\n");
    }

  exclusiv_bit_or = 0;
  logics[LOOPCOUNT / 2] = 1;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1) reduction(^:exclusiv_bit_or)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      exclusiv_bit_or = exclusiv_bit_or ^ logics[i];
    }
			dummyMethod2();
  if (!exclusiv_bit_or)
    {
      result++;
      fprintf (logFile, "Error in EXCLUSIV BIT OR part 2\n");
    }

  /*printf("\nResult:%d\n",result); */
  return (result == 0);
}

int
crosscheck_parallel_for_reduction (FILE * logFile)
{
  int sum = 0;
  int known_sum;
  double dsum = 0;
  double dknown_sum;
  double dt = 0.5;		/* base of geometric row for + and - test */
  double rounding_error = 1.E-9;
#define DOUBLE_DIGITS 20	/* dt^DOUBLE_DIGITS */
  int diff;
  double ddiff;
  int product = 1;
  int known_product;
#define MAX_FACTOR 10
#define KNOWN_PRODUCT 3628800	/* 10! */
  int logic_and = 1;
  int logic_or = 0;
  int bit_and = 1;
  int bit_or = 0;
  int exclusiv_bit_or = 0;
  int logics[LOOPCOUNT];
  int i;
  double dpt;
  int result = 0;

  dt = 1. / 3.;
  known_sum = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 1; i <= LOOPCOUNT; i++)
    {
      sum = sum + i;
    }
			dummyMethod2();

  if (known_sum != sum)
    {
      result++;
      /*printf("\nError in Sum with integers\n"); */
    }

  diff = (LOOPCOUNT * (LOOPCOUNT + 1)) / 2;
			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 1; i <= LOOPCOUNT; ++i)
    {
      diff = diff - i;
    }
			dummyMethod2();

  if (diff != 0)
    {
      result++;
      /*printf("\nError in Difference: Result was %d instead of 0.\n",diff); */
    }

  /* Tests for doubles */
  dsum = 0;
  dpt = 1;

			dummyMethod3();
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      dpt *= dt;
    }
			dummyMethod4();
  dknown_sum = (1 - dpt) / (1 - dt);
			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      dsum += pow (dt, i);
    }
			dummyMethod2();

  if (dsum != dknown_sum
      && (((dsum - dknown_sum) < rounding_error)
	  || ((dsum - dknown_sum) > rounding_error)))
    {
      result++;
      /*printf("\nError in sum with doubles: Calculated: %f Expected: %f (Difference: %E)\n",dsum,dknown_sum, dsum-dknown_sum); */
    }

  dpt = 1;

			dummyMethod3();
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      dpt *= dt;
    }
			dummyMethod4();
  ddiff = (1 - dpt) / (1 - dt);
			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < DOUBLE_DIGITS; ++i)
    {
      ddiff -= pow (dt, i);
    }
			dummyMethod2();
  if (ddiff > rounding_error || ddiff < (-rounding_error))
    {
      result++;
      /*printf("\nError in Difference with doubles: Difference %E\n",ddiff); */
    }

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 1; i <= MAX_FACTOR; i++)
    {
      product *= i;
    }
			dummyMethod2();

  known_product = KNOWN_PRODUCT;
  if (known_product != product)
    {
      result++;
      /*printf("\nError in Product: Known Product: %d\tcalculated Product: %d\n\n",known_product,product); */
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 1;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_and = (logic_and && logics[i]);
    }
			dummyMethod2();
  if (!logic_and)
    {
      result++;
      /*printf("Error in AND part 1\n"); */
    }

  logic_and = 1;
  logics[LOOPCOUNT / 2] = 0;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_and = logic_and && logics[i];
    }
			dummyMethod2();
  if (logic_and)
    {
      result++;
      /*printf("Error in AND part 2"); */
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 0;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_or = logic_or || logics[i];
    }
			dummyMethod2();
  if (logic_or)
    {
      result++;
      /*printf("Error in OR part 1"); */
    }
  logic_or = 0;
  logics[LOOPCOUNT / 2] = 1;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logic_or = logic_or || logics[i];
    }
			dummyMethod2();
  if (!logic_or)
    {
      result++;
      /*printf("Error in OR part 2"); */
    }


			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      logics[i] = 1;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_and = (bit_and & logics[i]);
    }
			dummyMethod2();
  if (!bit_and)
    {
      result++;
      /*printf("Error in BIT AND part 1\n"); */
    }

  bit_and = 1;
  logics[LOOPCOUNT / 2] = 0;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_and = bit_and & logics[i];
    }
			dummyMethod2();
  if (bit_and)
    {
      result++;
      /*printf("Error in BIT AND part 2"); */
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 0;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_or = bit_or | logics[i];
    }
			dummyMethod2();
  if (bit_or)
    {
      result++;
      /*printf("Error in BIT OR part 1\n"); */
    }
  bit_or = 0;
  logics[LOOPCOUNT / 2] = 1;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      bit_or = bit_or | logics[i];
    }
			dummyMethod2();
  if (!bit_or)
    {
      result++;
      /*printf("Error in BIT OR part 2\n"); */
    }

			dummyMethod3();
  for (i = 0; i < LOOPCOUNT; i++)
    {
      logics[i] = 0;
    }
			dummyMethod4();

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      exclusiv_bit_or = exclusiv_bit_or | logics[i];
    }
			dummyMethod2();
  if (exclusiv_bit_or)
    {
      result++;
      /*printf("Error in EXCLUSIV BIT OR part 1\n"); */
    }

  exclusiv_bit_or = 0;
  logics[LOOPCOUNT / 2] = 1;

			dummyMethod1();
#pragma omp parallel for schedule(dynamic,1)
  for (i = 0; i < LOOPCOUNT; ++i)
    {
      exclusiv_bit_or = exclusiv_bit_or | logics[i];
    }
			dummyMethod2();
  if (!exclusiv_bit_or)
    {
      result++;
      /*printf("Error in EXCLUSIV BIT OR part 2\n"); */
    }

  /*printf("\nResult:%d\n",result); */
  return (result == 0);
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