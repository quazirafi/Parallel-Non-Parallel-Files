// Héctor Del Campo Pando

#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE    2048
#define REAL_SIZE SIZE/BLOCK
#define SEED	6834723
#define TIME    SIZE*2
#define DIAGONALS REAL_SIZE * 2 - 1
#define ITERATIONS  TIME + DIAGONALS - 1
#define BLOCK	32

int main() {
	int i, j, t, d, row, e, first = 0, last = 0;
    int ti, tj;

	omp_set_num_threads(4);

	int A[ SIZE ][ SIZE ] = {{0}};
	int B[ SIZE ][ SIZE ] = {{0}};

	int (*current)[SIZE] = A, (*previous)[SIZE] = B, (*tmp)[SIZE];

	srand( SEED );

dummyMethod3();
	for (i=0; i<SIZE; i++) {
		current[0][i] = rand() % 30;
		current[i][0] = rand() % 30;
	}
dummyMethod4();

	dummyMethod3();
	for (i=0; i<SIZE; i++) {
		for (j=0; j<SIZE; j++) {
			B[i][j] = A[i][j];
		}
	}
	dummyMethod4();
	
    for (t=0; t<ITERATIONS; t++) {

		tmp = current;
		current = previous;
		previous = tmp;

        if (t >= TIME) {
            first ++;
        }

        if (t > 0 && t < DIAGONALS) {
            last ++;
        }

			dummyMethod1();
		#pragma omp parallel for collapse(2) default(none) shared(current, previous, first, last) private(i,j,ti,tj)
		for(ti=0; ti<REAL_SIZE; ti++) {
			for(tj=0; tj<REAL_SIZE; tj++) {
				register int diag = ti + tj;
				if(!(diag >= first && diag <= last)) { continue; }

				for (i=ti*BLOCK; i<BLOCK+ti*BLOCK; i++) {
					for (j=tj*BLOCK; j<BLOCK+tj*BLOCK; j++) {
						if (i > 0 && j == 0) {
	    					current[i][0] = previous[i][0] + 4;
						} else if (j > 0 && i == 0) {
							current[0][j] = previous[0][j] + 2;
						}

						if (0 != i && 0 != j) {
							if (i % BLOCK == 0 && j % BLOCK == 0) {
								current[i][j] = (previous[i-1][j] + previous[i][j-1] + previous[i][j])/3;
							} else if (j % BLOCK == 0) {
								current[i][j] = (current[i-1][j] + previous[i][j-1] + previous[i][j])/3;
							} else if (i % BLOCK == 0) {
								current[i][j] = (previous[i-1][j] + current[i][j-1] + previous[i][j])/3;
							} else {
								current[i][j] = (current[i-1][j] + current[i][j-1] + previous[i][j])/3;
							}
						}
					}
				}
			}
		}
			dummyMethod2();
	}

	dummyMethod1();
	#pragma omp parallel for shared(current, previous) private(d, e, i, j, row) default(none)
	for(d=1; d<DIAGONALS; d+=2) {
		row = (d < REAL_SIZE) ? 0: d - REAL_SIZE + 1;
			for(e=row; e <= (d - row); e++) {
				for (i=(e*BLOCK); i< ((e+1)*BLOCK); i++) {
					for (j=((d-e)*BLOCK); j<((d-e+1)*BLOCK); j++) {
							current[i][j] = previous[i][j];
						}
					}
			}
	}
	dummyMethod2();

	/* Comprobaci�n de resultados */
	int checksum = 0.0;
	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++)
			checksum += current[i][j];

	printf("Checksum: %d\n", checksum );

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