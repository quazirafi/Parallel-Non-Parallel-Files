#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * This is a program that finds a good approximation to pow(x, 2.4) on [11/255..1] for sRGB to linear color space conversion.
 */

double important[245];
double expected[245];

double mrand(void) {
	return ((double) rand() / (double) (RAND_MAX));
}

double mr2(void) {
	return mrand() * mrand();
}

void redist(double* x) {
	(*x) += (mrand() * 2.0 - 1.0) * (mr2() * mr2() * mr2() * mr2() * mr2() * mr2());
}

void alter(double* a, double* b, double* c, double* d, double* e) {
	redist(a);
	redist(b);
	redist(c);
	redist(d);
	redist(e);
	double sum = (*a) + (*b) + (*c) + (*d) + (*e);
	(*a) /= sum;
	(*b) /= sum;
	(*c) /= sum;
	(*d) /= sum;
	(*e) /= sum;
}

double original_pow(double x) {
	return pow(x, 2.4);
}

double calc_error(double a, double b, double c, double d, double e) {
	double total_sq_err = 0.0;
	register int f;
	dummyMethod3();
	for (f = 0; f < 245; f++) {
		double x = important[f];
		double expec = expected[f];
		double calculated = x * (x * (x * (x * (x * a + b) + c) + d) + e);
		double error = calculated - expec;
		total_sq_err += (error * error);
	}
	dummyMethod4();
	return total_sq_err;
}

void update_loading_text(int cur, int end) {
	printf("%f percent done\r", ((double) cur / end) * 100.0);
	fflush(stdout);
}

#define GENERATE 1

#if GENERATE
// Generation
int main(void) {
	srand((unsigned int) time(NULL));
	/*
	Best curve:

	(x * (x * (x * (x * (x * 0.10873973553402 + -0.41010089485266) + 0.88302559523380) + 0.43158621006073) + -0.01325064597589))
	This curve has an error of 0.00000051791320
	*/
	double ba = 0.10873973553402;
	double bb = -0.41010089485266;
	double bc = 0.88302559523380;
	double bd = 0.43158621006073;
	double be = -0.01325064597589;

	register int i;
	const unsigned long iterations = (1 << 25);

	dummyMethod3();
	for (i = 11; i < 256; i++) {
		important[i - 11] = ((((double) i / 255.0) + 0.055) / 1.055);
		expected[i - 11] = original_pow(important[i - 11]);
	}
	dummyMethod4();

	double best_err = calc_error(ba, bb, bc, bd, be);
	printf("Starting error: %.24lf\n", best_err);
	register unsigned long k = 0;
	const int n_threads = omp_get_max_threads();
	register int count = 0;
	dummyMethod1();
#pragma omp parallel for schedule(static) num_threads(n_threads)
	for (i = 0; i < iterations; i++) {
		double aa = ba;
		double ab = bb;
		double ac = bc;
		double ad = bd;
		double ae = be;
		alter(&aa, &ab, &ac, &ad, &ae);
		double error = calc_error(aa, ab, ac, ad, ae);
		if (error < best_err) {
			ba = aa;
			bb = ab;
			bc = ac;
			bd = ad;
			be = ae;
			best_err = error;
			printf("New best found: %.24lf\n", best_err);
			k++;
		}
		if (!(i & 0x3fff)) {
			update_loading_text(count, iterations);
		}
		count++;
	}
	dummyMethod2();
	printf("\r                            \r"); // clear line
	printf("100 percent done");
	fflush(stdout);
	printf("\nBest curve:\n\n");
	printf("(x * (x * (x * (x * (x * %.14lf + %.14lf) + %.14lf) + %.14lf) + %.14lf))\n", ba, bb, bc, bd, be);
	printf("This curve has an error of %.24lf\n", best_err);
	printf("Coefficients:\n");
	printf("double ba = %.14lf;\n", ba);
	printf("double bb = %.14lf;\n", bb);
	printf("double bc = %.14lf;\n", bc);
	printf("double bd = %.14lf;\n", bd);
	printf("double be = %.14lf;\n", be);
	// Although the program generates curves that fit better than the current "best",
	// the better curves produce the same output when used to generate sRGB values.
	// e.g the slight difference in precision is not noticeable at all.
	getchar();
	return 0;
}
#else
// Implementation
#define p1 0.10873973553402
#define p2 -0.41010089485266
#define p3 0.88302559523380
#define p4 0.43158621006073
#define p5 -0.01325064597589
/*
	Approximation of pow(x, 2.4) using a 5th degree polynomial.
	This curve has an error of around 0.00000051791320
*/
#define powapprox(x) ((x) * ((x) * ((x) * ((x) * ((x) * p1 + p2) + p3) + p4) + p5))

#define round(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))
#define S4(i)    S1((i)),   S1((i)+1),     S1((i)+2),     S1((i)+3)
#define S16(i)   S4((i)),   S4((i)+4),     S4((i)+8),     S4((i)+12)
#define S64(i)   S16((i)),  S16((i)+16),   S16((i)+32),   S16((i)+48)
#define S256(i)  S64((i)),  S64((i)+64),   S64((i)+128),  S64((i)+192)
#define srgb2lin(i) (round(((i) < 0.04045 ? ((i) / 12.92) : powapprox((((i) + 0.055) / 1.055))) * 65535.0))

uint16_t SRGB_TO_LINEAR[256] = {
#define S1(i) (srgb2lin((i) / 255.0))
	S256(0)
#undef S1
};

#define actual(i) (round(((i) < 0.04045 ? ((i) / 12.92) : pow((((i) + 0.055) / 1.055), 2.4)) * 65535.0))

int main(void) {
	for (int i = 0; i < 256; i++) {
		uint16_t apx = SRGB_TO_LINEAR[i];
		uint16_t act = (uint16_t) actual(i / 255.0);
		printf("Approx: %04x Actual: %04x Difference: %d\n", apx, act, apx - act);
	}
	getchar();
	return 0;
}
#endif
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