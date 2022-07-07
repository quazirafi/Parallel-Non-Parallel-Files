#include "omp.h"
#include "stencil2d.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void stencil2d_cpu_omp_wrapper(omp_offloading_t *off, int start, int len, long n, long m, int u_dimX, int u_dimY, REAL *u, REAL *uold, int radius, int coeff_dimX, REAL *coeff)
{
#if CORRECTNESS_CHECK
	    	BEGIN_SERIALIZED_PRINTF(off->devseqid);
			printf("udev: dev: %d, %dX%d\n", off->devseqid, n, m);
			print_array_dev("udev", off->devseqid, "u",(REAL*)u, n, m);
			printf("uolddev: dev: %d, %dX%d\n", off->devseqid, uold_0_length, uold_1_length);
			print_array_dev("uolddev", off->devseqid, "uold",(REAL*)uold, uold_0_length, uold_1_length);
			printf("i_start: %d, j_start: %d, n: %d, m: %d, uold_0_offset: %d, uold_1_offset: %d\n", i_start, j_start, n, m, uold_0_offset, uold_1_offset);
			END_SERIALIZED_PRINTF();
#endif
    int count = 4*radius+1;
#ifdef SQUARE_SETNCIL
	count = coeff_dimX * coeff_dimX;
#endif

    int ix, iy, ir;
							dummyMethod1();
#pragma omp parallel for private(ix, iy, ir)
    for (ix = start; ix < start+len; ix++) {
        REAL * temp_u = &u[(ix+radius)*u_dimY+radius];
        REAL * temp_uold = &uold[(ix+radius)*u_dimY+radius];
        #pragma simd
        for (iy = 0; iy < m; iy++) {
//                    if (off->devseqid == 0)printf("dev: %d, [%d][%d]:%f\n", off->devseqid, ix, iy, temp_u[0]);
            REAL result = temp_uold[0] * coeff[0];
/* 2/4 way loop unrolling */
            for (ir = 1; ir <= radius; ir++) {
                result += coeff[ir] * temp_uold[ir];           		//horizontal right
                result += coeff[-ir]* temp_uold[-ir];                  // horizontal left
                result += coeff[-ir*coeff_dimX] * temp_uold[-ir * u_dimY]; //vertical up
                result += coeff[ir*coeff_dimX] * temp_uold[ir * u_dimY]; // vertical bottom
#ifdef SQUARE_SETNCIL
						result += coeff[-ir*coeff_dimX-ir] * temp_uold[-ir * u_dimY-ir] // left upper corner
						result += coeff[-ir*coeff_dimX+ir] * temp_uold[-ir * u_dimY+ir] // right upper corner
						result += coeff[ir*coeff_dimX-ir] * temp_uold[ir * u_dimY]-ir] // left bottom corner
						result += coeff[ir*coeff_dimX+ir] * temp_uold[ir * u_dimY]+ir] // right bottom corner
#endif
            }
            *temp_u = result/count;
            temp_u++;
            temp_uold++;
        }
    }
}
							dummyMethod2();
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