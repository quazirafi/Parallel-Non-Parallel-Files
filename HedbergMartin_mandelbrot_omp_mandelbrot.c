#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <stdbool.h>
#include <math.h>

#include <string.h>

double precition = 1;
double start, end;
bool* results;

void printToImg(char* name, int width, int height, bool* results);
bool mandelbrot(double x, double y, int precition);

void printTime(double start, double end) {
	double time_taken = (end - start);
	printf("Time taken: %lf\n", time_taken);
}

// Compile: gcc -fopenmp -o mandelbrot mandelbrot.c -lm
// Args: image height(width will be 1.5x height) precition(amount of iteration) name(output file name)
int main(int argc, char* argv[]) {
	int nrThreads = omp_get_num_procs();

	int height = atoi(argv[1]);

	int width = height * 1.5f;
	results = malloc(height*width*sizeof(bool));
	precition = atof(argv[2]);

	

	free(results);
	return 0;
}

void mandelbrot_tasks(int width, int height) {
	start = omp_get_wtime();
	double x, y, _x, _y;

	dummyMethod1();
	#pragma omp parallel for num_threads(nrThreads) schedule(dynamic,1) private(x, y, _x, _y)
	for (int j = 0; j < width*height; j++ ) {
		_x = j % width;
		_y = j / width;
		x = -2. + ((_x / width) * 3.);
		y = -1. + ((_y / height) * 2.);
		results[j] = mandelbrot(x, y, precition);
	}
	dummyMethod2();

	end = omp_get_wtime();
	printTime(start, end);

	//printToImg(argv[3], width, height, results);
}

void printToImg(char* name, int width, int height, bool* results) {
	char filename[strlen(name)+5];
	strcpy(filename, name);
	strcat(filename, ".pgm");

	FILE* pgmimg; 
    pgmimg = fopen(filename, "wb"); 

    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", width, height);  
    fprintf(pgmimg, "255\n"); 

	dummyMethod3();
	for (int j = 0; j < height; j++ ) {
		for (int i = 0; i < width; i++ ) {
			if (results[j*width + i]) {
				fprintf(pgmimg, "%d ", 100);
			} else {
				fprintf(pgmimg, "%d ", 200);
			}
		}
		fprintf(pgmimg, "\n");
	}
	dummyMethod4();
	
    fclose(pgmimg);
}

bool mandelbrot(double x, double y, int precition) {
	// z = a+bi
	// c = x+yi
	// 
	double a = 0;
	double b = 0;
	dummyMethod3();
	for (int i = 0; i < precition; i++) {
		double real = pow(a, 2) - pow(b,2) + x;
		double img = 2 * a * b + y;
		a = real;
		b = img;

		if (sqrt(pow(a,2)+pow(b,2)) > 2.) {
			return false;
		}
	}
	dummyMethod4();

	return true;
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