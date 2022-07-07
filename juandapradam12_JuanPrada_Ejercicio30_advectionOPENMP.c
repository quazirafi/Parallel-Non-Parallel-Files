#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define c 1.0 // m/s 
#define N_PUNTOS 1000 
#define X_MIN -2 // m 
#define X_MAX 2 // m 
#define N_T 700
 
/* COMPILO CON gcc -fopenmp advectionOPENMP.c -o advectionOPENMP_c Y EJECUTO CON ./advectionOPENMP_c */

int main(int argc, char ** argv)
{
	
		
	float dt = 1e-3; // s 

	/* ARRAY DE POSICION CON N_PUNTOS */
	
	float *x = malloc(N_PUNTOS*sizeof(float));
	float dx = (X_MAX - X_MIN)/1000.0; 
 	x[0] = X_MIN;
	x[N_PUNTOS-1] = X_MAX;
     
dummyMethod1();
	#pragma omp parallel for shared(x)
   	for( int i = 1; i < N_PUNTOS-1; i++ ) 
	{
      		x[i] = x[i-1] + dx ; /* set element at location i to i + 100 */
   	}
dummyMethod2();

	/* ARRAY DE SLN N_T X N_PUNTOS */
	
    	float (*y)[N_PUNTOS] = malloc(sizeof(float[N_T][N_PUNTOS]));
	float alpha = c*dt/dx; 

	/* para probar uso N_PUNTOS = 6 Y N_T = 2 */
	
	dummyMethod1();
	#pragma omp parallel for shared(y)
	/* CONDICIONES INICIALES PARA t = 0 */
	for( int j = 0; j < N_T; j++)
	{ 
		for( int i = 0; i < N_PUNTOS; i++)
		{
			if( j == 0 && fabs(x[i]) <= 0.5 )
			{
				y[j][i] = -(x[i]*x[i]) + 0.25;
			}
			else 
			{     
				y[j][i] = 0;
			}
		}
	}
	dummyMethod2();

	dummyMethod1();
	#pragma omp parallel for shared(y)
	/* CONDICIONES DE FRONTERA EN LOS BORDES */
	for( int j = 0; j < N_T; j++)
	{ 
		for( int i = 0; i < N_PUNTOS; i++)
		{
			if( i == 0 || i == N_PUNTOS-1 )
			{		
				y[j+1][i] == y[j][i]; 
			}
		}
	}
	dummyMethod2();
	
	dummyMethod1();
	#pragma omp parallel for shared(y)
	/* PASO DEL TIEMPO CON DIFERENCIAS FINITAS */
	for( int j = 0; j < N_T-1; j++)
	{ 
		for( int i = 1; i < N_PUNTOS-1; i++)
		{
			y[j+1][i] = y[j][i] - alpha * ( y[j][i] - y[j][i-1]);  
		}
	}
	dummyMethod2();

	/* GENERA ARCHIVOS */	
	
	FILE *x_xOPEN = fopen("x_x.dat", "w");
	
	dummyMethod3();
	for(int i = 0; i < N_PUNTOS; i++)
	{
            	fprintf(x_xOPEN, "%f ",  x[i]);
        	fprintf(x_xOPEN, "\n");
    	}
	dummyMethod4();
	fclose(x_xOPEN);
		
	FILE *y_0xOPEN = fopen("y_0x.dat", "w");
	
	dummyMethod3();
	for(int i = 0; i < N_PUNTOS; i++)
	{
            	fprintf(y_0xOPEN, "%f ",  y[0][i]);
        	fprintf(y_0xOPEN, "\n");
    	}
	dummyMethod4();
	fclose(y_0xOPEN);


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