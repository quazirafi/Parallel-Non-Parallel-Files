/**
* This program do the integral process
* folowing the riemman method with openmp
**/

#include<stdio.h>
#include<math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double carre (double x){
	return x * x;
}

int main()
{
	float e; //precision

	// the interval length, air with mj as heigth, air with MJ as height, first element of small interval
	// second element of small interval, image of small element of the current interval
	// image of the biggest element of the current interval, born a, born b, 
	//number of rectangle built, number of retctable to add each iteration
	double l, Ii, Is, xb1, xb2, mj, MJ, a, b, c;

	int n, i, comptor = 0;

	//initialization

	a = 0.0; b = 5.0; e = 0.001;  n = 1; c = 1.0;

	do
	{
		Ii = 0; Is = 0; //init Ii and Is in zero
		n = n + c; //increasing the rectangle number
		l = (b - a) / n; //length of each intervall

		

			dummyMethod1();
		#pragma omp parallel for reduction(+:Ii) reduction(+:Is)
		for (i = 0; i < n; i++){
		
			xb1 = a + (i * l);
			xb2 = a + ((i + 1) * l);

			mj = carre(xb1);
			MJ = carre(xb2);			

			Ii += ((xb2 - xb1) * mj);
			Is += ((xb2 - xb1) * MJ);
			printf("end of loop %d \n", comptor++);
		}
			dummyMethod2();

		//to illustrate the amdal low, decommenting this line will decrease signicately the speed
		//because it a sequential instruction, but when commented the program run 5 times faster and a sequential one
		
		// printf("the iteration %d \n", comptor++);	

	}while(fabs(Is - Ii) > e);

	printf("Ii is : %f and Is is : %f \n", Ii, Is);

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