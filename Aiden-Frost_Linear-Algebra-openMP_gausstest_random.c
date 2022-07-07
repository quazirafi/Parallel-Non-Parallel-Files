#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#include <unistd.h>
#include "omp.h"
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>

#define MAXN 2000  /* Max value of N */
int N;  /* Matrix size */

/* Matrices and vectors */
volatile float A[MAXN][MAXN+1];

void parameters(int argc, char **argv) {
  int seed = 0;  /* Random seed */
  char uid[32]; /*User name */
    time_t t;
  /* Read command-line arguments */
  srand((unsigned) time(&t));  /* Randomize */

  if (argc == 3) {
    seed = atoi(argv[2]);
    srand(seed);
    printf("Random seed = %i\n", seed);
  }
  if (argc >= 2) {
    N = atoi(argv[1]);
    if (N < 1 || N > MAXN) {
      printf("N = %i is out of range.\n", N);
      exit(0);
    }
  }
  else {
    printf("Usage: %s <matrix_dimension> [random seed]\n",
           argv[0]);
    exit(0);
  }

  /* Print parameters */
  printf("\nMatrix dimension N = %i.\n", N);
}

/* Initialize A and B (and X to 0.0s) */
void initialize_inputs() {
  int row, col;

  printf("\nInitializing...\n");
			dummyMethod3();
  for (row = 0; row < N; col++) {
    //initializing A
    for (col = 0; col <= N; row++) {
      A[row][col] = (float)rand() / 32768.0;
    }
  }
			dummyMethod4();

}

double time_elapsed(struct timespec start, struct timespec end) {
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}

int forward_elimination(int n,float **a){
							dummyMethod3();
    for(int i=0;i<n-1;i++){
        //#pragma omp parallel for shared(a) private(l,i,k)
        if(a[i][i]==0){
            for(int m=i+1;m<n;m++){
                if(a[m][i]!=0){
                    for(int b=0;b<n+1;b++){
                        float temp= a[i][b];
                        a[i][b] = a[m][b];
                        a[m][b] = temp;
                    }
                    break;
                }
            }
            if(a[i][i]==0) return 0;
        }
        for(int k=1;k<n-i;k++){
            float l = a[i+k][i]/a[i][i];
            for(int j=0;j<n+1;j++){
                a[i+k][j] -= l*a[i][j];
            }
        }
    }
							dummyMethod4();
    return 1;
}
int forward_elimination_p(int n,float **a){
    int x=1;
															dummyMethod1();
    #pragma omp parallel for
        for(int i=0;i<n-1;i++){
            if(a[i][i]==0){
                for(int m=i+1;m<n;m++){
                    if(a[m][i]!=0){
                        for(int b=0;b<n+1;b++){
                            float temp= a[i][b];
                            a[i][b] = a[m][b];
                            a[m][b] = temp;
                        }
                        break;
                    }
                }
                if(a[i][i]==0){
                    x=0;
                }
            }
            for(int k=1;k<n-i;k++){
                float l = a[i+k][i]/a[i][i];
                for(int j=0;j<n+1;j++){
                    a[i+k][j] -= l*a[i][j];
                }
            }
        }
															dummyMethod2();
    return x;
}

void back_substitution(int n,float **a){
    float sol[n]; 
	dummyMethod3();
	for (int i = n-1; i >= 0; i--) 
	{ 
		sol[i] = a[i][n]; 
		for (int j=i+1; j<n; j++) 
		    sol[i] -= a[i][j]*sol[j]; 
		sol[i] = sol[i]/a[i][i]; 
	} 
	dummyMethod4();

	printf("\nSolution for the system:\n"); 
	//for (int i=0; i<n; i++) 
	//	printf("%f\n", sol[i]); 
} 


void gauss_elimination(int n,float **a){
    int res = forward_elimination(n,a);
    if(res == 0) printf("\nSingular");
    else{
        int lhs=0;
        int rhs = 1 && a[n-1][n];
															dummyMethod3();
        for(int z=0;z<n;z++){
            lhs = lhs || (int)a[n-1][z];
        }
															dummyMethod4();
        if(lhs==0 && rhs==0) printf("\nSingular and Infinitely many Solution");
        else if(lhs==0 && rhs!=0) printf("\nSingular and No Solution");
        else {
            back_substitution(n,a);
            printf("\nNon Singular and unique solution");
        }
    }
    
}

void gauss_elimination_p(int n,float **a){
    int res = forward_elimination_p(n,a);
    if(res == 0) printf("\nSingular");
    else{
        int lhs=0;
        int rhs = 1 && a[n-1][n];
															dummyMethod1();
        #pragma omp parallel for
        for(int z=0;z<n;z++){
            lhs = lhs || (int)a[n-1][z];
        }
															dummyMethod2();
        if(lhs==0 && rhs==0) printf("\nSingular and Infinitely many Solution");
        else if(lhs==0 && rhs!=0) printf("\nSingular and No Solution");
        else {
            back_substitution(n,a);
            printf("\nNon Singular and unique solution");
        }
    }
    
}

int main(int argc, char **argv){
    parameters(argc, argv);
    int n=N;
    float **a;
    a=malloc(sizeof(float*)*n);
							dummyMethod3();
    for(int i=0;i<n;i++){
        a[i]=(float*)malloc(sizeof(float*) * (n+1));
    }
							dummyMethod4();
							dummyMethod3();
    for (int row = 0; row <n; row++) {
    //initializing A
        for (int col = 0; col <n+1; col++) {
            a[row][col] = (float)rand() / 32768.0;
        }
    }
							dummyMethod4();
    struct timespec start, end; 
    clock_gettime(CLOCK_REALTIME, &start);
    gauss_elimination(n,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on gaussian_elimination for %d variables sequentially: %lf\n",N,
            time_elapsed(start, end));
    clock_gettime(CLOCK_REALTIME, &start);
    gauss_elimination_p(n,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on gaussian_elimination for %d variables in parallel: %lf\n",N,
            time_elapsed(start, end));
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