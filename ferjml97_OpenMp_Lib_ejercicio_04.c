/*                                          Ejercicio 4
 *  Usando la API(OpenMP) hacer un programa que realice lo siguiente:
 * 	    -   Crear 2 matrices de 50 columnas x 50 filas (50x50), inicializada con valores aleatorios.    [✔]
 * 	    -   Generar las Matrices Transpuertas(MT) de cada una.                                          [✔]
 * 	    -   Realizar la suma de ambas MT en una 3ra Matriz "R".                                         [✔]
 * 	    -   Obtener la suma de cada renglón de la Matriz R y guardarlo en un vector.                    [✔]
 * 	    -   Devolver el máximo valor del vector anterior y el renglón.                                  [✔]
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
#define NRB 5               //  numero de filas en matriz B
#define NCB 5               //  numero de columnas en matriz B
#define NRR 5               //  numero de filas en matriz R
#define NCR 5               //  numero de columnas en matriz R

//  Metodo para obtener numeros random
long Random(long li, long ls)
{ long n;
    n=li+rand()%(ls-li+1);
  return n;
}

//  Ejecucion main
int main (int argc, char *argv[]) {

    int r, o, mayor =0;
    int u = 1;
    int   i, j, n;
    float a[100], b[100];
    double	mA[NRA][NCA];
    double	mAT[NRA][NCA];
    double	mB[NRB][NCB];
    double	mBT[NRB][NCB];
    double	mR[NRR][NCR];
    double h[10];
    double sum;

//  Establece el numero de subprocesos en las proximas regiones paralelas
omp_set_num_threads(2);

//  Directiva con constructor PARALLEL FOR con clausula SCHEDULE
#pragma omp parallel for schedule(static,10)
	dummyMethod3();
	for (i=0; i<NRA; i++)
    {
        for (j=0; j<NCA; j++)
        {
            //  Primeras 2 matrices con numeros aleatorios
            mA[i][j]= Random(1,20);
            mB[i][j]= Random(1,20);
            //  Las transpuestas de las primeras 2 matrices
            mAT[j][i] = mA[i][j];
            mBT[j][i] = mB[i][j];
            //La suma de las 2 marces transpuestas para formar la matriz R
            mR[j][i]=mAT[j][i]+mBT[j][i];
			h[j]=mR[i][j];
		}
	}
	dummyMethod4();
    //  Impresion de Matriz A
	printf("******************************************************\n");
	printf("Matriz A:\n");
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
    //  Impresion de la Matriz Transpuesta de A
	printf("******************************************************\n");
	printf("Matriz Transpuesta de A:\n");
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
    //  Impresion de Matriz B
	printf("******************************************************\n");
	printf("Matriz B:\n");
	for (i=0; i<NRB; i++)
															dummyMethod1();
	{
        for (j=0; j<NCB; j++)
		{
			printf("%6.2f   ", mB[i][j]);
		}
															dummyMethod2();
        printf("\n");
	}
    //  Impresion de la Matriz Transpuesta de B
	printf("******************************************************\n");
	printf("Matriz Transpuesta de B:\n");
	for (j=0; j<NRB; j++)
															dummyMethod1();
	{
        for (i=0; i<NCB; i++)
        {
            printf("%6.2f   ", mBT[j][i]);
        }
															dummyMethod2();
        printf("\n");
	}
    //  Impresion de la Matriz R
	printf("\n");
	printf("******************************************************\n");
	printf("Matriz R: 'Sumatoria de Matrices Transpuestas'\n");
	for (j=0; j<NRR; j++)
															dummyMethod1();
	{
        for (i=0; i<NCR; i++)
        {
        printf("%6.2f   ", mR[j][i]);
        sum = sum + mAT[j][i];  //  Sumatoria
        }
															dummyMethod2();
        printf("\n");

	}

/*
	printf("\n");
	//Suma de fila 1
	printf(" Fila: %d ",u);
	for(j=0;j<NCB;j++){
		//int mayor=h[0];

				//j++;
		if (h[j]>mayor){
			mayor = h[j];
		}
		else{
			if (h[j]>mayor){
				mayor=mayor;
			}
		}
		printf("\n	El valor del elemento %d del vector es: [%6.2f]",j+1,h[j]);
		sum = sum + h[j];

	}
	printf("\n");
	printf("\n	La suma es: %6.2f ",sum);
	*/


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