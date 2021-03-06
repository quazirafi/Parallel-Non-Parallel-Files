#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h> /* where intrinsics are defined */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*void sgemm1( int m, int n, float *A, float *C)
{
    for( int i = 0; i < m; i++ )
      for( int k = 0; k < n; k++ ) 
        for( int j = 0; j < m; j++ ) 
        C[i+j*m] += A[i+k*m] * A[j+k*m];
    } */


void sgemm( int m, int n, float *A, float *C)
{   
    int e = m/4*4; //for row's edge case
    int p = n/20*20;
    int q = (n-p)/8*8 + p;
    int w = (n-q)/4*4 + q;
    int km0,km1,km2,km3,km4,km5,km6,km7,km8,km9,km10,km11,km12,km13,km14,km15,km16,km17,km18,km19,j,k,i,mj,km,jm;
    __m128 c0,b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19;
    float *t;  //b
    float *s;  //a
    float *c;  //c 

															dummyMethod1();
    #pragma omp parallel for private(t,s,c,km0,km1,km2,km3,km4,km5,km6,km7,km8,km9,km10,km11,km12,km13,km14,km15,km16,km17,km18,km19,j,k,i,mj,km,jm,c0,b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19)
        for (j=0; j<m; j++) {
            mj = m*j;
            t = A+j;
            c = C+mj;
            //every four column1
            for (k =0; k<p; k+=20){
                km0 = k*m;
                km1 = (k+1)*m;
                km2 = (k+2)*m;
                km3 = (k+3)*m;
                km4 = (k+4)*m;
                km5 = (k+5)*m;
                km6 = (k+6)*m;
                km7 = (k+7)*m;
                km8 = (k+8)*m;
                km9 = (k+9)*m;
                km10 = (k+10)*m;
                km11 = (k+11)*m;
                km12 = (k+12)*m;
                km13 = (k+13)*m;
                km14 = (k+14)*m;
                km15 = (k+15)*m;
                km16 = (k+16)*m;
                km17 = (k+17)*m;
                km18 = (k+18)*m;
                km19 = (k+19)*m;


                b0 = _mm_load1_ps( t + km0 );
                b1 = _mm_load1_ps( t + km1 );
                b2 = _mm_load1_ps( t + km2 );
                b3 = _mm_load1_ps( t + km3 );
                b4 = _mm_load1_ps( t + km4 );
                b5 = _mm_load1_ps( t + km5 );
                b6 = _mm_load1_ps( t + km6 );
                b7 = _mm_load1_ps( t + km7 );
                b8 = _mm_load1_ps( t + km8 );
                b9 = _mm_load1_ps( t + km9 );
                b10 = _mm_load1_ps( t + km10);
                b11 = _mm_load1_ps( t + km11);
                b12 = _mm_load1_ps( t + km12);
                b13 = _mm_load1_ps( t + km13);
                b14 = _mm_load1_ps( t + km14);
                b15 = _mm_load1_ps( t + km15);
                b16 = _mm_load1_ps( t + km16);
                b17 = _mm_load1_ps( t + km17);
                b18 = _mm_load1_ps( t + km18);
                b19 = _mm_load1_ps( t + km19);


                for(i = 0; i<e;i+=4){
                    s = A+i;
                    c0 = _mm_loadu_ps( c+i );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km0 ), b0 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km1 ), b1 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km2 ), b2 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km3 ), b3 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km4 ), b4 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km5 ), b5 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km6 ), b6 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km7 ), b7 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km8 ), b8 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km9 ), b9 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km10 ), b10 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km11 ), b11 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km12 ), b12 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km13 ), b13 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km14 ), b14 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km15 ), b15 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km16 ), b16 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km17 ), b17 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km18 ), b18 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km19 ), b19 ) );

                    _mm_storeu_ps( c + i, c0 );
                }

                for (i = e; i < m; i++) {
                    *(C+i+mj) += *(A+i+km0) * (*(t+km0));
                    *(C+i+mj) += *(A+i+km1) * (*(t+km1));
                    *(C+i+mj) += *(A+i+km2) * (*(t+km2));
                    *(C+i+mj) += *(A+i+km3) * (*(t+km3));
                    *(C+i+mj) += *(A+i+km4) * (*(t+km4));
                    *(C+i+mj) += *(A+i+km5) * (*(t+km5));
                    *(C+i+mj) += *(A+i+km6) * (*(t+km6));
                    *(C+i+mj) += *(A+i+km7) * (*(t+km7));
                    *(C+i+mj) += *(A+i+km8) * (*(t+km8));
                    *(C+i+mj) += *(A+i+km9) * (*(t+km9));
                    *(C+i+mj) += *(A+i+km10) * (*(t+km10));
                    *(C+i+mj) += *(A+i+km11) * (*(t+km11));
                    *(C+i+mj) += *(A+i+km12) * (*(t+km12));
                    *(C+i+mj) += *(A+i+km13) * (*(t+km13));
                    *(C+i+mj) += *(A+i+km14) * (*(t+km14));
                    *(C+i+mj) += *(A+i+km15) * (*(t+km15));
                    *(C+i+mj) += *(A+i+km16) * (*(t+km16));
                    *(C+i+mj) += *(A+i+km17) * (*(t+km17));
                    *(C+i+mj) += *(A+i+km18) * (*(t+km18));
                    *(C+i+mj) += *(A+i+km19) * (*(t+km19));
                }
            }

            for (k =p; k<q; k+=8){
                km0 = k*m;
                km1 = (k+1)*m;
                km2 = (k+2)*m;
                km3 = (k+3)*m;
                km4 = (k+4)*m;
                km5 = (k+5)*m;
                km6 = (k+6)*m;
                km7 = (k+7)*m;


                b0 = _mm_load1_ps( t + km0 );
                b1 = _mm_load1_ps( t + km1 );
                b2 = _mm_load1_ps( t + km2 );
                b3 = _mm_load1_ps( t + km3 );
                b4 = _mm_load1_ps( t + km4 );
                b5 = _mm_load1_ps( t + km5 );
                b6 = _mm_load1_ps( t + km6 );
                b7 = _mm_load1_ps( t + km7 );


                for(i = 0; i<e;i+=4){
                    s = A+i;
                    c0 = _mm_loadu_ps( c+i );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km0 ), b0 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km1 ), b1 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km2 ), b2 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km3 ), b3 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km4 ), b4 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km5 ), b5 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km6 ), b6 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km7 ), b7 ) );

                    _mm_storeu_ps( c + i, c0 );
                }

                for (i = e; i < m; i++) {
                    *(C+i+mj) += *(A+i+km0) * (*(t+km0));
                    *(C+i+mj) += *(A+i+km1) * (*(t+km1));
                    *(C+i+mj) += *(A+i+km2) * (*(t+km2));
                    *(C+i+mj) += *(A+i+km3) * (*(t+km3));
                    *(C+i+mj) += *(A+i+km4) * (*(t+km4));
                    *(C+i+mj) += *(A+i+km5) * (*(t+km5));
                    *(C+i+mj) += *(A+i+km6) * (*(t+km6));
                    *(C+i+mj) += *(A+i+km7) * (*(t+km7));
                }
            }

            for (k =q; k<w; k+=4){
                km0 = k*m;
                km1 = (k+1)*m;
                km2 = (k+2)*m;
                km3 = (k+3)*m;

                b0 = _mm_load1_ps( t + km0 );
                b1 = _mm_load1_ps( t + km1 );
                b2 = _mm_load1_ps( t + km2 );
                b3 = _mm_load1_ps( t + km3 );

                for(i = 0; i<e;i+=4){
                    s = A+i;
                    c0 = _mm_loadu_ps( c+i );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km0 ), b0 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km1 ), b1 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km2 ), b2 ) );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km3 ), b3 ) );

                    _mm_storeu_ps( c + i, c0 );
                }

                for (i = e; i < m; i++) {
                    *(C+i+mj) += *(A+i+km0) * (*(t+km0));
                    *(C+i+mj) += *(A+i+km1) * (*(t+km1));
                    *(C+i+mj) += *(A+i+km2) * (*(t+km2));
                    *(C+i+mj) += *(A+i+km3) * (*(t+km3));
                }
            }

            for (k =w; k<n; k++){
                km0 = k*m;
                b0 = _mm_load1_ps( t + km0 );

                for(i = 0; i<e;i+=4){
                    s = A+i;
                    c0 = _mm_loadu_ps( c+i );
                    c0 = _mm_add_ps( c0, _mm_mul_ps( _mm_loadu_ps( s + km0 ), b0 ) );

                    _mm_storeu_ps( c + i, c0 );
                }

                for (i = e; i < m; i++) {
                    *(C+i+mj) += *(A+i+km0) * (*(t+km0));
                }
            }
        }
															dummyMethod2();
}



/*int main( int argc, char **argv ) {
    int m =41;
    int n = 35,i;

    float *A = (float*)malloc( m*n*sizeof(float) );
    float *C = (float*)malloc( m*m*sizeof(float) );
    float *C1 = (float*)malloc( m*m*sizeof(float) );

    for( i = 0; i < m*n; i++ ) A[i] = (float)rand()/RAND_MAX;
    for( i = 0; i < m*m; i++ ) C[i] = (float) 0.00;
    for( i = 0; i < m*m; i++ ) C1[i] = (float) 0.00;
    
    sgemm(m, n, A, C);
    sgemm1(m, n, A, C1);  

    for( i = 0; i < m*m; i++ ) {
        printf("%d\n", i);
        printf("C1: %f\n ",C1[i]);
        printf("C:%f\n ",C[i]);
        if( C1[i] != C[i]) {
        printf("Error!!!! Transpose does not result in correct answer!!\n");
            exit( -1 );
       }
    }
 
   

    free( A );
    free( C );
    free( C1);
    return 0;
    }*/
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