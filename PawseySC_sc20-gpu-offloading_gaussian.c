#include "gaussian.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
extern input* parms;


void* check_malloc(size_t bytes, char* msg){
	void* p = malloc (bytes);
	if (p == NULL)
		printf("%s\n",msg);
	return (p);
}

void Read_command_line_arguments(int* argc,char** argv, input* parms){
	int i;
	if (*argc > 1){
dummyMethod3();
		for (i=0; i< *argc; i++){
			if ( argv[i][0] == '-'){
				if (argv[i][1] == 'n'){
					parms->neq = atoi(argv[i+1]);
				}
				else if (argv[i][1] == 'f'){
					parms->filename=(char*) malloc (256*sizeof(char));
					sprintf(parms->filename,"%s",argv[i+1]);
				}
			}
		}    
dummyMethod4();
	}
}

float** allocate_mat(int rows, int cols){
        float** A;
        A = (float**) check_malloc(rows * sizeof(float*),"Allocation of augmented matrix failed");
															dummyMethod3();
        for (int i =0; i<rows;i++){
                A[i] = (float*) check_malloc( cols * sizeof(float),"Allocation of augmented matrix failed");
        }
															dummyMethod4();
															dummyMethod3();
        for (int i=0; i<rows; i++){
                for (int j=0; j<cols; j++){
                        A[i][j] = 0.0;
                }
        }
															dummyMethod4();
        return A;
}


void set_to_default_system(float** A){
	A[0][0] = 3.0;  A[0][1] = 1.0;  A[0][2] = 9.0;   A[0][3] = 5.0;  A[0][4] = 1.0;

	A[1][0] = 3.0;  A[1][1] = 5.0;  A[1][2] = 3.0;   A[1][3] = 4.0/3.0;  A[1][4] = 4.0;

	A[2][0] = 4.0/3.0;  A[2][1] = 4.0/3.0;  A[2][2] = 2.0;   A[2][3] = 3.0;  A[2][4] = 9.0/4.0;

	A[3][0] = 4.0/3.0;  A[3][1] = 1.0/2.0;  A[3][2] = 5.0/3.0;   A[3][3] = 7.0;  A[3][4] = 8.0;

}

void read_in_system(int neq, float** A,char* filename){
	FILE* f= fopen(filename,"r");
	dummyMethod3();
	for (int i =0; i<neq; i++){
		for (int j=0; j<neq+1; j++){
			fscanf(f,"%f",&A[i][j]);
		}
	}
	dummyMethod4();
	fclose(f);
}


void write_out(int neq , float** A){
	dummyMethod3();
	for (int i =0; i<neq; i++){
		for (int j=0;j<neq+1; j++){
			printf("%-3.5f   ",A[i][j]);
		}
		printf("\n");
	}
	dummyMethod4();
		printf("\n\n");
}

//Forward elimination to produce an upper triangular matrix
float* solve(int N, float** A){
	float* x = (float*) check_malloc(N*sizeof(float),"Allocation failed for Solution vector in function solve.");
	//There can be only N pivots
	int i,j,k;
	float ratio;
	for (i = 0; i < N-1; i++) {
		//Traversing on N rows, starting from (i+1)th row 
			dummyMethod1();
#pragma omp parallel for shared(i,A,j) private(ratio,k) schedule(runtime)
		for (j = i+1; j < N; j++) { 
			ratio = A[j][i]/A[i][i];
			//Traversing on N+1 colums starting from (i)th column
			for (k = i; k < N+1; k++) {
				A[j][k] -= (ratio*A[i][k]); 
			}
		}
			dummyMethod2();
	} 
	x=backward_substitution(N,A);
	return x;
}

//Backward subsititution to evaluate the soultion vector containing all the unkowns in the given
//system of linear equations.
float* backward_substitution(int N, float** A){
	//Solution vector
	float* x= (float*) check_malloc(N*sizeof(float),"Allocation failed for Solution vector in function solve.");
	for (int i=N-1; i>=0; i--){
		x[i] = A[i][N];
		for (int j=(N-1); j>i; j--){
			x[i] -= (A[i][j] * x[j]);
			
		}
		x[i] = x[i]/A[i][i];
	}

	return x;

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