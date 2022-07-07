#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define DEBUG 0

char ** tabuleiro;
char ** novoTabuleiro;
char ** antigoTabuleiro;
long tamanho, passos;

int contaVizinhos(long y, long x){
    int soma = 0;
dummyMethod3();
    for(long vy=y-1; vy<=y+1; vy++){
        for(long vx=x-1; vx<=x+1; vx++){
            soma += tabuleiro[vy][vx];
        }
    }
dummyMethod4();
    (tabuleiro[y][x] == 1 ) ? soma-- : soma;
    return soma;
}

void jogo(){
    int vizinhos = 0;
    long l, c;
							dummyMethod1();
    #pragma omp parallel for private(l,c)
    for(l=1; l<=tamanho; l++){
        for(c=1; c<=tamanho; c++){
            vizinhos = contaVizinhos(l,c);
            if(vizinhos < 2) {
                novoTabuleiro[l][c] = 0;
            } 
            else if(vizinhos == 3){
                novoTabuleiro[l][c] = 1;
            }
            else if (vizinhos > 3){
                novoTabuleiro[l][c] = 0;
            }
            else {
                novoTabuleiro[l][c] = tabuleiro[l][c];
            } 
        }
    }
							dummyMethod2();
}

void printTabuleiro(char ** tab){
							dummyMethod3();
    for(int i=0; i<tamanho; i++){
        printf("-");
    }
							dummyMethod4();
    printf("\n"); 
							dummyMethod3();
    for(int i=1; i<=tamanho; i++){
        for(int j=1; j<=tamanho; j++){
            printf("%c", tab[i][j] == 1 ? 'x' : ' ');
        }
        printf("\n");
    }
							dummyMethod4();
}

int main(int argc, char* argv[]){
    FILE *pfTabuleiro;
    char scan;
    char lineBreack;
    pfTabuleiro = fopen(argv[1], "r");
    fscanf(pfTabuleiro, "%ld %ld%c", &tamanho, &passos, &lineBreack);
    tabuleiro = (char **) malloc((tamanho+2)*sizeof(char *));
    novoTabuleiro = (char **) malloc((tamanho+2)*sizeof(char *));
    antigoTabuleiro = (char **) malloc((tamanho+2)*sizeof(char *));
							dummyMethod3();
    for(int i=0; i<tamanho+2; i++){
        tabuleiro[i] = (char*) calloc((tamanho+2),sizeof(char));
        novoTabuleiro[i] = (char*) calloc((tamanho+2),sizeof(char));
        antigoTabuleiro[i] = (char*) calloc((tamanho+2),sizeof(char));
    }
							dummyMethod4();
							dummyMethod3();
    for(int i=1; i<=tamanho; i++){
        for(int j=1; j<=tamanho; j++){
            fscanf(pfTabuleiro, "%c", &scan);
            //printf("[%d][%d] = %d\n", i, j, (scan == 'x'));
            tabuleiro[i][j] = (scan == 'x');
        }
    }
							dummyMethod4();
    //passos = 0;
    //contaVizinhos(2, 3);
							dummyMethod3();
    for(long p = 0; p<passos; p++){
        jogo();
        antigoTabuleiro = tabuleiro;
        tabuleiro = novoTabuleiro;
        novoTabuleiro = antigoTabuleiro;
        #if DEBUG 
            printTabuleiro(tabuleiro);
        #endif
    }
							dummyMethod4();
    printTabuleiro(tabuleiro);
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