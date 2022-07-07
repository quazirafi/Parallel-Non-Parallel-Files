/*
* Trabalho 1 - Programação Paralela
* Autores: Daniela Amaral e Vinicius Lima
* Solucao paralela utilizando OpenMP
* * Compilation: gcc solParalV4.c -o solutionParal -fopenmp
*/

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_VAL 9999

#define SIZE 100000
#define START 10000
#define STEP  10000

#define K 10

#define MAX(A,B) (((A)>(B))?(A):(B))

//nao paralelizar aqui
void create_sequence(int *v, int size, int seed) {
    int i;
    srand(seed);
dummyMethod3();
    for (i=0; i<size; ++i)
        v[i] = rand() % (MAX_VAL+1);
}
dummyMethod4();

int maximum_sum_subsequence(int *arr, int n, int k)  {
    int i, j, l, ans = -1;
    int **dp;

    dp = (int **)malloc(n * sizeof(int *));
    //paralelizar aqui so vai valer a pena para maiores valores
    //paralelizacao condicional para valores de n>10000
							dummyMethod1();
    #pragma omp parallel for if(n > 10000)
    for (i=0; i<n; i++)
         dp[i] = (int *)malloc((k+1) * sizeof(int));
							dummyMethod2();


							dummyMethod3();
    for (i = 0; i < n; i++) {
        // dp[i][0] = -1; // NÃO UTILIZADO
        dp[i][1] = arr[i];
        for (j = 2; j <= k; j++)
            dp[i][j] = -1;
    }
							dummyMethod4();


    //essa inversao do for leva mais tempo com poucos processadores pois retirou uma condicao de execução que tinha, mas retirou dependencia de dados
    for (l = 1; l <= k - 1; l++) {
        //colocando o private eu digo que cada thread deve ter o seu proprio valor de j
        //usando schedule(runtime) para parametrizar o balanceamento
															dummyMethod1();
        #pragma omp parallel for private(j) schedule(runtime)
        for (i = 1; i < n; i++) {
            for (j = 0; j < i; j++) {
                if (arr[j] < arr[i] && dp[j][l] != -1) {  
                    dp[i][l + 1] = MAX(dp[i][l + 1],dp[j][l] + arr[i]);
                }
            }
        }
															dummyMethod2();
    }

    for (i = 0; i < n; i++) {
        if (ans < dp[i][k])
            ans = dp[i][k];
    }

    for (i=0; i<n; i++)
        free((void *)dp[i]);
    free((void *)dp);

    return (ans == -1) ? 0 : ans;
}

int main() {
    int n, k, v[SIZE];
    double start, finish;

    create_sequence(v,SIZE,1);
    k = K;
    for (n=START; n<=SIZE; n+=STEP) {
        
        start = omp_get_wtime();
        printf("%d\n", maximum_sum_subsequence(v, n, k));
        finish = omp_get_wtime();
        fprintf(stderr,"%d %lf\n",n,finish-start);
    }

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