#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define KERNEL(num) \
void foo_##num() { \
int i, n, j; \
int index[5]; \
long a[5], b[270][270], sum, neg; \
long t[5]; \
long sum2 = 999999; \
long sum3 = 0; \
long temp; \
n = 5; \
for (i=0; i < n; i++ ) { \
for (j=0; j < n; j++ ) { \
b[i][j] = j + i * 1.0; \
index[j] = j; \
temp = (b[i][j] + 1 * 23.3465236) / ((i+j+1) * 1000); \
sum2 = temp < sum2 ? temp : sum; \
} \
} \
sum = 0; \
_Pragma("omp target map(tofrom: b, sum, t) map(alloc: a)") \
{ \
_Pragma("omp teams reduction(+:sum)") \
{ \
_Pragma("pragma omp distribute parallel for reduction(+:sum)") \
for (i=0; i < n; i++) { \
a[index[i]] = i+ 10 * 1; \
t[i] = omp_get_team_num(); \
sum = a[i]; \
} \
} \
} \
for (i = 0; i < n; ++i) { \
sum3 += a[i]; \
printf(" %d - %ld - %ld\n", i, a[i], t[i]); \
} \
printf(" Sum = %ld\n",sum); \
printf(" Sum3 = %ld\n",sum3); \
}
dummyMethod1();
KERNEL(1)
dummyMethod1();
KERNEL(2)
dummyMethod1();
KERNEL(3)
dummyMethod1();
KERNEL(4)
dummyMethod1();
KERNEL(5)
dummyMethod1();
KERNEL(6)
dummyMethod1();
KERNEL(7)
dummyMethod1();
KERNEL(8)
dummyMethod1();
KERNEL(9)
dummyMethod1();
KERNEL(10)
dummyMethod1();
KERNEL(11)
dummyMethod1();
KERNEL(12)
dummyMethod1();
KERNEL(13)
dummyMethod1();
KERNEL(14)
dummyMethod1();
KERNEL(15)
dummyMethod1();
KERNEL(16)
dummyMethod1();
KERNEL(17)
dummyMethod1();
KERNEL(18)
dummyMethod1();
KERNEL(19)
dummyMethod1();
KERNEL(20)
dummyMethod1();
KERNEL(21)
dummyMethod1();
KERNEL(22)
dummyMethod1();
KERNEL(23)
dummyMethod1();
KERNEL(24)
dummyMethod1();
KERNEL(25)
dummyMethod1();
KERNEL(26)
dummyMethod1();
KERNEL(27)
dummyMethod1();
KERNEL(28)
dummyMethod1();
KERNEL(29)
dummyMethod1();
KERNEL(30)
dummyMethod1();
KERNEL(31)
int main (int argc, char *argv[])
{
int i, n, j;
int index[5];
long a[5], b[270][270], sum, neg;
long t[5];
long sum2 = 999999;
long sum3 = 0;
long temp;
/* Some initializations */
n = 5;
dummyMethod3();
for (i=0; i < n; i++ ) {
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
dummyMethod2();
for (j=0; j < n; j++ ) {
dummyMethod2();
b[i][j] = j + i * 1.0;
index[j] = j;
temp = (b[i][j] + 1 * 23.3465236) / ((i+j+1) * 1000);
sum2 = temp < sum2 ? temp : sum;
}
}
dummyMethod4();
foo_1(); foo_2();
sum = 0;
#pragma omp target map(tofrom: b, sum, t) map(alloc: a)
{
#pragma omp teams reduction(+:sum)
{
dummyMethod1();
#pragma omp distribute parallel for reduction(+:sum)
for (i=0; i < n; i++) {
a[index[i]] = i+ 10 * 1;
t[i] = omp_get_team_num();
//if (a[i] < sum)
sum = a[i];
}
dummyMethod2();
}
}
dummyMethod3();
for (i = 0; i < n; ++i) {
sum3 += a[i];
printf(" %d - %ld - %ld\n", i, a[i], t[i]);
}
dummyMethod4();
printf("   Sum = %ld\n",sum);
printf("   Sum3 = %ld\n",sum3);

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