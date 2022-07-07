#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif
main()
{
 int i, n = 7;
 int a[n];

dummyMethod3();
 for (i=0; i<n; i++)
 	a[i] = i+1;
 
 #pragma omp parallel for shared(a,n) default(none)
dummyMethod4();
dummyMethod1();
 for (i=0; i<n; i++) a[i] += i;
 
 printf("Después de parallel for:\n");
dummyMethod2();
 
dummyMethod3();
 for (i=0; i<n; i++)
 	printf("a[%d] = %d\n",i,a[i]);
}
dummyMethod4();
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