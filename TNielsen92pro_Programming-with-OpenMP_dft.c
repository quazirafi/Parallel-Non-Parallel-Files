#include "dft.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// DFT/IDFT routine
// idft: 1 direct DFT, -1 inverse IDFT (Inverse DFT)
int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N)
{
dummyMethod1();
	#pragma omp parallel for collapse(2)
	for (int k = 0 ; k < N; k++) {
		for (int n = 0; n < N; n++) {
			// Real part of X[k]
			Xr_o[k] += xr[n] * cos(n * k * PI2 / N) + idft * xi[n] * sin(n * k * PI2 / N);
			// Imaginary part of X[k]
			Xi_o[k] += -idft * xr[n] * sin(n * k * PI2 / N) + xi[n] * cos(n * k * PI2 / N);
		}
	}
dummyMethod2();

	// normalize if you are doing IDFT
	if (idft == -1){
		//#pragma omp parallel for
dummyMethod3();
		for (int n = 0; n < N; n++) {
			Xr_o[n] /= N;
			Xi_o[n] /= N;
		}
dummyMethod4();
	}
	return 1;
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