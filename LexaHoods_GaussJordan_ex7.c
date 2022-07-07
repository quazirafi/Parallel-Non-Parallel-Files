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

int main(int argc, char **argv){   
 
    FILE* fichier = fopen("perf7.csv", "w");  
    srand(time(NULL));
 
    int nl=2,nc=2;
    int i,j;
    int t,tmax=10;
    double debut,fin;
    if(argc==3){
        nl = atoi(argv[1]);
        nc = atoi(argv[2]);
        tmax=1;
    }
    fprintf(fichier,"TempsMatriceVecteur;TempsMatriceMatrice;nl;nc");
    
							dummyMethod3();
    for(t=0;t<tmax;t++){
        
        
        double *x=(double*) malloc(sizeof(double)*nl);
        double *y=(double*) malloc(sizeof(double)*nl);
        
        double **A=(double **) malloc(sizeof(double*)*nl);
        double **B=(double **) malloc(sizeof(double*)*nl);
        double **C=(double **) malloc(sizeof(double*)*nl);
        
        for(i=0;i<nl;i++){
            A[i]=(double *) malloc(sizeof(double)*nc);
            B[i]=(double *) malloc(sizeof(double)*nc);
            C[i]=(double *) malloc(sizeof(double)*nc);
            
            for(j=0;j<nc;j++){
                A[i][j]=rand()%10;
                B[i][j]=rand()%10;
                C[i][j]=0;
            }
            x[i]=rand()%10;
            y[i]=0;
        }

        printf("\nProduit Matrice Vecteur \n");
        
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
        ProdMatVect(nc,nl,A,x,y);
        fin = omp_get_wtime();
        if(tmax==1){
            for(i=0;i<nl;i++){
                printf("y%d %f\n",i,y[i]);
            }
        }
        printf("\ntemps: %3.6f s\n",fin-debut);
        fprintf(fichier,"\n%f;",fin-debut);
        
        
        printf("\nProduit Matrice Matrice \n");
        if(tmax==1){
            for(i=0;i<nl;i++){
                for(j=0;j<nc;j++){
                     printf("A%d%d %f\n",i,j,A[i][j]);
                }
            }
            for(i=0;i<nl;i++){
                for(j=0;j<nc;j++){
                     printf("B%d%d %f\n",i,j,B[i][j]);
                }
            }
        }
        
        debut = omp_get_wtime();
        ProdMatMat(nc,nl,A,B,&C);
        fin = omp_get_wtime();
        
        if(tmax==1){
            for(i=0;i<nl;i++){
                for(j=0;j<nc;j++){
                     printf("C%d%d %f\n",i,j,C[i][j]);
                }
            }
        }
        
        printf("\ntemps: %3.6f s\n",fin-debut);
        fprintf(fichier,"%f;",fin-debut);
        fprintf(fichier,"%d;%d;",nl,nc);
        
        for(i=0;i<nl;i++){
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
        free(x);
        free(y);
        
        nc*=2;
        nl*=2;
    }
							dummyMethod4();
        
    fclose(fichier);
    
    return 0;
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
gcc -fopenmp -Werror ex7.c -o ex7.out
./ex7.out 
ou bien make 7 
Alors on vas calculer les temps d'execution pour des matrices de taille
croissante et stocker les resultats dans perf7.csv

Si on précise une taille, on lance le calcul et on affiche les resultats
a des fins de verification

gcc -fopenmp -Werror ex7.c -o ex7.out
./ex7.out 2 2
ou bien make 7 x=2 y=2

Produit Matrice Vecteur 
A00 3.000000
A01 7.000000
A10 5.000000
A11 2.000000
x0 3.000000
x1 1.000000
y0 16.000000
y1 17.000000

temps: 0.000007 s

Produit Matrice Matrice 
A00 3.000000
A01 7.000000
A10 5.000000
A11 2.000000
B00 6.000000
B01 5.000000
B10 6.000000
B11 9.000000
C00 60.000000
C01 78.000000
C10 42.000000
C11 43.000000

temps: 0.000012 s
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