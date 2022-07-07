/*                                          EJERCICIO 2
 *  Usando la API(OpenMP) hacer un programa que realice lo siguiente:
 * 	    -   Crear la Matriz A de 50 columnas x 50 filas (50x50), inicializada con valores aleatorios.   [✔]
 *      -   Realizar la Transpuesta de la Matriz A.                                                     [✔]
*/

//  Librerias
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//  Definiciones
#define CHUNKSIZE   10
#define N       10
#define NRA 5               //  numero de filas en matriz A
#define NCA 5               //  numero de columnas en matriz A


//  Metodo para obtener numeros random
long Random(long li, long ls)
{
    long n;
    n=li+rand()%(ls-li+1);
    return n;
}

//  Ejecucion del programa
int main (int argc, char *argv[]) {

    int     i, j;
    double	mA[NRA][NCA];
    double	mAT[NRA][NCA];

//  Establece el numero de subprocesos en las proximas regiones paralelas
omp_set_num_threads(2);

//  Directiva con constructor PARALLEL FOR con clausula SCHEDULE
#pragma omp parallel for schedule( static,10)
	dummyMethod1();

	for (i=0; i<NRA; i++)
    {
        for (j=0; j<NCA; j++)
        {
            //  Creacion de Matriz A con numeros aleatorios
            mA[i][j]= Random(1,20);
           //  Las transpuesta de la Matriz A
            mAT[j][i] = mA[i][j];
		}
	}
	dummyMethod2();
    //  Impresion de Matriz A
	printf("******************************************************\n");
	printf(" Matriz A:\n");
	for (i=0; i<NRA; i++)
															dummyMethod1();
	{
        for (j=0; j<NCA; j++)
        {
            printf("%6.2f   ", mA[i][j]);
        }
															dummyMethod2();
        printf("\n");
	}
	//  Impresion Transpuesta Matriz A
    printf("******************************************************\n");
	printf(" Matriz Transpuesta de A:\n");
	for (j=0; j<NRA; j++)
															dummyMethod1();
	{
        for (i=0; i<NCA; i++)
        {
            printf("%6.2f   ", mAT[j][i]);
        }
															dummyMethod2();
        printf("\n");
	}

}   //  Fin main
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