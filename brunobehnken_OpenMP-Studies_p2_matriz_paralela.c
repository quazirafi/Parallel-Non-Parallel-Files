/* Programa 1:
 * Uma matriz 4xn deve ser preenchida com o valor 1.0
 * Cada uma das 4 threads deve preencher uma coluna */ 

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[]) {
	int j;
	int i, tid, n = 100000, m = 100;
	float a[n][m];

	omp_set_num_threads(10);
dummyMethod1();
	#pragma omp parallel for default(none) shared(a,n,m) private(tid,i)
		for (j = 0; j < m; j++) {
			for (i = 0; i < n; i++)	{
				a[i][j] = 1.0;
			}
		}
dummyMethod2();

dummyMethod3();
	for (i = 0; i < 4; i++)
		printf("%1.2f ",a[50][i]);
	printf("\n");
dummyMethod4();
	return 0;
}

// quando colocamos #pragma omp parallel for
// o unico comando que pode ter dentro da regiao paralela eh um for,
// e por isso nao devemos usar as chaves.

// clausula firstprivate(n): n éh uma variavel private mas eh inicializada
// com o valor que foi atribuido a ela anteriormente.
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