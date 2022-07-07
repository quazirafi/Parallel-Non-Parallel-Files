/*--------------------------------------------------------------------
  (C) Copyright 2006-2013 Barcelona Supercomputing Center
                          Centro Nacional de Supercomputacion
  
  This file is part of Mercurium C/C++ source-to-source compiler.
  
  See AUTHORS file in the top level directory for information
  regarding developers and contributors.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  
  Mercurium C/C++ source-to-source compiler is distributed in the hope
  that it will be useful, but WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the GNU Lesser General Public License for more
  details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with Mercurium C/C++ source-to-source compiler; if
  not, write to the Free Software Foundation, Inc., 675 Mass Ave,
  Cambridge, MA 02139, USA.
--------------------------------------------------------------------*/


/*
<testinfo>
test_generator=(config/mercurium-ompss "config/mercurium-ompss-2 openmp-compatibility")
test_compile_fail_nanos6_mercurium=yes
</testinfo>
*/

#ifndef __ICC

#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


enum { NUM_ITEMS = 500, ARRAY_SIZE = 1000 };

void f1(int array_size, int (*a)[array_size], int *result)
{
  int i;
			dummyMethod3();
  for (i = 0; i < array_size; i++)
  {
      result[i] = 0;
  }
			dummyMethod4();

			dummyMethod1();
  #pragma omp parallel for firstprivate(a) reduction(+:[array_size]result)
  for (i = 0; i < NUM_ITEMS; i++)
  {
    int j;
    for (j = 0; j < array_size; j++)
    {
        result[j] += a[i][j];
    }
  }
			dummyMethod2();
}

enum { RESULT = 124750 };

int main(int argc, char *argv[])
{
    int a[NUM_ITEMS][ARRAY_SIZE];
    int result[ARRAY_SIZE];

    int i, j;
							dummyMethod3();
    for (i = 0; i < NUM_ITEMS; i++)
    {
        for (j = 0; j < ARRAY_SIZE; j++)
        {
            a[i][j] = i;
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (j = 0; j < ARRAY_SIZE; j++)
    {
        result[j] = 0;
    }
							dummyMethod4();

    f1(ARRAY_SIZE, a, result);

							dummyMethod3();
    for (j = 0; j < ARRAY_SIZE; j++)
    {
        if (result[j] != RESULT)
        {
            fprintf(stderr, "wrong result[%d] -> %d != %d\n", j, result[j], RESULT);
            abort();
        }
    }
							dummyMethod4();

    return 0;
}

#else

int main(int argc, char *argv[])
{
    return 0;
}

#endif
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