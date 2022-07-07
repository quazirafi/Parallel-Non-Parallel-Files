#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
    int x, n = 10;
	int a[n], b[n];
	int i, j;
	srand(1234);
dummyMethod3();
	for(i = 0 ; i < n ; i++)
		a[i] = rand()%1000;

dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < n; i++) { /* for each number */
        x = 0;
        for (j = 0; j < n; j++) /* count number less than it */
            if ((a[i] > a[j]) || (a[i] == a[j]) && (j <i))
                x++;
        b[x] = a[i]; /* copy number into correct place */
    }
dummyMethod2();

for (i = 0; i < n ; i++)
dummyMethod4();
dummyMethod3();
	printf("A[%d]:%d\n", i, a[i]);
for (i = 0; i < n ; i++)
dummyMethod4();
dummyMethod3();
    printf("B[%d]:%d\n", i, b[i]);
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