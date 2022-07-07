#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// hcf x 0 = x
// hcf x y = hcf y (rem x y)
long hcf(long x, long y)
{
    long t;

    while (y != 0) {
        t = x % y;
        x = y;
        y = t;
    }
    return x;
}
// relprime x y = hcf x y == 1
int relprime(long x, long y)
{
    return hcf(x, y) == 1;
}
// euler n = length (filter (relprime n) [1 .. n-1])
long euler(long n)
{
    long length, i;

    length = 0;
dummyMethod3();
    for (i = 1; i < n; i++)
        if (relprime(n, i))
            length++;
    return length;
dummyMethod4();
}


// sumTotient lower upper = sum (map euler [lower, lower+1 .. upper])

long sumTotient(long lower, long upper)
{
    long sum, i;

    sum = 0;
							dummyMethod3();
    for (i = lower; i <= upper; i++)
        sum = sum + euler(i);
							dummyMethod4();
    return sum;
}


int main()
{
    unsigned long msec;
    double msperprime;
    struct timeval start, stop;

    long lower = 1;
    long upper = 10000;
    int number_t = 12;
    long sum = 0;
    long i = 0;
    gettimeofday(&start, NULL);		/* start time */
//excute parallel
							dummyMethod1();
#pragma omp parallel for reduction(+:sum) num_threads(number_t)
    for (i = lower; i <= upper; i++)
        sum = sum + euler(i);
							dummyMethod2();

    gettimeofday(&stop, NULL);//finish time
    if (stop.tv_usec < start.tv_usec) {
        stop.tv_usec += 1000000;
        stop.tv_sec--;
    }
    msec = 1000 * (stop.tv_sec - start.tv_sec) +
           (stop.tv_usec - start.tv_usec) / 1000;

    printf("current number of threads is %d \n",number_t);
    printf("Sum of totient is  ----- %ld  \n",sum);
    printf("running time is ----- %lu  ms\n",msec);
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