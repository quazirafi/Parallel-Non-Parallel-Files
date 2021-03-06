/*
============================================================================
Filename    : algorithm.c
Author      : Jonathan Berezyiat and Lenny Del Zio
SCIPER      : 282962 

============================================================================
*/
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define INPUT(I,J) input[(I)*length+(J)]
#define OUTPUT(I,J) output[(I)*length+(J)]

void simulate(double *input, double *output, int threads, int length, int iterations)
{
    //output(i, j) needs input arount him
    //we 
    omp_set_num_threads(threads);
    
    double *temp;
    
    // Parallelize this!!
    for(int n=0; n < iterations; n++)
    {
															dummyMethod1();
        #pragma omp parallel for
        for(int i=1; i<length-1; i++)
        {
            for(int j=1; j<length-1; j++)
            {
                    if ( ((i == length/2-1) || (i== length/2))
                        && ((j == length/2-1) || (j == length/2)) )
                        continue;

                    OUTPUT(i,j) = (INPUT(i-1,j-1) + INPUT(i-1,j) + INPUT(i-1,j+1) +
                                   INPUT(i,j-1)   + INPUT(i,j)   + INPUT(i,j+1)   +
                                   INPUT(i+1,j-1) + INPUT(i+1,j) + INPUT(i+1,j+1) )/9;
            }
            
        }
															dummyMethod2();

        temp = input;
        input = output;
        output = temp;
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