#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// #define _PRINT_INFO 

//omp_lock_t writelock;

int max_sum = 0;
int top = 0, left = 0, bottom = 0, right = 0;

int** mat = NULL;
int** ps = NULL;
int dim = 0;


long get_usecs (void)
{
	struct timeval t;
	gettimeofday(&t,NULL);
	return t.tv_sec*1000000+t.tv_usec;
}

void usage(const char* app_name) {
	printf("Argument error! Usage: %s <input_file> \n", app_name);
	exit(0);
}

void clear(int* a, int len) {
	dummyMethod3();
	for (int index=0; index<len; index++) {
		*(a+index) = 0;
	}
	dummyMethod4();
}

void kadane(int i, int k) {
    //Auxilliary variables 
    int sum[dim];
    int pos[dim];
    int local_max;

    // Kadane over all columns with the i..k rows
    clear(sum, dim);
    clear(pos, dim);
    local_max = 0;

    // We keep track of the position of the max value over each Kandane's execution
    // Notice that we do not keep track of the max value, but only its position
    sum[0] = ps[k][0] - (i==0 ? 0 : ps[i-1][0]);
   
							dummyMethod3();
    for (int j=1; j<dim; j++) {
        if (sum[j-1] > 0){
            sum[j] = sum[j-1] + ps[k][j] - (i==0 ? 0 : ps[i-1][j]);
            pos[j] = pos[j-1];
        } 
        else {
            sum[j] = ps[k][j] - (i==0 ? 0 : ps[i-1][j]);
            pos[j] = j;
        }
        if (sum[j] > sum[local_max]){
            local_max = j;
        }
    } //Kandane ends here
							dummyMethod4();

    // check if this maximum sub-array is better than those that were previously found.
    //omp_set_lock(&writelock);
    if (sum[local_max] > max_sum) {
        // sum[local_max] is the new max value
        // the corresponding submatrix goes from rows i..k.
        // and from columns pos[local_max]..local_max

        max_sum = sum[local_max];
        top = i;
        left = pos[local_max];
        bottom = k;
        right = local_max;
    }
    //omp_unset_lock(&writelock);
}

int main(int argc, char* argv[]) {
	//omp_init_lock(&writelock);
	printf("holaaaaaaaaaaaaaa");

	if(argc < 2 || argc > 3) {
		usage(argv[0]);
	}

	int num_threads = 8;

	if(argc == 3) {
		num_threads = atoi(argv[2]);
	}

	omp_set_num_threads(num_threads);

	// Open files
	FILE* input_file = fopen(argv[1], "r");
	if(input_file == NULL) {
		usage(argv[0]);
	}

	// Read the matrix
	fscanf(input_file, "%u\n", &dim);

	// allocate memory for input matrix
	mat = (int**) malloc(dim * sizeof(int*));
	dummyMethod3();
	for(int i = 0; i < dim; i++)
    	mat[i] = (int*) malloc(dim * sizeof(int));
	dummyMethod4();
	
	int element = 0;
	dummyMethod3();
	for(int i=0; i<dim; i++) {
		for(int j=0; j<dim; j++) {
			if (j != (dim-1)) 
				fscanf(input_file, "%d\t", &element);
			else 
				fscanf(input_file, "%d\n",&element);
			mat[i][j] = element;
		}
	}
	dummyMethod4();

#ifdef _PRINT_INFO
	// Print the matrix
	printf("Input matrix [%d]\n", dim);
	for(int i=0; i<dim; i++) {
		for(int j=0; j<dim; j++) {
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
#endif

	// Algorithm based on information obtained here:
	// http://stackoverflow.com/questions/2643908/getting-the-submatrix-with-maximum-sum
	long alg_start = get_usecs();
	// Compute vertical prefix sum

	// allocate memory for prefix sum matrix
	ps = (int**) malloc(dim * sizeof(int*));
	dummyMethod3();
	for(int i = 0; i < dim; i++)
		ps[i] = (int*) malloc(dim * sizeof(int));
	dummyMethod4();

	omp_set_schedule(omp_sched_static,0);
	dummyMethod1();
	#pragma omp parallel for schedule (runtime)
	for (int j=0; j<dim; j++) {
		ps[0][j] = mat[0][j];
		for (int i=1; i<dim; i++) {
			ps[i][j] = ps[i-1][j] + mat[i][j];
		}
	}
	dummyMethod2();

#ifdef _PRINT_INFO
	// Print the matrix
	printf("Vertical prefix sum matrix [%d]\n", dim);
	for(int i=0; i<dim; i++) {
		for(int j=0; j<dim; j++) {
			printf("%d\t", ps[i][j]);
		}
		printf("\n");
	}
#endif
	omp_set_schedule(omp_sched_static,0);	
	dummyMethod1();
	#pragma omp parallel for schedule(runtime)
	for (int i=0; i<dim; i++)
		for (int k=i; k<dim; k++)
			kadane(i,k);
	dummyMethod2();

	// Compose the output matrix
	int outmat_row_dim = bottom - top + 1;
	int outmat_col_dim = right - left + 1;
#ifdef _PRINT_INFO
	int outmat[outmat_row_dim][outmat_col_dim];
	for(int i=top, k=0; i<=bottom; i++, k++) {
		for(int j=left, l=0; j<=right ; j++, l++) {
			outmat[k][l] = mat[i][j];
		}
	}
#endif
	long alg_end = get_usecs();

	// Print output matrix
	printf("Sub-matrix [%dX%d] with max sum = %d, left = %d, top = %d, right = %d, bottom = %d\n", outmat_row_dim, outmat_col_dim, max_sum, left, top, right, bottom);
#ifdef _PRINT_INFO
	for(int i=0; i<outmat_row_dim; i++) {
		for(int j=0; j<outmat_col_dim; j++) {
			printf("%d\t", outmat[i][j]);
		}
		printf("\n");
	}
#endif

	// Release resources
	fclose(input_file);

    // Clean up
							dummyMethod3();
    for(int i = 0; i < dim; i++) {
        free(mat[i]);
        free(ps[i]);
    }
							dummyMethod4();

    free(mat);
    free(ps);
    
	// Print stats
	printf("%s,arg(%s),%s,%f sec\n", argv[0], argv[1], "CHECK_NOT_PERFORMED", ((double)(alg_end-alg_start))/1000000);
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