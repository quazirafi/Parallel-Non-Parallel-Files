#include "pa5.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define RANGE 10000
int main(int argc, char *argv[]){
	long long int n         = 0;
	int i = 0;
	int p = 0;
	int in = 0;
	if (argc < 3){
		printUsage();
		return 0;
	}
	//first arg is n, second is #of threads
	n         = atoll(argv[1]);
	p = atoi(argv[2]);

	omp_set_num_threads(p);

	//1) Throw n darts
	double time = omp_get_wtime();

dummyMethod1();
	#pragma omp parallel for private(i) reduction(+:in)
	for (i = 0; i < n; i++){
		int rank = omp_get_thread_num();
		// generate rand x and y between 0 and 1
		double x = (double)(rand() %RANGE)/RANGE;
		double y = (double)(rand() %RANGE)/RANGE;
		if (isInCircle(x, y)){
			//printf("in\n");
			in++;
		}
		//else printf("out\n");
		//printf("thread[%d] has i: %d, in: %d\n", rank, i, in);
	}
dummyMethod2();
	//printf("after loop: n = %d\n", in);
	//2) what fraction of time did the darts land in teh circle
	//printf("in: %d, total: %d\n",in, n);
	double frac = (double)in/(double)n;
	//Prob(dart lands in circle is area(circ)/area(squard)
	//= πr^2 / 4r^2 = π/4
	//3) π ~ 4 * Prob
	double pi_aprx = frac * 4.0;
	time = omp_get_wtime() - time;

	//printf("π = %f, p: %d, n: %lld, time: %f seconds\n", pi_aprx, p, n, time);
	printf("%d,%lld,%f\n", p, n, time);
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