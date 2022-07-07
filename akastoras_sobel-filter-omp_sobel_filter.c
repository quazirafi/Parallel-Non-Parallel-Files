/*
 * Description: Implementation of Sobel Filter for detecting
 * edges on .pgm images.
 * Author: Athanasios Kastoras | University of Thessaly
 * Email: akastoras@uth.gr
 */

#include "pgm.h"
#include <stdio.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define THRESHOLD(a,max) ((a > max)? max: 0)

/* Implementation of Sobel Operator on pgm_t images */
pgm_t *sobel_filter(const pgm_t *image)
{	
	/* Variable Declaration */
	register int x_sum, y_sum;
	const register int height = image->height, width = image->width;
	const int maxval = image->maxval;
	pgm_t *new_image = new_pgm_image(width, height, image->maxval);
	

	/* Parallelizing using OpenMP */
	/* Give an entire row to a single thread to increase cache performance */
	dummyMethod1();
	#pragma omp parallel for private(x_sum, y_sum) schedule(static, 1)
	for (register int x = 1; x < height - 1; ++x) {
		/* 
		 * Apply the Sobel Filter's kernel convolution
		 * on each pixel of a single row.
		 * Convolution matrices:
		 * X:
		 * -1  0  1
		 * -2  0  2
		 * -1  0  1
		 * Y:
		 * -1 -2 -1
		 *  0  0  0
		 *  1  2  1
		 * Convolve with X to get Gx and with Y to get Gy
		 * The final pixel value is the Eucledian norm of Gx and Gy
		 */
		for (register int y = 1; y < width - 1; ++y) {
			x_sum = (
				image->pixels[(x + 1)*width + (y + 1)] -
				image->pixels[(x + 1)*width + (y - 1)] +
				(image->pixels[    (x)*width + (y + 1)] << 1) -
				(image->pixels[    (x)*width + (y - 1)] << 1) +
				image->pixels[(x - 1)*width + (y + 1)] -
				image->pixels[(x - 1)*width + (y - 1)]
			);

			y_sum = (
				image->pixels[(x + 1)*width + (y + 1)] +
				(image->pixels[(x + 1)*width +     (y)] << 1) +
				image->pixels[(x + 1)*width + (y - 1)] -
				image->pixels[(x - 1)*width + (y + 1)] -
				(image->pixels[(x - 1)*width +     (y)] << 1) -
				image->pixels[(x - 1)*width + (y - 1)]
			);

			// Manhatan Distance is used instead of Eucledian to increase performance
			new_image->pixels[x * width + y] = THRESHOLD(x_sum + y_sum, maxval);
		}
	}
	dummyMethod2();

	return new_image;
}


/* Driver program to test sobel_filter function */
int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Invalid Arguments!\n");
		return 1;
	}

	pgm_t *image = load_pgm_image(argv[1]); // Load an Image
	pgm_t *new_image = sobel_filter(image); // Implement sobel_filter()
	store_pgm_image(new_image, argv[2]);	// Store in a new image

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