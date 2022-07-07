#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int threadct = 4;

int main(int argc, char** argv) 
{
    int total_throws;
    int throws_inside_circle=0;
    printf("Enter the total number of dart throws: ");
    scanf("%d", &total_throws);     
 
    int i;
    double sq_dist;

dummyMethod1();
    #pragma omp parallel for num_threads(threadct) shared(total_throws) private(i, sq_dist) reduction(+: throws_inside_circle)
    for (i = 0; i < total_throws; i++) 
    {
        double rand_x = (rand() % (INT_MAX - 1)) / (double)INT_MAX;
        double rand_y = (rand() % (INT_MAX - 1)) / (double)INT_MAX;
        // To print the double values
        // printf("%lf\t%lf\n", rand_x, rand_y);
        sq_dist = rand_x*rand_x + rand_y*rand_y;
        if (sq_dist<=1) throws_inside_circle++;
    }
dummyMethod2();
    
    long double pi_estimate_value = 4*throws_inside_circle/((double)total_throws);
    printf("Value of pie is: %.12Lf", pi_estimate_value);

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