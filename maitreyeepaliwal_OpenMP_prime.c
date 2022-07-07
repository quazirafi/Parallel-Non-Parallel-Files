#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
	int i=0;
	int n;
	printf("Done by Maitreyee\n\n");
	scanf("%d", &n);


	int j=0,count1=0,pc=0;
	double start_time, end_time;

	dummyMethod1();
	#pragma omp parallel for reduction(+:total)
	for(i=1; i<=n; i++) {
            start_time = omp_get_wtime();

			int count1 = 0;

			for(j=1; j<=i; j++) {

				if((i%j) == 0) {

					count1++;
				}
			}
		if(count1 <= 2) {

				total++;
				printf("%d ", i);
				end_time = omp_get_wtime()-start_time;
			 printf("\t %f \n", end_time);

			}

}
	dummyMethod2();

printf("\nNumber of prime numbers between are %d\n",total);
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