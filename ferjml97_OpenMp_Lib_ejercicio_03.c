/*                                          EJERCICIO 3
 *  Usando la API(OpenMP) hacer un programa que realice lo siguiente:
 * 	    -   Crear la Matriz A de 5 columnas x 5 filas (50x50), inicializada con valores aleatorios.     [✔]
 *      -   Realizar la Transpuesta de la Matriz A.                                                     [✔]
 * 	    -   Obtener la suma de cada fila de la Matriz Transpuesta de A y guardarlo en un vector.        [✔]
 * 	    -   Devolver el maximo valor del vector anterior y el renglón.                                  [✔]
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

    int     i,z, j,n, f;
    double  mA[NRA][NCA];
    double	mAT[NRA][NCA];
    double sum = 0;
    double mayor =0;
    int u = 1;
    double h[5];

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
	printf(" Matriz Transpuesta de A:                     Total\n");
	for (j=0; j<NRA; j++)
															dummyMethod1();
	{
        for (i=0; i<NCA; i++)
        {
            printf("%6.2f   ", mAT[j][i]);
            sum = sum + mAT[j][i];  //  Sumatoria
        }
															dummyMethod2();
        printf("%6.2f",sum);
        if(j < NRA) // Mayor suma por fila
        {
            h[j] = sum;
            if( h[j] > mayor)
            {
                mayor = h[j];
                f = j;
            }
        }
        u ++;
        sum = 0;
        printf("\n");
	} //    Fin if
    printf("\n Mayor renglon: %d con sumatoria de: %6.2f \n", f, mayor);

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