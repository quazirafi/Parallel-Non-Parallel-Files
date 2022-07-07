#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <string.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_CNT 100
int a [MAX_CNT] = {};
int total_cnt = 0;

void getWanShu(int cnt)
{

    omp_lock_t alock;
    omp_init_lock(&alock);
    
    int tcnt = 0;
    omp_set_num_threads(cnt);
    int q = 0;
    int sum = 0;
							dummyMethod1();
    #pragma omp parallel for private(q, sum)  // for reduction(+:sum)
    for (int n = 1; n < 5000000; n++)
    {
        sum = 0;
	q = sqrt(n);
        for (int i = 1; i <= q; i++) 
        {
            if (n % i == 0)
            {
                sum += i;
		if (i != 1) {
		  sum += n / i;
		}
            }
        }
	
        if (sum == n)
        {
	  omp_set_lock(&alock);
	  a[tcnt] = n;
	  tcnt++;
	  omp_unset_lock(&alock);
        }
    }
							dummyMethod2();
    total_cnt = tcnt;
}

int main(int argc, char **argv) {
  int cnt = 1;
  memset(a, 0, MAX_CNT);
  if (argc > 1) {
    cnt = atoi(argv[1]);
  }
  getWanShu(cnt);
			dummyMethod3();
  for (int i = 0; i < 100 && a[i] != 0; i++) {
    printf("%d\n", a[i]);
  }
			dummyMethod4();
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