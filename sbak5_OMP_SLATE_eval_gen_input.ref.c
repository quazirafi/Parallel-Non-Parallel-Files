#include <sys/time.h>
#include <time.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static unsigned long long current_time_ns() {
#ifdef __MACH__
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    unsigned long long s = 1000000000ULL * (unsigned long long)mts.tv_sec;
    return (unsigned long long)mts.tv_nsec + s;
#else
    struct timespec t ={0,0};
    clock_gettime(CLOCK_MONOTONIC, &t);
    unsigned long long s = 1000000000ULL * (unsigned long long)t.tv_sec;
    return (((unsigned long long)t.tv_nsec)) + s;
#endif
}
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef FP_NUMBER
typedef double FP_NUMBER;
#else
typedef float FP_NUMBER;
#endif


#define GET_RAND_FP ((FP_NUMBER)rand()/((FP_NUMBER)(RAND_MAX)+(FP_NUMBER)(1)))
char L_FNAME[32], U_FNAME[32], A_FNAME[32];

int main (int argc, char **argv){
    int i,j,k,MatrixDim;
    FP_NUMBER sum, *L, *U, *A;
    FILE *fl,*fu,*fa;

    if ( argc < 2) {
        printf("./gen_input [Matrix_Dimension_size]\n");
        return 1;
    }

    MatrixDim = atoi(argv[1]);
    L = (FP_NUMBER *) malloc(sizeof(FP_NUMBER*)*MatrixDim*MatrixDim);
    U = (FP_NUMBER *) malloc(sizeof(FP_NUMBER*)*MatrixDim*MatrixDim);
    A = (FP_NUMBER *) malloc(sizeof(FP_NUMBER*)*MatrixDim*MatrixDim);

    if ( !L || !U || !A){
        printf("Can not allocate memory\n");
        if (L) free(L);
        if (U) free(U);
        if (A) free(A);
        return 1;
    }

    srand(time(NULL));

    sprintf(L_FNAME, "l-%d.dat", MatrixDim);
    fl = fopen(L_FNAME, "wb");
    if (fl == NULL) {
        printf("Cannot open file %s\n", L_FNAME);
        return 1;
    }

    sprintf(U_FNAME, "u-%d.dat", MatrixDim);
    fu = fopen(U_FNAME, "wb");
    if (fu == NULL) {
        printf("Cannot open file %s\n", U_FNAME);
        return 1;
    }

    sprintf(A_FNAME, "%d.dat", MatrixDim);
    fa = fopen(A_FNAME, "wb");
    if (!fa) {
        printf("Cannot open file %s\n", A_FNAME);
        return 1;
    }

 { const unsigned long long parallel_for_start = current_time_ns();
dummyMethod1();
#pragma omp parallel for default(none) private(i,j) shared(L,U,MatrixDim)
for (i=0; i < MatrixDim; i ++){
        for (j=0; j < MatrixDim; j++){
            if ( i == j) {
                L[i * MatrixDim + j] = 1.0;
                U[i * MatrixDim + j] = GET_RAND_FP;
            } else if (i < j){
                L[i * MatrixDim + j] = 0;
                U[i * MatrixDim + j] = GET_RAND_FP;
            } else { // i > j
                L[i * MatrixDim + j] = GET_RAND_FP;
                U[i * MatrixDim + j] = 0;
            }
        }
    } ; 
dummyMethod2();
const unsigned long long parallel_for_end = current_time_ns();
printf("pragma62_omp_parallel %llu ns\n", parallel_for_end - parallel_for_start); } 


 { const unsigned long long parallel_for_start = current_time_ns();
dummyMethod1();
#pragma omp parallel for default(none) private(i,j,k,sum) shared(L,U,A,MatrixDim)
for (i=0; i < MatrixDim; i++ ) {
        for (j=0; j < MatrixDim; j++){
            sum = 0;
            for(k=0; k < MatrixDim; k++)
                sum += L[i * MatrixDim + k]*U[k * MatrixDim + j];
            A[i * MatrixDim + j] = sum;
        }
    } ; 
dummyMethod2();
const unsigned long long parallel_for_end = current_time_ns();
printf("pragma79_omp_parallel %llu ns\n", parallel_for_end - parallel_for_start); } 


							dummyMethod3();
    for (i=0; i < MatrixDim; i ++) {
        for (j=0; j < MatrixDim; j++)
            fprintf(fl, "%f ", L[i * MatrixDim + j]);
        fprintf(fl, "\n");
    }
							dummyMethod4();
    fclose(fl);

							dummyMethod3();
    for (i=0; i < MatrixDim; i ++) {
        for (j=0; j < MatrixDim; j++)
            fprintf(fu, "%f ", U[i * MatrixDim + j]);
        fprintf(fu, "\n");
    }
							dummyMethod4();
    fclose(fu);

    fprintf(fa, "%d\n", MatrixDim);
							dummyMethod3();
    for (i=0; i < MatrixDim; i ++) {
        for (j=0; j < MatrixDim; j++)
            fprintf(fa, "%f ", A[i * MatrixDim + j]);
        fprintf(fa, "\n");
    }
							dummyMethod4();
    fclose(fa);

    free(L);
    free(U);
    free(A);

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