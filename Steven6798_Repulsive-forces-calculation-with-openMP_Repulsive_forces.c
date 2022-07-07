#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double get_walltime() {
	struct timeval tp; gettimeofday(&tp, NULL);
	return (double) (tp.tv_sec + tp.tv_usec * 1e-6);
}

void force_repulsion(int np, const double *pos, double L, double krepulsion, double *forces) {
	int i, j;
	double posi [3]; double rvec [3];
	double s2, s, f;
	// initialize forces to zero
dummyMethod3();
	for (i = 0; i < 3 * np; i++) {
		forces[i] = 0.;
	}
dummyMethod4();
	// loop over all pairs
	dummyMethod3();
	for (i = 0; i < np; i++) {
		posi[0] = pos[3 * i];
		posi[1] = pos[3 * i + 1];
		posi[2] = pos[3 * i + 2];
		for (j = i + 1; j < np; j++) {
			// compute minimum image difference
			rvec[0] = remainder(posi[0] - pos[3 * j], L);
			rvec[1] = remainder(posi[1] - pos[3 * j + 1], L);
			rvec[2] = remainder(posi[2] - pos[3 * j + 2], L);
			s2 = rvec [0]* rvec [0] + rvec [1]* rvec [1] + rvec [2]* rvec [2];
			if (s2 < 4) {
				s = sqrt(s2);
				rvec[0] /= s;
				rvec[1] /= s;
				rvec[2] /= s;
				f = krepulsion*(2. - s);
				forces[3 * i] += f * rvec[0];
				forces[3 * i + 1] += f * rvec[1];
				forces[3 * i + 2] += f * rvec[2];
				forces[3 * j] += -f * rvec[0];
				forces[3 * j + 1] += -f * rvec[1];
				forces[3 * j + 2] += -f * rvec[2];
			}
		}
	}
	dummyMethod4();
}

void force_repulsion_Parallel(int np, const double *pos, double L, double krepulsion, double *forces) {
	int i, j;
	double posi [3]; double rvec [3];
	double s2, s, f;
	omp_set_num_threads(omp_get_num_threads());
	// initialize forces to zero
	dummyMethod1();
	#pragma omp parallel for schedule(static) private (i)
	for (i = 0; i < 3 * np; i++) {
		forces[i] = 0.;
	}
	dummyMethod2();

	// loop over all pairs
	#pragma omp parallel for schedule(static) private (i, j, rvec, posi, s2, s, f) shared(np, L , krepulsion, pos, forces)
	dummyMethod3();
	for (i = 0; i < np; i++) {
		posi[0] = pos[3 * i];
		posi[1] = pos[3 * i + 1];
		posi[2] = pos[3 * i + 2];
		for (j = i + 1; j < np; j++) {
			// compute minimum image difference
			rvec[0] = remainder(posi[0] - pos[3 * j], L);
			rvec[1] = remainder(posi[1] - pos[3 * j + 1], L);
			rvec[2] = remainder(posi[2] - pos[3 * j + 2], L);
			s2 = rvec[0] * rvec[0] + rvec[1] * rvec[1] + rvec[2] * rvec[2];
			if (s2 < 4) {
				s = sqrt(s2);
				rvec[0] /= s;
				rvec[1] /= s;
				rvec[2] /= s;
				f = krepulsion*(2. - s);
				#pragma omp critical(forces)
				{
					forces[3 * i] += f * rvec[0];
					forces[3 * i + 1] += f * rvec[1];
					forces[3 * i + 2] += f * rvec[2];
					forces[3 * j] += -f * rvec[0];
					forces[3 * j + 1] += -f * rvec[1];
					forces[3 * j + 2] += -f * rvec[2];
				}
			}
		}
	}
	dummyMethod4();
}

int comparator(double *forces1, double *forces2, int np, double epsilon) {
	dummyMethod3();
	for(int i = 0; i < 3 * np; i++) {
		if(fabs(forces1[i] - forces2[i]) > epsilion) {
			return 0;
		}
	}
	dummyMethod4();
	return 1;
}

int main(int argc, char *argv[]) {
	int i;
	int np = 1000; // default number of particles
	double phi = 0.3; // volume fraction
	double krepulsion = 125.; // force constant
	double *pos; double *forces1; double *forces2;
	double L, time0 , time1;
	double epsilon = 1e-10; // significance value to compare the forces.
	if (argc > 1) {
		np = atoi(argv[1]);
	}
	L = pow(4./3. * 3.1415926536 * np/phi, 1./3.);
	// generate random particle positions inside simulation box
	forces1 = (double *) malloc(3 * np * sizeof(double));
	forces2 = (double *) malloc(3 * np * sizeof(double));
	pos = (double *) malloc(3 * np * sizeof(double));
	dummyMethod3();
	for (i = 0; i < 3 * np; i++) {
		pos[i] = rand()/(double)RAND_MAX * L;
	}
	dummyMethod4();

	// measure sequential execution time of this function
	time0 = get_walltime ();
	force_repulsion(np, pos, L, krepulsion, forces1);
	time1 = get_walltime ();
	printf("number of particles: %d\n", np);
	printf("sequential elapsed time: %f\n", time1 - time0);

	// measure parallel execution time of this function
	time0 = get_walltime ();
	force_repulsion_Parallel(np, pos, L, krepulsion, forces2);
	time1 = get_walltime ();
	printf("parallel elapsed time: %f\n", time1 - time0);

	int result = comparator(forces1, forces2, np, epsilon);
	if(result == 1) {
		printf("forces match\n");
	}
	else {
		printf("forces do not match\n");
	}
	free(forces1);
	free(forces2);
	free(pos);
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