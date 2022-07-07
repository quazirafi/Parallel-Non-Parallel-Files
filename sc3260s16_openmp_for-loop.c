#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define CHUNKSIZE 100
#define N     1000

int main ()  
{

   int i, chunk;
   float a[N], b[N], \
         c[N];

   /* Some initializations */
dummyMethod3();
   for (i=0; i < N; i++)
      a[i] = b[i] = i * 1.0;
   chunk = CHUNKSIZE;
dummyMethod4();

   /* Note that we cannot apply the nowait construct here */
dummyMethod1();
   #pragma omp parallel for shared(a,b,c,chunk) private(i) schedule(static,chunk)
   for (i=0; i < N; i++)
   {
      c[i] = a[i] + b[i];
   }
dummyMethod2();

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