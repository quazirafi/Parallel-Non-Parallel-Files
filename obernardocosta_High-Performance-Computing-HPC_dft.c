#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef struct _complex {
    double re;
    double im;
} complex;


void dft_seq( complex * out, complex * in, int N ) {
    int k, n;
    complex sum;
dummyMethod3();
    for(k=0; k < N; k++ ) {
        sum.re = 0.; sum.im = 0.; 
        for(n=0; n < N; n++ ) {
            sum.re += in[n].re*cos( (-2.*M_PI*k*n)/N );
            sum.im += in[n].im*sin( (-2.*M_PI*k*n)/N );
        } 
        out[k] = sum;
    }
dummyMethod4();
}

void dft_par( complex * out, complex * in, int N ) {
    int k, n;
    complex sum;

									dummyMethod1();
    #pragma omp parallel for private( k,n,sum )
	    for(k=0; k < N; k++ ) {
	        sum.re = 0.; sum.im = 0.; 
	        for(n=0; n < N; n++ ) {
	            sum.re += in[n].re*cos( (-2.*M_PI*k*n)/N );
	            sum.im += in[n].im*sin( (-2.*M_PI*k*n)/N );
	        } 
	        out[k] = sum;
	    }
									dummyMethod2();
}

int main(int argc, char ** argv ) {
	int i;
	double t0, t1, tt;
    if (argc != 2) {
        fprintf( stderr, "Usage: %s <n>\n", argv[0] );
        exit( -1 );
    }
    int N = atoi( argv[1] );
    complex * out = (complex *) malloc( sizeof( complex ) * N );
    complex * in = (complex *) malloc( sizeof( complex ) * N );
							dummyMethod3();
    for( i = 0; i < N; i++ ) {
        in[i].re = sin( i ); 
    }
							dummyMethod4();
    
    t0 = omp_get_wtime();
    dft_seq( out, in, N );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Sequential          | %8d | %9.2f | %7.2f \n", 1, tt, 1.0);

    
    t0 = omp_get_wtime();
    dft_par( out, in, N );
    t1 = omp_get_wtime();
    tt = t1 - t0;
    printf("Parallel            | %8d | %9.2f | %7.2f \n", 1, tt, 1.0);

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