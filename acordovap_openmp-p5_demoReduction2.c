//
//  demoReduction.c
//  Código para calcular una integral tomado del curso de colfax
//  Primera versión: secuencial
//
//  Created by José Alberto Incera Diéguez on 03/05/17.
//
//

// Edited: Alan C. Posadas, Mariana
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]){

    if (argc == 2)
        omp_set_num_threads(atoi(argv[1]));

    const int nTrials = 5;

    for(int trial = 0; trial < nTrials; trial++) {
        const double x_upper_bound = 1.0 + trial;
        const double x_lower_bound = 0.0;

        const int nSteps = 100000000;
        const double dx = (x_upper_bound - x_lower_bound)/nSteps;

        double integral = 0.0;

        const double t0 = omp_get_wtime();
																							dummyMethod1();
        #pragma omp parallel for reduction(+: integral)
            for(int i = 0; i < nSteps; i++) {
                // integrate using the midpoint rectangle method
                const double x = x_lower_bound + dx*((double)i + 0.5);
                integral += 1.0 / sqrt(x) * dx;
            }
																							dummyMethod2();
        const double t1 = omp_get_wtime();

        const double analytical_result = (sqrt(x_upper_bound) - sqrt(x_lower_bound))*2;
        const double numerical_result = integral;
        printf("Result = %.8f (Should be %.8f; err = %.8f)  Time = %f ms\n", numerical_result, analytical_result, analytical_result-numerical_result, (t1-t0)*1000.0);
    }
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