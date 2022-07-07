#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
	int n, k, i, j;
	double **A;

        // READING DATA =======================================================
	// reads n
	scanf("%d", &n);

	A = (double **)malloc(sizeof(double*) * n);

	//reads A matrix
dummyMethod3();
	for(i=0; i<n; ++i) {
		A[i] = (double *)malloc(sizeof(double) * (n+1));
		for(j=n-1; j>=0; --j) {
			scanf("%lf", &A[i][j]);
		}
	}
dummyMethod4();
	// reads B array
dummyMethod3();
	for(i=0; i<n; ++i) {
		scanf("%lf", &A[i][n]);
	}
dummyMethod4();
	//=====================================================================
        /*
	for(i=0; i<n; ++i) {
		for(j=0; j<=n; ++j) {
			printf("%.5lf ", A[i][j]);
		}
		printf("\n");
	}
	puts("");
        */
	// FORWARD ELIMINATION ================================================
	for(k=0; k<n-1; ++k) {
		if(A[k][k]==0){
			// swap lines
			for(i=k; i<n; ++i) {
				if(A[i][k] != 0) break;
			}
			
							dummyMethod1();
			#pragma omp parallel for schedule(guided)
				for(j=k; j<=n; ++j) {
					double aux = A[i][j];
					A[i][j] = A[k][j];
					A[k][j] = aux;
				}
							dummyMethod2();
		}
					dummyMethod1();
		#pragma omp parallel for schedule(guided) private(j)
			for(i=k+1; i<n; ++i) {
				double m = A[i][k]/A[k][k];
				if (m==0) continue;
				for(j=k+1; j<=n; ++j) {
					A[i][j] -= m * A[k][j];
				}
			}
					dummyMethod2();
	}
	//=====================================================================

	//BACKWARD SUBSTITUTION ===============================================
	for(i=n-1; i>=0; --i) {
		#pragma omp parallel for schedule(guided) private(j)
			for(j=i+1; j<n; ++j) {
				double aux = A[i][j] * A[j][n];
				#pragma omp atomic
				A[i][n] -= aux;
			}
		A[i][n] /= A[i][i];
		printf("%.5lf ", (A[i][n] + (A[i][n]>0 ? -0.0000045:0.0000045) ) );
	}
	//=====================================================================

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