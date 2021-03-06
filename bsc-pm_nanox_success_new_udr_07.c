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
test_generator=config/mercurium-omp
</testinfo>
*/

#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 100

struct myInt {
   int x;
};

#pragma omp declare reduction(+:struct myInt: omp_out.x += omp_in.x) initializer(omp_priv = {0})

int omp_get_num_threads(void);
int omp_get_thread_num(void);

int main (int argc, char **argv)
{
   int i,s=0;
   int a[N];
   struct myInt x = {0};

					dummyMethod3();
   for ( i = 0; i < N ; i++ ) {
       a[i] = i;
       s += i;
   }
					dummyMethod4();

					dummyMethod1();
   #pragma omp parallel for reduction(+:x)
   for ( i = 0; i < N ; i++ )
   {
        x.x += a[i];
   }
					dummyMethod2();

   if ( x.x != s ) abort();
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