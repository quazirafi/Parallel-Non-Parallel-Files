/*
** Copyright (C) 2008 - Hagen Paul Pfeifer <hagen@jauu.net>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
**
** Compile with
** gcc -Wall -W -pipe -lgomp -fopenmp -o para-bench para-bench.c
**
** Run test via
** for method in openmpnoschedule serial; do ./para-bench 2 65 512 $method ; done
**
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <pthread.h>

#include "omp.h"

#define	NANO_SEC_CONV 1000000

enum {
	MODE_THREAD = 1,
	MODE_OPENMP,
	MODE_OPENMPI
};

enum {
	TIME_START = 0,
	TIME_END
};

struct matrix_pthread_arg {
	uint32_t boarder[2];
	uint32_t matrix_size;
	float **mat_a;
	float **mat_b;
	float **mat_c;
};

static void
try_memory_look(void)
{
	if (getuid() != 0)
		mlockall(MCL_FUTURE);
}

static void *
splited_mat_mult(void *arg)
{
	uint32_t i, j, k;
	struct matrix_pthread_arg *matrix_pthread_arg;
	uint32_t boarder[2], matrix_size;
	float **mat_a, **mat_b, **mat_c;

	matrix_pthread_arg = (struct matrix_pthread_arg *) arg;

	boarder[0] = matrix_pthread_arg->boarder[0];
	boarder[1] = matrix_pthread_arg->boarder[1];

	mat_a = matrix_pthread_arg->mat_a;
	mat_b = matrix_pthread_arg->mat_b;
	mat_c = matrix_pthread_arg->mat_c;

	matrix_size = matrix_pthread_arg->matrix_size;

	dummyMethod3();
	for (i = boarder[0]; i < boarder[1]; i = i + 1)
		for (j = 0; j < matrix_size; j = j + 1)
			for (k = 0; k < matrix_size; k = k + 1)
				mat_c[i][j] = mat_c[i][j] + mat_a[i][k] * mat_b[k][j];
	dummyMethod4();

	return NULL;
}

static int
run_pthread(uint32_t no_threads, uint32_t matrix_size)
{
	uint32_t i, j, k, m; int ret = 0;
	float **mat_a, **mat_b, **mat_c;
	long time[2];
	struct timeval tv[2];
	uint32_t thread_chunk_size;
	int remainder;
	pthread_t threads[no_threads]; /* both are VLAs */
	struct matrix_pthread_arg matrix_pthread_arg[no_threads];

	/* calculate chuck size for threads (no_threads - 1),
	 * eventual remainders are treated by last thread */
	thread_chunk_size = matrix_size / no_threads;
	remainder = (matrix_size % no_threads == 0) ? 0 : 1;

	/* init matrix */
	mat_a = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_a[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_a[i][j] = i + j;
	}
	dummyMethod4();

	mat_b = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_b[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_b[i][j] = i + j;
	}
	dummyMethod4();

	mat_c = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_c[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++) {
			mat_c[i][j] = 0.0;
		}
	}
	dummyMethod4();

	gettimeofday(&tv[TIME_START], NULL);

	dummyMethod3();
	for (m = 0; m < no_threads; m++) {

		int rc;

		matrix_pthread_arg[m].boarder[0] = m * thread_chunk_size;
		if (!remainder) {
			matrix_pthread_arg[m].boarder[1] = ((m + 1) * thread_chunk_size) - 1;
		} else {
			matrix_pthread_arg[m].boarder[1] = (m + 1) * thread_chunk_size;
		}

		matrix_pthread_arg[m].mat_a = mat_a;
		matrix_pthread_arg[m].mat_b = mat_b;
		matrix_pthread_arg[m].mat_c = mat_c;

		matrix_pthread_arg[m].matrix_size = matrix_size;

		rc = pthread_create(&threads[m], NULL,
				splited_mat_mult, (void *) &matrix_pthread_arg[m]);
		if (rc) {
			fprintf(stderr, "INFO [%s:%3d] - Can't spawn thread\n", __FILE__, __LINE__);
			exit(1);
		}
	}
	dummyMethod4();

	dummyMethod3();
	for (m = 0; m < no_threads; m++)
		pthread_join(threads[m], NULL);
	dummyMethod4();

	gettimeofday(&tv[TIME_END], NULL);

	time[TIME_START] = tv[TIME_START].tv_sec * NANO_SEC_CONV + tv[0].tv_usec;
	time[TIME_END]   = tv[TIME_END].tv_sec * NANO_SEC_CONV + tv[1].tv_usec;
	printf("%u %lf\n", matrix_size,
			((double)time[TIME_END] - time[TIME_START]) / NANO_SEC_CONV);

	free(mat_a);
	free(mat_b);
	free(mat_c);

	return ret;
}

