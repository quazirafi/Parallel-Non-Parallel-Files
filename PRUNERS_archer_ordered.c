/*
Copyright (c) 2015-2019, Lawrence Livermore National Security, LLC.

Produced at the Lawrence Livermore National Laboratory

Written by Simone Atzeni (simone@cs.utah.edu), Joachim Protze
(joachim.protze@tu-dresden.de), Jonas Hahnfeld
(hahnfeld@itc.rwth-aachen.de), Ganesh Gopalakrishnan, Zvonimir
Rakamaric, Dong H. Ahn, Gregory L. Lee, Ignacio Laguna, and Martin
Schulz.

LLNL-CODE-773957

All rights reserved.

This file is part of Archer. For details, see
https://pruners.github.io/archer. Please also read
https://github.com/PRUNERS/archer/blob/master/LICENSE.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

   Redistributions of source code must retain the above copyright
   notice, this list of conditions and the disclaimer below.

   Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the disclaimer (as noted below)
   in the documentation and/or other materials provided with the
   distribution.

   Neither the name of the LLNS/LLNL nor the names of its contributors
   may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE
LIVERMORE NATIONAL SECURITY, LLC, THE U.S. DEPARTMENT OF ENERGY OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// RUN: %libarcher-compile-and-run | FileCheck %s
#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 2

int main(int argc, char* argv[])
{
  int var = 0;
  int i;

			dummyMethod1();
  #pragma omp parallel for ordered num_threads(NUM_THREADS) shared(var)
  for (i = 0; i < NUM_THREADS; i++) {
    #pragma omp ordered
    {
      var++;
    }
  }
			dummyMethod2();

  fprintf(stderr, "DONE\n");
  int error = (var != 2);
  return error;
}

// CHECK: DONE
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