#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define A 0.0
#define B 2.0
#define EPSILON 10E-8
#define INIT_N 1000

double left_rect_method(long steps);
double mid_rect_method (long steps);
double right_rect_method (long steps);
double trapezium_method (long steps);
double simpsons_method (long steps);
double f(double x);


double left_rect_method (long steps) 
{
    double x, sum = 0.0,
           step_size = (double)(B - A) / steps;

dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < steps; i++)
    {
        x = A + i * step_size;
        sum += f(x);
    }
dummyMethod2();

    sum *= step_size;

    return sum;
}

double mid_rect_method (long steps) 
{
    double x, sum = 0.0,
           step_size = (double)(B - A) / steps;

							dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < steps; i++)
    {
        x = A + (i + 0.5) * step_size;
        sum += f(x);
    }
							dummyMethod2();

    sum *= step_size;

    return sum;
}

double right_rect_method (long steps) 
{
    double x, sum = 0.0,
           step_size = (double)(B - A) / steps;

							dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < steps; i++)
    {
        x = A + (i + 1) * step_size;
        sum += f(x);
    }
							dummyMethod2();
    
    sum *= step_size;

    return sum;
}

double trapezium_method (long steps) 
{
    double x, sum = 0.0,
           step_size = (double)(B - A) / steps;

							dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < steps; i++)
    {
        x = A + i * step_size;
        sum += f(x);
    }
							dummyMethod2();

    sum += (f(A) + f(B)) / 2;
    sum *= step_size;

    return sum;
}

double simpsons_method (long steps) 
{
    double x_lo, x_hi, x_mid, sum = 0.0,
           step_size = (double)(B - A) / steps;

							dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < steps; i++)
    {
        x_lo = A + i * step_size;
        x_hi = A + (i + 1) * step_size;
        x_mid = (x_lo + x_hi) / 2;

        sum += f(x_lo) + 4 * f(x_mid) + f(x_hi);
    }
							dummyMethod2();

    sum *= step_size / 6.0;

    return sum;
}


double f(double x)
{
    return exp( sqrt(1.1 * x + 1.0) );
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