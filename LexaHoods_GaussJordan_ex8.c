#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void ProdMatVect(int nc, int nl, double** A, double* x, double* y);
void ProdMatMat(int nc, int nl, double** A, double** B, double*** C);
void SommVectVect(int n, double* a, double* b, double** c);


int main(int argc, char **argv){   
 
    FILE* fichier = fopen("perf8.csv", "w");  
    srand(time(NULL));
    
    fprintf(fichier,"Temps;nl;nc");
    
    int nl=2,nc=2;
    int t,tmax=10;
    int i,j;
    
    double debut,fin;
    
    if(argc==3){
        nl = atoi(argv[1]);
        nc = atoi(argv[2]);
        tmax=1;
    }
							dummyMethod3();
    for(t=0;t<tmax;t++){
    
        double **A=(double **) malloc(sizeof(double*)*nl);
        
        double *x=(double *) malloc(sizeof(double)*nl);
        double *temp=(double *) malloc(sizeof(double)*nl);
        double *temp2=(double *) malloc(sizeof(double)*nl);
        
        
        for(i=0;i<nl;i++){
            A[i]=(double *) malloc(sizeof(double)*nc);
            
            for(j=0;j<nc;j++){
                A[i][j]=rand()%10;
            }
            
            x[i]=rand()%10;
            temp[i]=0;
            temp2[i]=0;
        }
        
        if(tmax==1){
            for(i=0;i<nl;i++){
                for(j=0;j<nc;j++){
                     printf("A%d%d %f\n",i,j,A[i][j]);
                }
            }
            for(i=0;i<nl;i++){
                printf("x%d %f\n",i,x[i]);
            }
        }
        
        
        debut = omp_get_wtime();
        ProdMatVect(nc,nl,A,x,temp);
        SommVectVect(nl,temp,x,&temp2);
        ProdMatVect(nc,nl,A,temp2,temp);
        SommVectVect(nl,temp,x,&temp2);
        fin = omp_get_wtime();
        
        if(tmax==1){
            for(i=0;i<nl;i++){
                printf("resulat%d %f\n",i,temp2[i]);
            }
        }
        
        printf("\ntemps: %3.6f s\n",fin-debut);
        fprintf(fichier,"\n%f;%d;%d;",fin-debut,nl,nc);
        
        for(i=0;i<nl;i++){
            free(A[i]);
        }
        free(A);
        free(x);
        free(temp);
        free(temp2);


        nc*=2;
        nl*=2;
    }
							dummyMethod4();
    
    fclose(fichier);
    
    return 0;
}

void SommVectVect(int n, double* a, double* b, double** c){
    int i;
    
							dummyMethod1();
    #pragma omp parallel for
    for(i=0;i<n;i++){
        (*c)[i]=a[i]+b[i];
    }
							dummyMethod2();
}

void ProdMatVect(int nc, int nl, double** A, double* x, double* y){
    
    int i,j;
    double somme;
    
							dummyMethod1();
    #pragma omp parallel for
    for(i=0;i<nl;i++){
        #pragma omp parallel for reduction(+:somme)
        for(j=0;j<nc;j++){
            somme+=A[i][j]*x[j];
        }
        y[i]=somme;
    }
							dummyMethod2();
}

void ProdMatMat(int nc, int nl, double** A, double** B, double*** C){
    
    int i,j,k;
    double somme;
    
							dummyMethod1();
    #pragma omp parallel for
    for(i=0;i<nl;i++){
        #pragma omp parallel for
        for(j=0;j<nc;j++){
            somme=0;
            #pragma omp parallel for reduction(+:somme)
            for(k=0;k<nl;k++){
                somme+=A[i][k]*B[k][j];
            }
            (*C)[i][j]=somme;
        }
    }
							dummyMethod2();
}

/*

Si on ne précise pas la taille en faisant
gcc -fopenmp -Werror ex8.c -o ex8.out
./ex8.out 
ou bien make 8
Alors on vas calculer les temps d'execution pour des matrices de taille
croissante et stocker les resultats dans perf8.csv

Si on précise une taille, on lance le calcul et on affiche les resultats
a des fins de verification

gcc -fopenmp -Werror ex8.c -o ex8.out
./ex8.out 2 2
ou bien
make 8 x=2 y=2 

A00 6.000000
A01 0.000000
A10 6.000000
A11 3.000000
x0 5.000000
x1 0.000000
resulat0 215.000000
resulat1 300.000000

temps: 0.002236 s
*/
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