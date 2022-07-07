// ---------------------------------------------------------------------------------------
/*
=========================================================================
Author: Rodrigo de Barros Vimieiro
Date: October, 2019
rodrigo.vimieiro@gmail.com
=========================================================================

Compile it -> gcc jacobipar.c -o jacobipar.bin -fopenmp

*/
// ---------------------------------------------------------------------------------------

#include "jacobipar.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
*** MAIN ***
*/
int main(int argc,char **argv){

    unsigned int rank, nTreads;
    unsigned int nIter;

    // Test if the arguments are correct
    if(argc==3){

        char *p;

        errno = 0;

        rank = (unsigned int) strtol(argv[1], &p, 10);
        nTreads = (unsigned int) strtol(argv[2], &p, 10);

        // https://stackoverflow.com/a/9748431/8682939
        // Check for errors: e.g., the string does not represent an integer
        // or the integer is larger than int
        if (errno != 0 || *p != '\0' || rank > INT_MAX) {
            // Put here the handling of the error, like exiting the program with
            // an error message
            printf("*** Error: Please, give the program its correct input: <rank, nThreads> ***\n");
            return 0;
        }

    }
    else{
        printf("*** Error: Please, give the program its correct input: <rank, nThreads> ***\n");
        return 0;
    }



    const double epsilon = PRECISION;

    double b_hat[rank];

    // Memory allocation for matrix A, x and b
	double* const A = (double*)malloc(rank*rank * sizeof(double));
    double* const x = (double*)malloc(rank * sizeof(double));
    double* const b = (double*)malloc(rank * sizeof(double));

    if((A == NULL)&&(x == NULL)&&(b == NULL)){
        printf("*** malloc Error ***\n");
        return 0;
    }

    double wtime = omp_get_wtime();

    // Initialization, should only be called once.
	srand(time(NULL));


    // Generate random numebers 0-10 to place on matrix A
    generateRandNumbers(A,b,rank,nTreads);
            
/*     A[0] = 4;A[1] = 2;A[2] = 1;
    A[3] = 1;A[4] = 3;A[5] = 1;
    A[6] = 2;A[7] = 3;A[8] = 6;

    b[0] = 7;b[1] = -8;b[2] = 6; */
    

    // Show preliminary informations
    if(showAuxInf){

        printf("\n\n***************\n\n");
        
        printf("\nMatrix rank: %d \n",rank);

        printf("\nNumber of threads: %d \n",nTreads);

        printf("\nA = [\n");
															dummyMethod3();
        for(int j = 0; j < rank; j++){
            for(int i = 0; i < rank; i++)
                printf("%.2f ",A[i*rank+j]); 
            printf("\n");
        }
															dummyMethod4();
        printf("]\n");

        printf("\nb = [");
															dummyMethod3();
        for(int i = 0; i < rank; i++)
                    printf("%.2f ",b[i]); 
															dummyMethod4();
        printf("]\n");

    }

    // Test if matrix A will converge
    if(convergenceTest(A,rank,nTreads) == false){
        printf("\n******* The matrix A might not converge. *******\n\n");
        return 0;
    }

    // Solve Ax=b through Jacobi method
    solveJacobi(A,x,b,rank,epsilon,&nIter,nTreads);


    // Solve b with calculated x
							dummyMethod1();
    #pragma omp parallel for schedule(static) num_threads(nTreads)
    for(int i = 0; i < rank; i++){
        b_hat[i] = 0;
        for(int j = 0; j < rank; j++)
                b_hat[i] += A[i*rank+j] * x[j]; 
    }
							dummyMethod2();

    double finalTime = omp_get_wtime ( ) - wtime;

    if(showAuxInf){
        // print informations
        printf("\nx = [");
															dummyMethod3();
        for(int i = 0; i < rank; i++)
                    printf("%.2f ",x[i]); 
															dummyMethod4();
        printf("]\n");

        printf("\nb = [");
															dummyMethod3();
        for(int i = 0; i < rank; i++)
                    printf("%.2f ",b[i]); 
															dummyMethod4();
        printf("]\n");

        printf("\nb# = [");
															dummyMethod3();
        for(int i = 0; i < rank; i++)
                    printf("%.2f ",b_hat[i]); 
															dummyMethod4();
        printf("]\n");

        printf("\nTempo: %f \n",finalTime); 

        printf("\n\n***************\n\n");
    }

    write2file(finalTime,nIter,nTreads);

    // Free all allocated variables
    free(A);
    free(x);
    free(b);
}

