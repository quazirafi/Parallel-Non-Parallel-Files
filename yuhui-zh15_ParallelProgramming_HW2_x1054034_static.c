/* 
	File: Sequential Mandelbort Set
	Author: Zhang Yuhui
	Email: yuhui-zh15@mails.tsinghua.edu.cn
	Description: Non-dynamic 
 */

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <mpi.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef struct complextype { double real, imag; } Compl;

int main(int argc, char* argv[])
{
	/* init */
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int thread_num = atoi(argv[1]); 
	double realaxis_left = atof(argv[2]);
	double realaxis_right = atof(argv[3]);
	double imageaxis_lower = atof(argv[4]);
	double imageaxis_upper = atof(argv[5]);
	int width = atoi(argv[6]);
	int height = atoi(argv[7]);
	char *output = argv[8];
	
	/* calculate points */
	int len = width * height / size;
	if (rank < (width * height % size)) len += 1;
	int *BUF = (int*)malloc(len * sizeof(int)); 
	
	int k;
	dummyMethod1();
	#pragma omp parallel for num_threads(thread_num) schedule(dynamic)
	for(k = 0; k < len; k++) {
		int i = (k * size + rank) / height;
		int j = (k * size + rank) % height;
		Compl z, c;
		z.real = 0.0;
		z.imag = 0.0;
		c.real = realaxis_left + (double)i * ((realaxis_right - realaxis_left) / (double)width);
		c.imag = imageaxis_lower + (double)j * ((imageaxis_upper - imageaxis_lower) / (double)height);
		double lengthc = c.real * c.real + c.imag * c.imag;
		if (lengthc < 0.0625) { BUF[k] = 100000; continue; }
		int repeats = 0;
		double lengthsq = 0.0;
		double temp;
		while(repeats < 100000 && lengthsq <= 4.0) {
			temp = z.real * z.real - z.imag * z.imag + c.real;
			z.imag = 2 * z.real * z.imag + c.imag;
			z.real = temp;
			lengthsq = z.real * z.real + z.imag * z.imag; 
			repeats++;
		}
		BUF[k] = repeats;
	}
	dummyMethod2();
	
	if (rank == 0) {
		FILE *fp;
		int *BUFAll = (int*)malloc((width * height + 2) * sizeof(int));
		BUFAll[0] = width;
		BUFAll[1] = height;
		int i, current_rank;
			dummyMethod4();
			dummyMethod3();
		for (i = 0; i < len; i++) BUFAll[size * i + 2] = BUF[i];
			dummyMethod3();
		for (current_rank = 1; current_rank < size; current_rank++) {
			len = width * height / size;
			if (current_rank < (width * height % size)) len += 1;
			MPI_Recv(BUF, len, MPI_INT, current_rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (i = 0; i < len; i++) BUFAll[current_rank + size * i + 2] = BUF[i];
		}
			dummyMethod4();
		fp = fopen(output,"wb");
		fwrite(BUFAll, sizeof(int), width * height + 2, fp);
		fclose(fp);
		free(BUFAll);
	}
	else {
		MPI_Send(BUF, len, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	free(BUF);
	MPI_Finalize();
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