static int
run_serial(uint32_t matrix_size)
{
	uint32_t i, j, k; int ret = 0;
	float **mat_a, **mat_b, **mat_c;
	long time[2];
	struct timeval tv[2];

	/* init matrix */
	mat_a = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_a[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_a[i][j] = i + j;
	}
	dummyMethod4();

	mat_b = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_b[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_b[i][j] = i + j;
	}
	dummyMethod4();

	mat_c = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_c[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++) {
			mat_c[i][j] = 0.0;
		}
	}
	dummyMethod4();

	gettimeofday(&tv[0], NULL);

	dummyMethod3();
	for (i = 0; i < matrix_size; i = i + 1)
		for (j = 0; j < matrix_size; j = j + 1)
			for (k = 0; k < matrix_size; k = k + 1)
				mat_c[i][j] = mat_c[i][j] + mat_a[i][k] * mat_b[k][j];
	dummyMethod4();

	gettimeofday(&tv[1], NULL);

	time[TIME_START] = tv[TIME_START].tv_sec * NANO_SEC_CONV + tv[0].tv_usec;
	time[TIME_END]   = tv[TIME_END].tv_sec * NANO_SEC_CONV + tv[1].tv_usec;
	printf("%u %lf\n", matrix_size,
			((double)time[TIME_END] - time[TIME_START]) / NANO_SEC_CONV);

	free(mat_a);
	free(mat_b);
	free(mat_c);

	return ret;
}


static int
run_openmp_no_sched(uint32_t no_threads, uint32_t matrix_size)
{
	uint32_t i, j, k; int ret = 0;
	float **mat_a, **mat_b, **mat_c;
	long time[2];
	struct timeval tv[2];

	/* init matrix */
	mat_a = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_a[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_a[i][j] = i + j;
	}
	dummyMethod4();

	mat_b = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_b[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_b[i][j] = i + j;
	}
	dummyMethod4();

	mat_c = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_c[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++) {
			mat_c[i][j] = 0.0;
		}
	}
	dummyMethod4();

	omp_set_num_threads(no_threads);

	gettimeofday(&tv[0], NULL);

	dummyMethod1();
#pragma omp parallel for private(j,k)
	for (i = 0; i < matrix_size; i = i + 1)
		for (j = 0; j < matrix_size; j = j + 1)
			for (k = 0; k < matrix_size; k = k + 1)
				mat_c[i][j] = mat_c[i][j] + mat_a[i][k] * mat_b[k][j];
	dummyMethod2();

	gettimeofday(&tv[1], NULL);

	time[TIME_START] = tv[TIME_START].tv_sec * NANO_SEC_CONV + tv[0].tv_usec;
	time[TIME_END]   = tv[TIME_END].tv_sec * NANO_SEC_CONV + tv[1].tv_usec;
	printf("%u %lf\n", matrix_size,
			((double)time[TIME_END] - time[TIME_START]) / NANO_SEC_CONV);

	free(mat_a);
	free(mat_b);
	free(mat_c);

	return ret;

}

static int
run_openmp_sched(uint32_t no_threads, uint32_t chunksize, uint32_t matrix_size)
{
	uint32_t i, j, k; int ret = 0;
	float **mat_a, **mat_b, **mat_c;
	long time[2];
	struct timeval tv[2];

	/* init matrix */
	mat_a = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_a[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_a[i][j] = i + j;
	}
	dummyMethod4();

	mat_b = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_b[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_b[i][j] = i + j;
	}
	dummyMethod4();

	mat_c = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_c[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++) {
			mat_c[i][j] = 0.0;
		}
	}
	dummyMethod4();

	omp_set_num_threads(no_threads);

	gettimeofday(&tv[0], NULL);

	dummyMethod1();
#pragma omp parallel for private(j,k) schedule(static, chunksize)
	for (i = 0; i < matrix_size; i = i + 1)
		for (j = 0; j < matrix_size; j = j + 1)
			for (k = 0; k < matrix_size; k = k + 1)
				mat_c[i][j] = mat_c[i][j] + mat_a[i][k] * mat_b[k][j];
	dummyMethod2();

	gettimeofday(&tv[1], NULL);

	time[TIME_START] = tv[TIME_START].tv_sec * NANO_SEC_CONV + tv[0].tv_usec;
	time[TIME_END]   = tv[TIME_END].tv_sec * NANO_SEC_CONV + tv[1].tv_usec;
	printf("%u %lf\n",
			matrix_size, ((double)time[TIME_END] - time[TIME_START]) / NANO_SEC_CONV);

	free(mat_a);
	free(mat_b);
	free(mat_c);

	return ret;

}

