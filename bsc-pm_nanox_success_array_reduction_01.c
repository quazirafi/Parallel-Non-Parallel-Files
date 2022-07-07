/*--------------------------------------------------------------------
  (C) Copyright 2006-2012 Barcelona Supercomputing Center
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
test_generator=config/mercurium-omp
</testinfo>
*/

#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Intel compiler has lots of problems with VLAs
// let's skip this test
#ifndef __ICC

enum { NUM_ITEMS = 100, ARRAY_SIZE = 10 };

void f2(int (*a)[ARRAY_SIZE], int *result)
{
  int i;
			dummyMethod3();
  for (i = 0; i < ARRAY_SIZE; i++)
  {
      result[i] = 0;
  }
			dummyMethod4();

			dummyMethod1();
  #pragma omp parallel for firstprivate(a) reduction(+:[ARRAY_SIZE]result)
  for (i = 0; i < NUM_ITEMS; i++)
  {
    int j;
    for (j = 0; j < ARRAY_SIZE; j++)
    {
        result[j] += a[i][j];
    }
  }
			dummyMethod2();
}

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

    f2(a, result);

							dummyMethod3();
    for (j = 0; j < ARRAY_SIZE; j++)
    {
        if (result[j] != 4950)
        {
            fprintf(stderr, "wrong result[%d] -> %d != 4950\n", j, result[j]);
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