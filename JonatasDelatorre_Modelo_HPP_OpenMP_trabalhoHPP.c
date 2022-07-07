#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


typedef struct ficha_de_aluno {
    int direcao;
    int posicao;
    int id;
} particula;


particula *copia_particulas_para_next( particula * destino_mat, particula * origem_mat, int np ) {
dummyMethod3();
    for( int i=0; i < np; i++ ) {
        destino_mat[i] = origem_mat[i];
    }
dummyMethod4();
    return destino_mat;
}


int numero_aleatorio( int intervalo, int aux) {
	return ( rand() % intervalo + aux );
}


particula *iniciar_particulas( particula *particulas, int np, int n_posicoes ) {
    int i, j; 
    int posicoes = 0;

							dummyMethod3();
    for( i=0; i < np; i++ ) {
        particulas[i].id = i;
        particulas[i].direcao = numero_aleatorio(5, 1);
        particulas[i].posicao = numero_aleatorio(n_posicoes, 0);
    }
							dummyMethod4();
    return particulas;
}


particula *alocando_vetor_particulas( particula *particulas, int n, int np ) {
    int i;
    particulas = (particula *) malloc( sizeof( particula ) * np );
    /*for( i=0; i < n; i++ ) {
        particulas[i] = (particula) malloc( sizeof( particula ) );
    }*/
    return particulas;
}

int checkParedeLados(int posicao, int n) {
    return posicao % n;
}

void hpp( int N, int n, particula *particulas, particula *next, int np) {
    int i, j, k;
    particula atual;
    int flag;

    int indo_esquerda = 1, indo_direita = 2, indo_baixo = 3, indo_cima = 4, vazio = 0;
    int parede_horizontal, parede_vertical;

							dummyMethod1();
    #pragma omp parallel for private(j, k, parede_horizontal, parede_vertical, atual, flag)
    for( i=0; i < N; i++ ) {
        for( j=0; j < np; j++) {
            flag = 0;
            atual = particulas[i];
            parede_horizontal = checkParedeLados(atual.posicao, n);
            if(atual.direcao == indo_esquerda && parede_horizontal == 0){
                atual.direcao == indo_direita;
            }
            else if(atual.direcao == indo_direita && parede_horizontal == n-1){
                atual.direcao == indo_esquerda;
            }
            else if(atual.direcao == indo_cima && atual.posicao < n){
                atual.direcao == indo_baixo;
            }
            else if(atual.direcao == indo_baixo && atual.posicao > (n*n)-n-1 ){
                atual.direcao == indo_cima;
            }
            else {
                for( k=0; k < np; k++) {
                    if(atual.posicao == particulas[k].posicao && atual.id != particulas[k].id){
                        if( atual.direcao == indo_esquerda ) {
                            flag = 1;
                            particulas[k].direcao == indo_direita;
                            if(atual.posicao > n-1){
                                atual.posicao = atual.posicao - n;
                                atual.direcao = indo_cima;
                            }
                            else {
                                atual.direcao = indo_baixo;
                            }
                        }
                        else if( atual.direcao == indo_direita ) {
                            flag = 1;
                            particulas[k].direcao == indo_esquerda;
                            if(atual.posicao < (n*n)-n){
                                atual.posicao = atual.posicao + n;
                                atual.direcao = indo_baixo;
                            }
                            else {
                                atual.direcao = indo_cima;
                            }
                        }
                        else if( atual.direcao == indo_cima ) {
                            particulas[k].direcao == indo_baixo;
                            if(parede_horizontal < n-1){
                                atual.posicao = atual.posicao + 1;
                                atual.direcao = indo_direita;
                            }
                            else {
                                atual.direcao = indo_esquerda;
                            }
                        }
                        else if( atual.direcao == indo_baixo ) {
                            particulas[k].direcao == indo_cima;
                            if(parede_horizontal != 0){
                                atual.posicao = atual.posicao + 1;
                                atual.direcao = indo_esquerda;
                            }
                            else {
                                atual.direcao = indo_direita;
                            }
                        }
                    }
                }
            }
            if(flag == 0) {
                
                if( atual.direcao == indo_esquerda && parede_horizontal > 0 ) {
                    atual.posicao = atual.posicao - 1;
                }
                else if( atual.direcao == indo_direita && parede_horizontal < n-1 ) {
                    atual.posicao = atual.posicao + 1;
                }
                else if( atual.direcao == indo_cima && atual.posicao > n-1 ) {
                    atual.posicao = atual.posicao - n;
                }
                else if( atual.direcao == indo_baixo && atual.posicao <= n*n-n ) {
                    atual.posicao = atual.posicao + n;
                }
            }
            next[i].posicao = atual.posicao;
            next[i].direcao = atual.direcao;
            next[i].id = atual.id;
        }
        particulas = copia_particulas_para_next(particulas, next, n);
    }
							dummyMethod2();
}


int main() {
    // n x n tamanho da matrix
    // N numero de interacoes
    // curr matriz corrente
    // next matriz obtida a partir de curr
    // np numero de particulas
    int n, N, deno;
    particula *particulas;
    particula *next;
    omp_set_num_threads(4);

    deno = 100;
    n = 2000;

    int np = (n*n)/deno;
    //printf("\n%d\n", np);

    N = 100;

    srand( (unsigned)time(0) );

    particulas = alocando_vetor_particulas( particulas, n, np );
    next = alocando_vetor_particulas( next, n, np );
    particulas = iniciar_particulas( particulas, np, n*n );

    /*for(int i = 0; i < np; i++) {
        printf("\n %d", particulas[i].id);
        printf("\n %d", particulas[i].posicao);
        printf("\n %d", particulas[i].direcao);
    }*/

    double t0, t1, tt;

    t0 = omp_get_wtime();
    hpp( N, n, particulas, next, np);
    t1 = omp_get_wtime();

    tt = t1 - t0;
    printf("Tempo gasto: %g ms.\n", tt);
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