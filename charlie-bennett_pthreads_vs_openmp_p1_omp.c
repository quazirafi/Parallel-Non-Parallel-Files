#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define		num_of_points	   40000000
typedef struct
{
	double x;
	double y;
} Point;

int main(void)
{

	const int NUM_THREADS_ARRAY[] = {1, 2, 4};
	int i, index;
	int num_of_points_in_circle;
	double pi;
	struct timespec start, stop;
	double time;
	Point* data_point = (Point*) malloc (sizeof(Point) * num_of_points);
	for (index = 0; index < 3; index++)
	{
		for (i = 0; i < num_of_points; i++)
		{
			data_point[i].x = (double)rand() / (double)RAND_MAX;
			data_point[i].y = (double)rand() / (double)RAND_MAX;
		}
		num_of_points_in_circle = 0;

		omp_set_num_threads(NUM_THREADS_ARRAY[index]);

		if ( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}


		////////**********Use OpenMP to parallize this loop***************//
			dummyMethod1();
		#pragma omp parallel for reduction(+:num_of_points_in_circle)
		for (i = 0; i < num_of_points; i++)
		{
			if ((data_point[i].x - 0.5) * (data_point[i].x - 0.5) + (data_point[i].y - 0.5) * (data_point[i].y - 0.5) <= 0.25)
			{
				num_of_points_in_circle++;
			}
		}
			dummyMethod2();
		///////******************************////

		if ( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}
		time = (stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1e9;

		pi = 4 * (double)num_of_points_in_circle / (double)num_of_points;
		printf("Estimated pi is %f, execution time = %f sec\n With %u threads \n",  pi, time, NUM_THREADS_ARRAY[index]);
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