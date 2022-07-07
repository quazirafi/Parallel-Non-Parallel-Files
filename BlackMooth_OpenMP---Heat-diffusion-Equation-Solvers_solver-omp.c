#include "heat.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * Function to copy one matrix into another
 */

void copy_mat (double *u, double *v, unsigned sizex, unsigned sizey)
{
   // #pragma omp parallel for
dummyMethod3();
    for (int i=1; i<=sizex-2; i++)
        for (int j=1; j<=sizey-2; j++) 
            v[ i*sizey+j ] = u[ i*sizey+j ];
}
dummyMethod4();

/*
 * Blocked Jacobi solver: one iteration step
 */
double relax_jacobi (double *u, double *utmp, unsigned sizex, unsigned sizey)
{
    double diff, sum=0.0;
    #pragma omp parallel private(diff) reduction(+:sum)
    {
    int howmany=omp_get_num_threads();
    int blockid=omp_get_thread_num();
      int i_start = lowerb(blockid, howmany, sizex);
      int i_end = upperb(blockid, howmany, sizex);
							dummyMethod3();
    for (int i=max(1, i_start); i<= min(sizex-2, i_end); i++) {
        for (int j=1; j<= sizey-2; j++) {
	     utmp[i*sizey+j]= 0.25 * ( u[ i*sizey     + (j-1) ]+  // left
	                               u[ i*sizey     + (j+1) ]+  // right
				       u[ (i-1)*sizey + j     ]+  // top
				       u[ (i+1)*sizey + j     ]); // bottom
	     diff = utmp[i*sizey+j] - u[i*sizey + j];
	     sum += diff * diff; 
	 }
      }
							dummyMethod4();
      
    }

    return sum;
}

/*
 * Blocked Gauss-Seidel solver: one iteration step
 */
double relax_gauss (double *u, unsigned sizex, unsigned sizey)
{
    double unew, diff, sum=0.0;
    int howmany=omp_get_max_threads();
							dummyMethod1();
    #pragma omp parallel for ordered(2) private(unew,diff) reduction(+:sum)
    for (int row=0;row<howmany;row++) {
        for(int column=0;column<howmany;column++) {
            int row_start=lowerb(row,howmany,sizex);
            int column_start=lowerb(column,howmany,sizey);
            int row_end=upperb(row,howmany,sizex);
            int column_end=upperb(column,howmany,sizey);
            #pragma omp ordered depend(sink:row-1,column) 
            for(int i=max(1,row_start);i<=min(sizex-2,row_end);i++) {
                for(int j=max(1,column_start);j<=min(sizey-2,column_end);j++) {
                    unew=0.25*(u[i*sizey+(j-1)]+
                           u[i*sizey+(j+1)]+
                           u[ (i-1)*sizey+j]+
                           u[ (i+1)*sizey+j]);
                    diff=unew-u[i*sizey+j];
                    sum+=diff*diff;
                    u[i*sizey+j]=unew;
                }
            }
            #pragma omp ordered depend(source)
      }
    }
							dummyMethod2();

    return sum;
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