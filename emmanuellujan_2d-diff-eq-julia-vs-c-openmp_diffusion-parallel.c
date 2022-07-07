#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
#include <math.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*******************************************************************************
*   In this simple code a 2D stationary diffusion equation is solved using
*   the finite difference method
*
*   Equation: d2u/dx2 + d2u/dy2 = 0
*
*   Initial condition: u(t=0,x,y) = 0
*
*   Boundary conditions:
*           u(t,x=0,y) = 0
*           u(t,x=1,y) = 0
*           u(t,x,y=0) = 1
*           u(t,x,y=1) = 0
*
*   How to run:
*            gcc -o diffusion-parallel -fopenmp diffusion-parallel.c -lm
*            export OMP_NUM_THREADS=8;
*            ./diffusion-parallel 100000 4000000
*
*           Note: first parameter is the number of convergence iterations
*                 second parameter is the number of mesh nodes
*
*******************************************************************************/

int main(int argc, char **argv) 
{

    // No. of convergence iterations
    int it_max = atoi(argv[1]);

    // No. of spatial domain nodes
    int n = (int) (sqrt(atof(argv[2])));

    // Define dependent variable (e.g. Temperature)
    double * u = malloc(n*n*sizeof(double));

    // Set initial conditions
							dummyMethod3();
    for(int i=0;i<n*n;i++)
        u[i] = 0.0;
							dummyMethod4();

    // Add boundary conditions
							dummyMethod3();
    for(int j=0;j<n;j++)
        u[j] = 1.0;
							dummyMethod4();

    // Solve eq. system, measuring time
    double start, end;

    start = omp_get_wtime(); 

    for(int k=0;k<it_max;k++)
															dummyMethod1();
        #pragma omp parallel for collapse(2) schedule(guided)
        for(int i=1;i<n-1;i++)
            for(int j=1;j<n-1;j++)
                u[i*n+j] = (u[(i+1)*n+j]+u[(i-1)*n+j]+u[i*n+j+1]+u[i*n+j-1])/4.0;
															dummyMethod2();

    end = omp_get_wtime(); 

    // Print result
    printf("%f\n",end - start);
    
    // Save CSV

    const char *fname = "heatmap-c.csv";
    if( access( fname, F_OK ) == -1 )
    {
        FILE *heatmap = fopen(fname, "w"); 
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n-1;j++)
                fprintf(heatmap, "%lf,", u[i*n+j]);
            fprintf(heatmap, "%lf\n", u[i*n+n-1]);
        }
        fclose(heatmap); 
    }

    free(u);
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