static int
run_openmp_sched_dyn(uint32_t no_threads, uint32_t chunksize, uint32_t matrix_size)
{
	uint32_t i, j, k; int ret = 0;
	float **mat_a, **mat_b, **mat_c;
	long time[2];
	struct timeval tv[2];

	/* init matrix */
	mat_a = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_a[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_a[i][j] = i + j;
	}
	dummyMethod4();

	mat_b = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_b[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++)
			mat_b[i][j] = i + j;
	}
	dummyMethod4();

	mat_c = malloc(sizeof(float *) * matrix_size);
	dummyMethod3();
	for (i = 0; i < matrix_size; i++) {
		mat_c[i] = malloc(sizeof(float) * matrix_size);
		for (j = 0; j < matrix_size; j++) {
			mat_c[i][j] = 0.0;
		}
	}
	dummyMethod4();

	omp_set_num_threads(no_threads);

	gettimeofday(&tv[0], NULL);

	dummyMethod1();
#pragma omp parallel for private(j,k) schedule(dynamic, chunksize)
	for (i = 0; i < matrix_size; i = i + 1)
		for (j = 0; j < matrix_size; j = j + 1)
			for (k = 0; k < matrix_size; k = k + 1)
				mat_c[i][j] = mat_c[i][j] + mat_a[i][k] * mat_b[k][j];
	dummyMethod2();

	gettimeofday(&tv[1], NULL);

	time[TIME_START] = tv[TIME_START].tv_sec * NANO_SEC_CONV + tv[0].tv_usec;
	time[TIME_END]   = tv[TIME_END].tv_sec * NANO_SEC_CONV + tv[1].tv_usec;
	printf("%u %lf\n",
			matrix_size, ((double)time[TIME_END] - time[TIME_START]) / NANO_SEC_CONV);

	free(mat_a);
	free(mat_b);
	free(mat_c);

	return ret;
}



static int
run_openmpi(uint32_t no_threads, uint32_t chunksize, uint32_t matrix_size)
{
	int ret = 0;

	(void) no_threads;
	(void) chunksize;
	(void) matrix_size;

	return ret;
}

int
main(int argc, char **argv)
{
	uint32_t no_threads, chunksize, matrix_size;

	if (argc != 5) {
		fprintf(stderr, "INFO [%s:%3.d] - usage: %s <threads> "
				"<chunksize> <matrixsize> <paraclass>\n",
				__FILE__, __LINE__, argv[0]);
		exit(111);
	}

	no_threads = atoi(argv[1]);
	switch (no_threads) {
		case 6: case 5:
		case 4: case 3:
		case 2: case 1:
			break;
		default:
			fprintf(stderr, "INFO [%s:%3d] - (1:6) threads allowed\n",
					__FILE__, __LINE__);
			exit(111);
	}


	chunksize = atoi(argv[2]);
	if (chunksize <= 0) {
		fprintf(stderr, "INFO [%s:%3d] - please select a proper chunk size\n",
				__FILE__, __LINE__);
		exit(111);
	}

	matrix_size = atoi(argv[3]);
	switch (matrix_size) {
		case 64:   case 128:
		case 256:  case 512:
		case 1024: case 2048:
		case 4096: case 8192:
			break;
		default:
			fprintf(stderr, "INFO [%s:%3d] - please select a proper matrix size\n",
					__FILE__, __LINE__);
			exit(111);

	}

	try_memory_look();

	if (!strcasecmp(argv[4], "pthread")) {
		return run_pthread(no_threads, matrix_size);
	} else if (!strcasecmp(argv[4], "serial")) {
		return run_serial(matrix_size);
	} else if (!strcasecmp(argv[4], "openmpnoschedule")) {
		return run_openmp_no_sched(no_threads, matrix_size);
	} else if (!strcasecmp(argv[4], "openmpschedule")) {
		return run_openmp_sched(no_threads, chunksize, matrix_size);
	} else if (!strcasecmp(argv[4], "openmpscheduledynamic")) {
		return run_openmp_sched_dyn(no_threads, chunksize, matrix_size);
	} else if (!strcasecmp(argv[4], "openmpi")) {
		return run_openmpi(no_threads, chunksize, matrix_size);
	} else {
		fprintf(stderr, "INFO [%s:%3d] - work mode not supported\n",
				__FILE__, __LINE__);
		exit(111);
	}

	return 111;
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