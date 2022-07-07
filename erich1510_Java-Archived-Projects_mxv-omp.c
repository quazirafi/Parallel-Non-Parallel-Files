/*

   DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

   Copyright 2009 Sun Microsystems, Inc. All rights reserved.

   The contents of this file are subject to the terms of the BSD License("BSD")(the "License").
   You can obtain a copy of the License at: http://www.opensparc.net/pubs/t1/licenses/BSD+_License.txt

   The BSD License

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

       * Redistribution of source code must retain the above copyright
         notice, this list of conditions and the following disclaimer.
       * Redistribution in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer in
         the documentation and/or other materials provided with the
         distribution.
       * Neither the name of Sun Microsystems, Inc. or the names of
         contributors may be used to endorse or promote products derived
         from this software without specific prior written permission.

   This software is provided "AS IS," without a warranty of any kind. ALL
   EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY
   IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
   NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MICROSYSTEMS, INC. ("SUN") AND
   ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A
   RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
   IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT
   OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR
   PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY,
   ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF SUN HAS
   BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   You acknowledge that this software is not designed, licensed or intended for
   use in the design, construction, operation or maintenance of any nuclear facility.

*/

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void mxv(int m, int n, double * restrict a,
         double * restrict b, double * restrict c);

int main(int argc, char *argv[]) {
   double *a,*b,*c;
   int i, j, m, n, t;

   if(argc >= 3 )
   { //parse args from cmd, parse to integers
     m = atoi(argv[1]);
     n = atoi(argv[2]);
     t = atoi(argv[3]); //new third arg = number of threads
     omp_set_num_threads(t);
   }

   if ( (a=(double *)malloc(m*sizeof(double))) == NULL )
      perror("memory allocation for a");
   if ( (b=(double *)malloc(m*n*sizeof(double))) == NULL )
      perror("memory allocation for b");
   if ( (c=(double *)malloc(n*sizeof(double))) == NULL )
      perror("memory allocation for c");

					dummyMethod3();
   for (j=0; j<n; j++) //printf("Initializing matrix B and vector c\n");
      c[j] = 2.0;
					dummyMethod4();
					dummyMethod3();
   for (i=0; i<m; i++)
      for (j=0; j<n; j++)
         b[i*n+j] = i;
					dummyMethod4();

   double start = omp_get_wtime();
   (void) mxv(m, n, a, b, c); //Executing mxv function
   double time = omp_get_wtime() - start;

   printf("%d \t %d \t %d \t %f \n", t, m, n, time);

   free(a);free(b);free(c);
   return(0);
}

void mxv(int m, int n, double * restrict a, double * restrict b,
         double * restrict c)
{
   int i, j;

					dummyMethod1();
#pragma omp parallel for shared(m,n,a,b,c) private(i,j) //private/public variables specified
   for (i=0; i<m; i++)
   {
      a[i] = 0.0;
      for (j=0; j<n; j++)
      a[i] += b[i*n+j]*c[j];
   }
					dummyMethod2();
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