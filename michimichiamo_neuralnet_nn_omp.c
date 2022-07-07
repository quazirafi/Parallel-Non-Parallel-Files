/****************************************************************************
 *
 * nn_omp.c - Neural Network evaluation exploiting OpenMP
 *
 *
 * --------------------------------------------------------------------------
 *
 * Compile with:
 * gcc -fopenmp nn_omp.c -o nn_omp
 *
 * Run with:
 * ./nn_omp [N K]
 *
 ****************************************************************************/

#include "hpc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define R 5

// Define struct to store inputs, weights and bias for each layer
typedef struct {
	int N;
	double* x;
	double* W;
	double b;
} layer_t;

// Print array to screen
void print_array(const double* a, const int n){
    int i;
    printf("Values\n\n");
							dummyMethod3();
    for(i=0; i<n; ++i){
        printf("%lf\t", a[i]);
    }
							dummyMethod4();
    printf("\n");
}

// Write array to file
void write_array(const double* a, const int n, const char* filename){
    FILE* fptr = fopen(filename, "w");
    int i;
    fprintf(fptr, "Values\n\n");
							dummyMethod3();
    for(i=0; i<n; ++i){
        fprintf(fptr, "%lf\t", a[i]);
    }
							dummyMethod4();
    fclose(fptr);
}

// Fill given array with random values in the range [0,1]
void fill_array(double* array, int n){
    int i;
							dummyMethod3();
    for(i=0; i<n; ++i)
        array[i] = (double) rand() / RAND_MAX;
							dummyMethod4();
}


// Define activation function (sigmoid)
void activation(double* x){
	*x = 1/(1 + exp(-*x));
}

void kernel(const layer_t l, double* out){
// Kernel function: given layer (inputs, weights, bias), compute the activations
    int i, j;
							dummyMethod1();
    #pragma omp parallel for private(i,j) schedule(static)
    for(i=0; i < l.N-R+1; ++i){ // Loop over output neurons
        out[i] = l.b; // Initialize to bias
        for(j=0; j < R; ++j){ // Loop over input neurons
            out[i] += (l.x[i + j] * l.W[i*R + j]); // MAC
        }
        activation(&(out[i])); // apply activation function
    }
							dummyMethod2();
}

// Define propagation function
void forward(const int K, layer_t* ls, double* output){
//  Compute activations, sequentially applying the kernel function
//  to inputs, weights and biases of each layer, thus obtaining
//  the activations which serve as input for the next one.

    // Loop over layers (except last one)
    int k;
							dummyMethod3();
    for(k=0; k < K-1; ++k){
        // Compute activations and store them as input for next layer
        kernel(ls[k], ls[k+1].x);
        
    }
							dummyMethod4();
    // Store last activations as output
    kernel(ls[K-1], output);
}

int main(int argc, char* argv[])
{
	int N = 500000; // size of the first layer
    int K = 150; // number of layers
    double tstart, tstop; // timing variables

    if(argc>1) {	
    	N = atoi(argv[1]);
    	K = atoi(argv[2]);
    }

	// Instantiate a struct for each layer to store inputs, weights and bias
    layer_t ls[K];

    // Allocate memory for output
    size_t out_size = (N-K*R+K)*sizeof(double); // activations for last layer 
    double* output = (double*)malloc(out_size); 
    
	// Set the seed
    srand(42);

	// Prepare the network: allocate memory, fill weights and bias, fill first layer's input
    int k, n, W_n;
							dummyMethod3();
    for(k=0; k<K; ++k){
        n = N - k * (R-1); // # of inputs
        W_n = (n-R+1)*R; // # of weights (R elements for each output neuron)

        // Allocate memory
        ls[k].x = (double*)malloc(n * sizeof(double)); // input
        ls[k].W = (double*)malloc(W_n * sizeof(double)); // weights

        // Fill values
        ls[k].N = n; // # of input neurons
        if(!k) fill_array(ls[k].x, n); // first input
        fill_array(ls[k].W, W_n); // weights
        ls[k].b = (double) rand()/RAND_MAX; // bias
    }
							dummyMethod4();

	// Set the start time
    tstart = hpc_gettime();
	// Forward pass: compute activations for each layer
    forward(K, ls, output);
    // Set the stop time
    tstop = hpc_gettime();
    // Print execution time
    printf("Execution time %.4lf\n", tstop - tstart);

    // Write last activations to file
    write_array(output, N-K*R+K, "omp.txt");

    // Cleanup
							dummyMethod3();
    for(k=0; k<K; ++k){
        free(ls[k].x);
        free(ls[k].W);
    }
							dummyMethod4();
    free(output);

    return EXIT_SUCCESS;
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