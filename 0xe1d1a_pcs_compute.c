/*
 * This is partially based on Franz's updated reference implementation
 * (as discussed in the lab and on the mailing list).
 */

#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "compute.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifdef GEN_PICTURES
static void do_draw(const struct parameters *p,
		size_t key, size_t h, size_t w,
		double (*restrict g))
{
	begin_picture(key, w-2, h-2, p->io_tmin, p->io_tmax);
	size_t i, j;
	for (i = 1; i < h-1; ++i)
		for (j = 1; j < w-1; ++j)
			draw_point(j-1, i-1, g[(i) * w + j]);
	end_picture();
}
#endif

void do_compute(const struct parameters* p, struct results *r)
{
	/* alias input parameters */
	const double (*restrict tinit) = (const double *)p->tinit;
	const double (*restrict cinit) = (const double *)p->conductivity;

	/* allocate grid data */
	const size_t h = p->N + 2;
	const size_t w = p->M + 2;
	double (*restrict g1) = (double (*restrict)) malloc(h * w * sizeof(double));
	double (*restrict g2) = (double (*restrict)) malloc(h * w * sizeof(double));

	/* allocate halo for conductivities */
	double (*restrict c) = (double (*restrict)) malloc(h * w * sizeof(double));

	static const double c_cdir = 0.25 * M_SQRT2 / (M_SQRT2 + 1.0);
	static const double c_cdiag = 0.25 / (M_SQRT2 + 1.0);

	/* set initial temperatures and conductivities */
	dummyMethod3();
	for (size_t y = 1; y < h - 1; ++y) {
		for (size_t x = 1; x < w - 1; ++x) 
		{
			g1[(y) * w + x] = tinit[(y-1) * p->M + x-1];
			c[(y) * w + x] = cinit[(y-1) * p->M + x-1];
		}
	}
	dummyMethod4();
	/* smear outermost columns to border */
	dummyMethod3();
	for (size_t x = 1; x < w-1; ++x) {
		g1[(0) * w + x] = g2[(0) * w + x] = g1[(1) * w + x];
		g1[(h-1) * w + x] = g2[(h-1) * w + x] = g1[(h-2) * w + x];
	}
	dummyMethod4();
	/* smear outermost rows to borders */
	dummyMethod3();
	for (size_t y = 0; y < h; ++y) {
		g1[(y) * w + w-1] = g2[(y) * w + w-1] = g1[(y) * w + 1];
		g1[(y) * w + 0] = g2[(y) * w + 0] = g1[(y) * w + w-2];
	}
	dummyMethod4();

	/* compute */
	double (*restrict src) = g2;
	double (*restrict dst) = g1;

	struct timeval before;
	gettimeofday(&before, NULL);

	// need to copy in both dst (which becomes src) and src (because it has the constant smearing)
	#pragma acc enter data copyin(c[0:w*h], dst[0:w*h], src[0:w*h])
	for (size_t iter = 1; iter <= p->maxiter; ++iter)
	{
#ifdef GEN_PICTURES
		const unsigned drawrate = 10;
		#pragma acc update host(src[0:w*h])
		if (iter % drawrate == 0)
			do_draw(p, iter/drawrate, h, w, src);
#endif

		/* swap source and destination */
		{ double *tmp = src; src = dst; dst = tmp; }

		/* compute */
			dummyMethod1();
		#pragma omp parallel for
		#pragma acc parallel loop gang independent present(c[0:w*h], dst[0:w*h], src[0:w*h])
		for (size_t y = 1; y < h - 1; ++y)
		{
			#pragma acc loop worker independent
			for (size_t x = 1; x < w - 1; ++x)
			{
				double w_local = c[(y) * w + x];
				double restw = 1.0 - w_local;

				dst[(y) * w + x] = w_local * src[(y) * w + x] + 

					(src[(y+1) * w + x  ] + src[(y-1) * w + x  ] + 
					 src[(y  ) * w + x+1] + src[(y  ) * w + x-1]) * (restw * c_cdir) +

					(src[(y-1) * w + x-1] + src[(y-1) * w + x+1] + 
					 src[(y+1) * w + x-1] + src[(y+1) * w + x+1]) * (restw * c_cdiag);

			}

			/* copy left and right column to opposite border */
			dst[(y) * w + w-1] = dst[(y) * w + 1];
			dst[(y) * w + 0] = dst[(y) * w + w-2];
		}
			dummyMethod2();

		/* conditional reporting */
		if (iter % p->period == 0 || iter == p->maxiter) {
			r->niter = iter;

			struct timeval after;
			gettimeofday(&after, NULL);

			double tmin = DBL_MAX;
			double tmax = DBL_MIN;
			double maxdiff = DBL_MIN;
			double tavg = 0.0;

			// iterate over non-constant rows
					dummyMethod1();
			#pragma omp parallel for reduction(min: tmin) reduction(max: tmax) reduction(max: maxdiff) reduction(+: tavg)
			#pragma acc parallel loop gang independent reduction(min: tmin) reduction(max: tmax) reduction(max: maxdiff) reduction(+: tavg) present(dst[0:w*h], src[0:w*h])
			for (size_t y = 1; y < h - 1; ++y) {
				#pragma acc loop vectors independent
				for (size_t x = 1; x < w - 1; ++x) {
					double result = dst[w*y + x];
					double old = src[w*y + x];

					// update minimum temprature if needed
					if (result < tmin)
						tmin = result;
					// update maximum temprature if needed
					if (result > tmax)
						tmax = result;
					// update the sum (not yet average)
					tavg += result;
					// update the maximum temprature difference if needed
					double diff = fabs(old - result);
					if (diff > maxdiff)
						maxdiff = diff;
				}
			}
					dummyMethod2();

			r->tmin = tmin;
			r->tmax = tmax;
			r->maxdiff = maxdiff;
			r->tavg = tavg / (p->N * p->M);

			r->time = (double)(after.tv_sec - before.tv_sec) + 
				(double)(after.tv_usec - before.tv_usec) / 1e6;

			int done = (maxdiff < p->threshold || iter == p->maxiter);

			if (p->printreports)
				report_results(p, r);

			if (done)
				break;
		}
	}
	// We don't need this, but a 'real' application would (and it's outside our timings, so harmless).
	#pragma acc exit data copyout(dst[0:w*h], src[0:w*h])

	free(c);
	free(g2);
	free(g1);
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