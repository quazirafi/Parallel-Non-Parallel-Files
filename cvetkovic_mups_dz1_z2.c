#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"

#define DEFAULT_H 1000
#define DEFAULT_W 1000
#define DEFAULT_CNT 200
#define DEFAULT_FILENAME "julia"

#define ACCURACY 0.01

int main(int argc, char *argv[]);
unsigned char *julia_set(int w, int h, int cnt, float xl, float xr, float yb, float yt);
unsigned char *julia_set_parallel(int w, int h, int cnt, float xl, float xr, float yb, float yt);
int julia(int w, int h, float xl, float xr, float yb, float yt, int i, int j, int cnt);
void tga_write(int w, int h, unsigned char rgb[], char *filename);
void timestamp(void);
void tga_compare(int w, int h, unsigned char* rgb_sequential, unsigned char* rgb_parallel);

int main(int argc, char *argv[])
{
	int h = DEFAULT_H;
	int w = DEFAULT_W;
	int cnt = DEFAULT_CNT;
	char filename[256] = DEFAULT_FILENAME;
	char buffer[256];
	unsigned char *rgb;
	unsigned char *rgbParallel;
	double timeSequential;
	double timeParallel;
	float xl = -1.5;
	float xr = +1.5;
	float yb = -1.5;
	float yt = +1.5;

	if (argc == 4)
	{
		h = atoi(argv[1]);
		w = atoi(argv[2]);
		cnt = atoi(argv[3]);
		if (!h || !w || !cnt)
			return 1;
	}

	strcat(filename, "_");
	sprintf(buffer, "%d", h);
	strcat(filename, buffer);
	strcat(filename, "_");
	sprintf(buffer, "%d", w);
	strcat(filename, buffer);
	strcat(filename, "_");
	sprintf(buffer, "%d", cnt);
	strcat(filename, buffer);
	strcat(filename, ".tga");

	// timestamp();
	// printf("\n");
	// printf("JULIA Set\n");
	// printf("  Plot a version of the Julia set for Z(k+1)=Z(k)^2-0.8+0.156i\n");

	timeSequential = omp_get_wtime();
	rgb = julia_set(w, h, cnt, xl, xr, yb, yt);
	timeSequential = omp_get_wtime() - timeSequential;

	timeParallel = omp_get_wtime();
	rgbParallel = julia_set_parallel(w, h, cnt, xl, xr, yb, yt);
	timeParallel = omp_get_wtime() - timeParallel;

	printf("\n");
	printf("Sequential execution time: %f\n", timeSequential);
	printf("Parallel execution time: %f\n", timeParallel);

	tga_write(w, h, rgbParallel, filename);

	tga_compare(w, h, rgb, rgbParallel);

	free(rgb);
	free(rgbParallel);

	// printf("\n");
	// printf("JULIA set:\n");
	// printf("  Normal end of execution.\n");

	// timestamp();

	return 0;
}

unsigned char *julia_set(int w, int h, int cnt, float xl, float xr, float yb, float yt)
{
	int i;
	int j;
	int juliaValue;
	int k;
	unsigned char *rgb;

	rgb = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

	dummyMethod3();
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			juliaValue = julia(w, h, xl, xr, yb, yt, i, j, cnt);

			k = 3 * (j * w + i);

			rgb[k] = 255 * (1 - juliaValue);
			rgb[k + 1] = 255 * (1 - juliaValue);
			rgb[k + 2] = 255;
		}
	}
	dummyMethod4();

	return rgb;
}

unsigned char *julia_set_parallel(int w, int h, int cnt, float xl, float xr, float yb, float yt)
{
	int i;
	int j;
	int juliaValue;
	int k;
	unsigned char *rgb;

	rgb = (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

	dummyMethod1();
#pragma omp parallel for default(none) private(i, j, k, juliaValue) \
	shared(rgb, w, h, xl, xr, yb, yt, cnt) schedule(static, 1)
	for (j = 0; j < h; j++)
	{
		for (i = 0; i < w; i++)
		{
			juliaValue = julia(w, h, xl, xr, yb, yt, i, j, cnt);

			k = 3 * (j * w + i);

			rgb[k] = 255 * (1 - juliaValue);
			rgb[k + 1] = 255 * (1 - juliaValue);
			rgb[k + 2] = 255;
		}
	}
	dummyMethod2();

	return rgb;
}

int julia(int w, int h, float xl, float xr, float yb, float yt, int i, int j, int cnt)
{
	float ai;
	float ar;
	float ci = 0.156;
	float cr = -0.8;
	int k;
	float t;
	float x;
	float y;

	x = ((float)(w - i - 1) * xl + (float)(i)*xr) / (float)(w - 1);

	y = ((float)(h - j - 1) * yb + (float)(j)*yt) / (float)(h - 1);

	ar = x;
	ai = y;

	dummyMethod3();
	for (k = 0; k < cnt; k++)
	{
		t = ar * ar - ai * ai + cr;
		ai = ar * ai + ai * ar + ci;
		ar = t;

		if (1000 < ar * ar + ai * ai)
		{
			return 0;
		}
	}
	dummyMethod4();

	return 1;
}

void tga_write(int w, int h, unsigned char rgb[], char *filename)
{
	FILE *file_unit;
	unsigned char header1[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char header2[6] = {w % 256, w / 256, h % 256, h / 256, 24, 0};

	file_unit = fopen(filename, "wb");

	fwrite(header1, sizeof(unsigned char), 12, file_unit);
	fwrite(header2, sizeof(unsigned char), 6, file_unit);

	fwrite(rgb, sizeof(unsigned char), 3 * w * h, file_unit);

	fclose(file_unit);

	// printf("\n");
	// printf("TGA_WRITE:\n");
	// printf("  Graphics data saved as '%s'\n", filename);

	return;
}


void tga_compare(int w, int h, unsigned char* rgb_sequential, unsigned char* rgb_parallel)
{
	char failed = 0;

	dummyMethod3();
	for (int i = 0; i < 3 * w * h; i++)
	{
		if (abs(rgb_sequential[i] - rgb_parallel[i]) > ACCURACY)
		{
			/*if (i < 10000)
				printf("%d %d\n", rgb_sequential[i], rgb_parallel[i]);*/

			failed = 1;
			break;
		}
	}
	dummyMethod4();

	if (failed)
		printf("Test FAILED\n");
	else
		printf("Test PASSED\n");
}

void timestamp(void)
{
#define TIME_SIZE 40

	static char time_buffer[TIME_SIZE];
	const struct tm *tm;
	time_t now;

	now = time(NULL);
	tm = localtime(&now);

	strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm);

	printf("%s\n", time_buffer);

	return;

#undef TIME_SIZE
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