// Test if matrix A will converge
int convergenceTest(double* const A,
                    unsigned int rank,
                    unsigned int nTreads){

    double alpha[rank];
    unsigned int convergence=0;    

    // Calculate alpha to test convergence
							dummyMethod1();
    #pragma omp parallel for schedule(static) num_threads(nTreads) reduction(+:convergence)
    for(int k = 0; k < rank; k++){

        alpha[k] = 0;

        for(int j = 0; j < rank; j++){
            if(j != k){
                alpha[k] += fabs(A[k*rank+j]) / fabs(A[k*rank+k]); 
            }
        }
        
        if(alpha[k] < 1)
            convergence++;

    }
							dummyMethod2();

    // Show alpha
    if(showAuxInf){
            printf("\n");
																							dummyMethod3();
            for(int k = 0; k < rank; k++)
                printf("Alpha%d:%.2f \n",k,alpha[k]);
																							dummyMethod4();
    }

    if (convergence == rank)
        return true;
    else
        return false;

}

// Solve Ax=b through Jacobi method
void solveJacobi(double* const A,
                 double* const x,
                 double* const b,
                 unsigned int rank,
                 const double epsilon,
                 unsigned int *nIter,
                 unsigned int nTreads){

    double x_k[rank];
    bool iterate = true;
    unsigned int iterN = 0;

    // Generate x0
							dummyMethod1();
    #pragma omp parallel for schedule(static) num_threads(nTreads)
    for(int i=0; i<rank; i++)
        x_k[i] = b[i] / A[i*rank+i];
							dummyMethod2();

    // Show x0
    if(showAuxInf){
        printf("\nx0 = [");
															dummyMethod3();
        for(int i = 0; i < rank; i++)
                    printf("%.2f ",x_k[i]); 
															dummyMethod4();
        printf("]\n");
    }

    while(iterate){

        iterN++;

        double maxXi = 0, maxDiffXi = 0;
        double absXi, absDiffXi;
        // Calculate x^{k+1}
															dummyMethod1();
        #pragma omp parallel for schedule(static) num_threads(nTreads) reduction(max:maxXi) reduction(max:maxDiffXi)
        for(int i=0; i<rank; i++){

            double sum = 0;
            for(int j=0; j<rank; j++){
                if(j != i)
                    sum += -A[i*rank+j] * x_k[j];
            }

            x[i] = (b[i] + sum) / A[i*rank+i];

            // Find the max x^{k+1} element
            absXi = fabs(x[i]);
            if(absXi > maxXi)
                maxXi = absXi;

            // Find the max x^{k+1}-x^{k} diference
            absDiffXi = fabs(x[i] - x_k[i]);
            if(absDiffXi > maxDiffXi)
                maxDiffXi = absDiffXi;  

        }
															dummyMethod2();

        // Show x^{k+1}
        if(showAuxInf){
            printf("x%d = [",iterN);
																							dummyMethod3();
            for(int i = 0; i < rank; i++)
                        printf("%.2f ",x[i]); 
																							dummyMethod4();
            printf("]\n");
        }

        // Calculate difference x^{k+1} - x^{k}
        if((maxDiffXi/maxXi) < epsilon)
            // Iteration stop!!
            iterate = false;
        else
            // Iteration continues...
            // Place x^{k+1} into x^{k}
																							dummyMethod1();
            #pragma omp parallel for schedule(static) num_threads(nTreads)
            for(int i=0; i<rank; i++)
                x_k[i] = x[i];  
																							dummyMethod2();

    }  

    nIter[0] =  iterN; 

    return;

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