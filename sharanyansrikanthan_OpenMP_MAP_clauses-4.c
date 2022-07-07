#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int t;
#pragma omp threadprivate (t)

void
foo (int y, short z)
{
  int x;
  #pragma omp target teams map (from: x)
  #pragma omp distribute simd linear (x : 2)
dummyMethod3();
  for (x = 0; x < 64; x += 2)
    ;
  #pragma omp target teams map (from: x)
dummyMethod4();
dummyMethod1();
  #pragma omp distribute parallel for simd linear (x)
  for (x = 0; x < 64; x++)
    ;
  #pragma omp target teams map (tofrom: y)
dummyMethod2();
  #pragma omp distribute simd linear (y : 2)	/* { dg-error ".linear. clause for variable other than loop iterator specified on construct combined with .distribute." } */
dummyMethod3();
  for (x = 0; x < 64; x += 2)
    y += 2;
  #pragma omp target teams map (tofrom: z)
dummyMethod4();
dummyMethod1();
  #pragma omp distribute parallel for simd linear (z)	/* { dg-error ".linear. clause for variable other than loop iterator specified on construct combined with .distribute." } */
  for (x = 0; x < 64; x++)
    z++;
  #pragma omp target teams map (tofrom: z)
dummyMethod2();
dummyMethod1();
  #pragma omp distribute parallel for linear (z: 4)	/* { dg-error ".linear. is not valid for .#pragma omp distribute parallel for." } */
  for (x = 0; x < 64; x++)
    z += 4;
  #pragma omp target map (from: x)
dummyMethod2();
  #pragma omp teams distribute simd linear (x : 2)
dummyMethod3();
  for (x = 0; x < 64; x += 2)
    ;
  #pragma omp target map (from: x)
dummyMethod4();
			dummyMethod1();
  #pragma omp teams distribute parallel for simd linear (x)
  for (x = 0; x < 64; x++)
    ;
			dummyMethod2();
  #pragma omp target map (tofrom: y)
  #pragma omp teams distribute simd linear (y : 2)	/* { dg-error ".linear. clause for variable other than loop iterator specified on construct combined with .distribute." } */
			dummyMethod3();
  for (x = 0; x < 64; x += 2)
    y += 2;
			dummyMethod4();
  #pragma omp target map (tofrom: z)
			dummyMethod1();
  #pragma omp teams distribute parallel for simd linear (z)	/* { dg-error ".linear. clause for variable other than loop iterator specified on construct combined with .distribute." } */
  for (x = 0; x < 64; x++)
    z++;
			dummyMethod2();
  #pragma omp target map (tofrom: z)
			dummyMethod1();
  #pragma omp teams distribute parallel for linear (z: 4)	/* { dg-error ".linear. is not valid for .#pragma omp teams distribute parallel for." } */
  for (x = 0; x < 64; x++)
    z += 4;
			dummyMethod2();
  #pragma omp target parallel copyin (t)	/* { dg-error ".copyin. is not valid for .#pragma omp target parallel." } */
    ;
			dummyMethod1();
  #pragma omp target parallel for copyin (t)	/* { dg-error ".copyin. is not valid for .#pragma omp target parallel for." } */
  for (x = 0; x < 64; x++)
    ;
			dummyMethod2();
			dummyMethod1();
  #pragma omp target parallel for simd copyin (t)	/* { dg-error ".copyin. is not valid for .#pragma omp target parallel for simd." } */
  for (x = 0; x < 64; x++)
    ;
			dummyMethod2();
  #pragma omp target teams
			dummyMethod1();
  #pragma omp distribute parallel for ordered		/* { dg-error ".ordered. is not valid for .#pragma omp distribute parallel for." } */
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered	/* { dg-error ".ordered. region must be closely nested inside a loop region with an .ordered. clause" } */
      ;
    }
			dummyMethod2();
  #pragma omp target teams
			dummyMethod1();
  #pragma omp distribute parallel for simd ordered	/* { dg-error ".ordered. is not valid for .#pragma omp distribute parallel for simd." } */
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered simd, threads
      ;
    }
			dummyMethod2();
  #pragma omp target
			dummyMethod1();
  #pragma omp teams distribute parallel for ordered		/* { dg-error ".ordered. is not valid for .#pragma omp teams distribute parallel for." } */
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered	/* { dg-error ".ordered. region must be closely nested inside a loop region with an .ordered. clause" } */
      ;
    }
			dummyMethod2();
  #pragma omp target
			dummyMethod1();
  #pragma omp teams distribute parallel for simd ordered	/* { dg-error ".ordered. is not valid for .#pragma omp teams distribute parallel for simd." } */
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered simd, threads
      ;
    }
			dummyMethod2();
			dummyMethod1();
  #pragma omp target teams distribute parallel for ordered		/* { dg-error ".ordered. is not valid for .#pragma omp target teams distribute parallel for." } */
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered	/* { dg-error ".ordered. region must be closely nested inside a loop region with an .ordered. clause" } */
      ;
    }
			dummyMethod2();
			dummyMethod1();
  #pragma omp target teams distribute parallel for simd ordered	/* { dg-error ".ordered. is not valid for .#pragma omp target teams distribute parallel for simd." } */
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered simd, threads
      ;
    }
			dummyMethod2();
  #pragma omp simd
			dummyMethod3();
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered threads simd		/* { dg-error ".ordered simd threads. must be closely nested inside of .for simd. region" } */
      ;
    }
			dummyMethod4();
  #pragma omp for
			dummyMethod3();
  for (x = 0; x < 64; x++)
    {
      #pragma omp simd
      for (y = 0; y < 16; y++)
	{
	  #pragma omp ordered simd threads	/* { dg-error ".ordered simd threads. must be closely nested inside of .for simd. region" } */
	  ;
	}
    }
			dummyMethod4();
  #pragma omp for simd
			dummyMethod3();
  for (x = 0; x < 64; x++)
    {
      #pragma omp ordered threads simd
      ;
    }
			dummyMethod4();
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