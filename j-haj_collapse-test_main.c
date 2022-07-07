#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/**
 * Sums the values in the cartesian product [0, m] x [0, n] sequentially
 *
 * @param m end of first range of integers
 * @param n end of second range of integers
 *
 * @return sum of all values in the cartesian product [0, m] x [0, n]
 */
long seq_sum(long m, long n) {
	long result = 0;
dummyMethod3();
	for (long i = 0; i < m; ++i) {
		for (long j = 0; j < n; ++j) {
			result += i + j;
		}
	}
dummyMethod4();
	return result;
}

/**
 * Sums the values in the cartesian product [0, m] x [0, n] in parallel
 *
 * @param m end of first range of integers
 * @param n end of second range of integers
 *
 * @return sum of all values in the cartesian product [0, m] x [0, n]
 */
long par_sum(long m, long n) {
	long result = 0;

	dummyMethod1();
#pragma omp parallel for reduction(+:result)
	for (long i = 0; i < m; ++i) {
		for (long j = 0; j < n; ++j) {
			result += i + j;
		}
	}
	dummyMethod2();
	return result;
}

/**
 * Sums the values in the cartesian product [0, m] x [0, n] in parallel using
 * two omp parallel directives
 *
 * @param m end of first range of integers
 * @param n end of second range of integers
 *
 * @return sum of all values in the cartesian product [0, m] x [0, n]
 */
long par_double_sum(long m, long n) {
	long result = 0;

	dummyMethod1();
#pragma omp parallel for reduction(+:result)
	for (long i = 0; i < m; ++i) {
#pragma omp parallel for reduction(+:result)
		for (long j = 0; j < n; ++j) {
			result += i + j;
		}
	}
	dummyMethod2();
	return result;
}
/**
 * Sums the values in the cartesian product [0, m] x [0, n] in parallel using
 * OpenMP's `collapse` directive
 *
 * @param m end of first range of integers
 * @param n end of second range of integers
 *
 * @return sum of all values in the cartesian product [0, m] x [0, n]
 */
long par_collapse_sum(long m, long n) {
	long result = 0;

	dummyMethod1();
#pragma omp parallel for collapse(2) reduction(+:result)
	for (long i = 0; i < m; ++i) {
		for (long j = 0; j < n; ++j) {
			result += i + j;
		}
	}
	dummyMethod2();
	return result;
}

void print_result(long result, double time, char* msg) {
	printf("Result of %ld in %lf s for %s\n", result, time, msg);
}

int main(int argc, char* argv[]) {

	long m = 20000;
	long n = 20000;

	double start, stop;

	omp_set_num_threads(4);

	start = omp_get_wtime();
	long res_seq = seq_sum(m, n);
	stop = omp_get_wtime();
	print_result(res_seq, stop - start, "sequential");

	start = omp_get_wtime();
	long res_par = par_sum(m, n);
	stop = omp_get_wtime();
	print_result(res_par, stop - start, "parallel");

	start = omp_get_wtime();
	long res_par_2 = par_double_sum(m, n);
	stop = omp_get_wtime();
	print_result(res_par_2, stop - start, "parallel (doulbe for)");

	start = omp_get_wtime();
	long res_par_collapse = par_collapse_sum(m, n);
	stop = omp_get_wtime();
	print_result(res_par_collapse, stop - start, "parallel collapse");

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