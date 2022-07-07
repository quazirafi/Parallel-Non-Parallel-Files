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
volatile float A[MAXN][MAXN];

double time_elapsed(struct timespec start, struct timespec end) {
	double t;
	t = (end.tv_sec - start.tv_sec); 
	t += (end.tv_nsec - start.tv_nsec) * 0.000000001; 
	return t;
}

int forward_elimination(int n,float **a){
    int x=1;
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
            if(a[i][i]==0) x=0;
        }
        for(int k=1;k<n-i;k++){
            float l = a[i+k][i]/a[i][i];
            for(int j=0;j<n+1;j++){
                a[i+k][j] -= l*a[i][j];
            }
        }
    }
							dummyMethod4();
    /*
    printf("\nFinal Matrix\n");
   for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } */
    return x;
    
    
}
int forward_elimination_p(int n,float **a){
    int x;
															dummyMethod1();
    #pragma omp parallel for shared(x)
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
                if(a[i][i]==0) x=0;;
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
	dummyMethod3();
	for (int i=0; i<n; i++) 
		printf("%f\n", sol[i]); 
	dummyMethod4();
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


int main(){
    int n;
    printf("Enter the number of unknown variables:");
    scanf("%d",&n);
    float **a;
    a=malloc(sizeof(float*)*n);
							dummyMethod3();
    for(int i=0;i<n;i++){
        a[i]=(float*)malloc(sizeof(float*) * (n+1));
    }
							dummyMethod4();
    printf("Enter the elements:\n");
							dummyMethod3();
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            scanf("%f",&a[i][j]);
        }
    }
							dummyMethod4();
   /*for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } 
    */
    struct timespec start, end; 
    clock_gettime(CLOCK_REALTIME, &start);
    gauss_elimination(n,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on gaussian_elimination for %d variables sequentially: %lf\n",n,
            time_elapsed(start, end));
    clock_gettime(CLOCK_REALTIME, &start);
    gauss_elimination_p(n,a);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("\nTime spent on gaussian_elimination for %d variables in parallel: %lf\n",n,
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