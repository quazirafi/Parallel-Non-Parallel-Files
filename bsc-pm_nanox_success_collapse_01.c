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
test_CFLAGS=-std=gnu99
</testinfo>
*/

#include<assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10

void init(int (*v)[N])
{
							dummyMethod3();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            v[i][j] = 0;
							dummyMethod4();
}

void check(int (*v)[N])
{
							dummyMethod3();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            assert(v[i][j] == 1);
							dummyMethod4();
}

int main(int argc, char* argv[])
{
    int v[N][N];
    int i, j;

    {
        init(v);
															dummyMethod1();
        #pragma omp parallel for collapse(2)
        for(i = 0; i < N; ++i)
            for(j = 0; j < N; ++j)
                v[i][j] += 1;
															dummyMethod2();
        check(v);
    }

    {
        init(v);
        #pragma omp parallel
        {
            #pragma omp for collapse(2)
																							dummyMethod3();
            for(i = 0; i < N; ++i)
                for(j = 0; j < N; ++j)
                    v[i][j] += 1;
																							dummyMethod4();
        }
        check(v);
    }

    {
        init(v);
        #pragma omp parallel
        {
            #pragma omp single
            {
                int SIZE = N;
                #pragma omp taskloop grainsize(SIZE) collapse(2)
																															dummyMethod3();
                for(i = 0; i < N; ++i)
                    for(j = 0; j < N; ++j)
                        v[i][j] += 1;
																															dummyMethod4();
            }
        }
        check(v);
    }

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