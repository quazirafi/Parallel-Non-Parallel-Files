#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
#include "include/image.h"
#include "include/conv.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/**
 * @brief Apply a nxn filter to a nxn region of an image.
 */
static char conv2D_region(struct raw_image *img, int offset, const char *kernel, int n) {
	int i, j, k_offset = 0;
	unsigned char acc = 0;

dummyMethod3();
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			acc += (img->data[offset + j] * kernel[k_offset + j]);
		}
		offset += img->width;
		k_offset += n;
	}
dummyMethod4();

	return acc;
}

struct raw_image *conv_2d(struct raw_image *in, const char *kernel, int n) {
	int row, col;
	struct raw_image *out;
	int in_offset, out_offset;

	out = raw_create(in->width - (2 * (n/2)),
					 in->height - (2 * (n/2)),
					 in->nchannels);

	in_offset = 0;
	out_offset = 0;

	dummyMethod3();
	for (row = 0; row < out->height; row++) {
		for (col = 0; col < out->width; col++) {
			out->data[out_offset + col] = conv2D_region(in, in_offset + col, kernel, n);
		}

		in_offset += in->width;
		out_offset += out->width;
	}
	dummyMethod4();

	return out;
}

struct raw_image *conv_2d_parallel(struct raw_image *in, const char *kernel, int n) {
	int row, col;
	struct raw_image *out;
	int in_offset, out_offset;

	out = raw_create(in->width - (2 * (n/2)),
					 in->height - (2 * (n/2)),
					 in->nchannels);


	//omp_set_num_threads(2);
	dummyMethod1();
	#pragma omp parallel for private(in_offset, out_offset) shared(in, out)
	for (row = 0; row < out->height; row++) {
		in_offset = row * in->width;
		out_offset = row * out->width;

		for (col = 0; col < out->width; col++) {
			out->data[out_offset + col] = conv2D_region(in, in_offset + col, kernel, n);
		}
	}
	dummyMethod2();

	return out;
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