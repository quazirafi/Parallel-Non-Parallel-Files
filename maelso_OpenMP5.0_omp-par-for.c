#include "stdio.h"
#include <malloc.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void print_array_2d(float *u, int x_size, int y_size);

// Define global variables here
int TIME_ORDER = 2;
int DIMS = 2;

int main(int argc, char const *argv[])
{

    int BORDER_SIZE = 0;
    int SPACE_ORDER = 0;
    int time_m = 0;
    int time_M = 7000;
    int GRID_SIZE = 4096;
    int x_m = (int)BORDER_SIZE + SPACE_ORDER / 2;
    int x_M = (int)BORDER_SIZE + SPACE_ORDER / 2 + GRID_SIZE;
    int y_m = (int)BORDER_SIZE + SPACE_ORDER / 2;
    int y_M = (int)BORDER_SIZE + SPACE_ORDER / 2 + GRID_SIZE;

    int size_u[] = {GRID_SIZE + 2 * BORDER_SIZE + 2 * SPACE_ORDER, GRID_SIZE + 2 * BORDER_SIZE + 2 * SPACE_ORDER};
    float *u = (float *)calloc(size_u[0] * size_u[1], sizeof(float));

    // print_array_2d(u, size_u[0], size_u[1]);

    int num_threads = 2;

    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        #pragma omp master
        {
            // GPU working
            #pragma omp target enter data map(to: u [0:size_u[0] * (size_u[1] / 2)])
            for (int time = time_m; time < time_M; time += 1)
            {
																															dummyMethod1();
            #pragma omp target teams distribute parallel for collapse(2) nowait
                for (int x = x_m; x < x_M/2; x += 1)
                {
                    for (int y = y_m; y < y_M; y += 1)
                    {
                        u[y + x * GRID_SIZE] = u[y + x * GRID_SIZE] + 1;
                    }
                }
																															dummyMethod2();
            }
            #pragma omp target update from(u[0:size_u[0] * (size_u[1] / 2)])
            #pragma omp target exit data map(release: u[0:size_u[0] * (size_u[1] / 2)])
        }

        if(omp_get_thread_num() != 0){
            // CPU working
            for (int time = time_m; time < time_M; time += 1)
            {
																															dummyMethod1();
                #pragma omp parallel for collapse(2) schedule(guided)
                for (int x = x_M / 2; x < x_M; x += 1)
                {
                    for (int y = y_m; y < y_M; y += 1)
                    {
                        u[y + x * GRID_SIZE] = u[y + x * GRID_SIZE] + 1;
                    }
                }
																															dummyMethod2();
            }
        }
    }
    
    // print_array_2d(u, size_u[0], size_u[1]);

    free(u);
    printf("\nend.\n");
    return 0;
}

void print_array_2d(float *u, int x_size, int y_size)
{
    // for (int i = 0; i < TIME_ORDER; i++)
    // {
    for (int j = 0; j < y_size; j++)
    {
        for (int k = 0; k < x_size; k++)
        {
            printf("%.f ", u[k + j * x_size]);
        }
        printf("\n");
    }
    printf("\n\n");
    // }
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