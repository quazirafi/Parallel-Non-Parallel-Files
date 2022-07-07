#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void Normalization(float ** Ak,float Akj, int n);
void Simplification(float ** vect1, float ** vect2, float valeur, int n);
void DivVector(float *** matrix ,float coef, int n,float * vect);

void FillRandomMatrix(float *** matrix, int n);
void FillTestMatrix(float *** matrix, int n);
void FillVector(float ** vect, int n);
void FillRandomVector(float ** vect, int n);
void FreeTab(float ** matrix,float * vect,int n);

void DisplayMatrix(float ** matrix, int n);
void DisplayVector(float * vector, int n);



int main(void) {

    int n = 0;
    float max = 0;
    float ** A;
    float * temp;
    float temp2;
    float * b;
    clock_t t1, t2;
    int numThreads;
    int display;

    printf("Number of threads ? \n");
    scanf(" %d",&numThreads);
    omp_set_num_threads(numThreads);
    omp_set_nested(1);
    omp_set_dynamic(1);

		//Step 0: Matrix initialization
    printf("Size of matrix A ? \n");
    scanf(" %d",&n);

	A = (float**)calloc(n,sizeof(float*));
    b = (float*)calloc(n,sizeof(float));
    FillTestMatrix(&A,n);
    FillRandomVector(&b,n);

    printf("Display system (1/0) ? \n");
    scanf(" %d", &display);

    if(display) {
        printf("Initial system:\n");
    	DisplayMatrix(A, n);
        DisplayVector(b, n);
    }

    printf("Start solving\n");
    t1 = clock();


		//Step 1: Solving system
    int r = -1, k = 0;
    for (int j=0; j<n; j++) {

		max = A[r+1][j];
        k=r+1;

		//Looking for max
        for (int i=r+1; i<n; i++) {
            if (A[i][j] > max) {
                max = A[i][j];
                k = i;
            }
        }

		//If pivot not null
        if (A[k][j] != 0) {
            r++;

            //Normalization of the line to get reduced row echelon form
            b[k] = b[k] / A[k][j];
            Normalization( &(A[k]), A[k][j], n );

            if(k!=r) {
                temp = A[k];
                A[k] = A[r];
                A[r] = temp;
                temp2 = b[k];
                b[k] = b[r];
                b[r] = temp2;
            }


            //Simplification of other lines
																							dummyMethod1();
            #pragma omp parallel for schedule(static, 500)
            for (int i = 0 ; i < n; i++) {
                if(i != r) {
                    b[i] = b[i] - b[r] * A[i][j];
                    Simplification(&(A[i]), &(A[r]), A[i][j], n);
                }
            }
																							dummyMethod2();
        }
    }

    t2 = clock();
    float diff = ((float)(t2 - t1) / 1000000.0F ) * 1000;

    if(display) {
        printf("Solution:\n");
        DisplayMatrix(A, n);
        DisplayVector(b, n);
    }

    printf("Execution time: %f\n",diff);

    //FreeTab(A, b, n);

	return 0;
}



void Simplification(float ** Ai, float ** Ar, float Aij, int n) {
    for (int i = 0; i<n; i++) {
        (*Ai)[i] = (*Ai)[i] - (*Ar)[i] * Aij;
    }
}



void Normalization(float ** Ak, float Akj, int n) {
							dummyMethod1();
    #pragma omp parallel for schedule(static, 500)
    for (int i = 0; i < n; i++) {
        (*Ak)[i] = (*Ak)[i] / Akj;
    }
							dummyMethod2();
}



void FillRandomMatrix(float *** matrix, int n) {
    float val;
    srand (time (NULL));

    for (int i=0 ; i < n ; i++) {
        (*matrix)[i] = (float*)calloc(n,sizeof(float));
    }

    for (int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            val = rand()%100;
            (*matrix)[i][j] = val;
        }
    }
}



void FillTestMatrix(float *** matrix, int n) {
    float val;
    srand (time (NULL));

    for (int i=0 ; i < n ; i++) {
        (*matrix)[i] = (float*)calloc(n,sizeof(float));
    }

    for (int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            if(i == j || i-1 == j || i+1 == j) {
                val = rand()%100;
            }
            else {
                val = 0;
            }
            (*matrix)[i][j] = val;

        }
    }
}



void FillVector(float ** vect, int n) {
    float val;
    for (int i = 0 ; i < n ; i++) {
        printf("Value of b [%d] ? : \n",i);
        scanf(" %f",&val);
        (*vect)[i] = val;
    }
}



void FillRandomVector(float ** vect, int n) {
    float val;

    (*vect) = (float*)calloc(n,sizeof(float));

    for(int i = 0 ; i < n ; i++) {
        val = rand()%100;
        (*vect)[i] = val;
    }
}



void DisplayMatrix(float ** matrix, int n) {
    printf("Matrix A :\n");
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            printf(" %f \t",matrix[i][j]);
        }
        printf("\n");
    }
}



void DisplayVector(float * vector, int n) {
    printf("Vector b :\n");
    for (int i = 0 ; i < n ; i++) {
        printf(" %f \t",vector[i]);
        printf("\n");
    }
    printf("\n");
}



void FreeTab(float ** matrix,float * vect,int n) {
    for (int i = 0 ; i < n ; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vect);
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