/*
   Erro parar gerar struct.
   Erro na anotação dos parâmetros

   This program performs K nearest neighbors on the GPU with 
   dynamically allocated matrices.
    
    Author: Gleison Souza Diniz Mendon?a 
    Date: 04-01-2015
    version 2.0
    
    Run:
    ipmacc k-nearest_gpu.c -o k-nearest
    ./k-nearest matrix-size
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "../../common/mgbenchUtilFunctions.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 128
#define SIZE_2 SIZE/2
#define GPU_DEVICE 0
#define ERROR_THRESHOLD 0.05
#define default_v 100000.00

typedef struct point
{
    int x;
    int y;
}point;

typedef struct sel_points
{
    int position;
    float value;
}sel_points;


void init(point *pivots, point *the_points, sel_points *selected_cpu, sel_points *selected_gpu)
{
    int i,j;
    #pragma acc data copy(pivots[0:64])
    #pragma acc kernels
    #pragma acc loop independent
							dummyMethod3();
    for(i=0;i<SIZE_2;i++)
    {
        pivots[i].x = i*3;
        pivots[i].y = i*2;
    }
							dummyMethod4();

    #pragma acc data copy(the_points[0:128],selected_cpu[0:16512],selected_gpu[0:16512])
    #pragma acc kernels
    #pragma acc loop independent
							dummyMethod3();
    for(i=0;i<SIZE;i++)
    {
        the_points[i].x = i*3;
        the_points[i].y = i*2;
        
        for(j=0;j<SIZE;j++)
        {
            selected_cpu[i*SIZE+j].position = 0;
            selected_cpu[i*SIZE+j].value = default_v;
            selected_gpu[i*SIZE+j].position = 0;
            selected_gpu[i*SIZE+j].value = default_v;
        }
    }
							dummyMethod4();
}

void k_nearest_gpu(point *pivots, point *the_points, sel_points *selected)
{
    int i,j,m;
 
    #pragma omp target device (GPU_DEVICE)
    #pragma omp target map(to: pivots[0: SIZE_2], the_points[0:SIZE]) map(tofrom: selected[0:SIZE*SIZE])
    {
															dummyMethod1();
	#pragma omp parallel for collapse(2)
        #pragma acc data copy(pivots[0:64],the_points[0:128],selected[0:8320])
        #pragma acc kernels
        #pragma acc loop independent
        for(i=0;i<SIZE_2;i++)
        {
            for(j=0;j<SIZE;j++)
            {
                float distance,x,y;
                x = pivots[i].x - the_points[j].x;
                y = pivots[i].y - the_points[j].y;
                x = x * x;
                y = y * y;
                        
                distance = x + y;
                distance = sqrt(distance);
                        
                selected[i*SIZE+j].value = distance;
                selected[i*SIZE+j].position = j;
            }
        }
															dummyMethod2();
  
        /// for each line in matrix
        /// order values
        
															dummyMethod1();
	#pragma omp parallel for collapse(1)
        #pragma acc data copy(selected[0:8320])
        #pragma acc kernels
        #pragma acc loop independent
        for(i=0;i<SIZE_2;i++)
        {
            for(j=0;j<SIZE;j++)
            {
                for(m=j+1;m<SIZE;m++)
                {
                    if(selected[i*SIZE+j].value>selected[i*SIZE+m].value)
                    {
                        sel_points aux;
                        aux = selected[i*SIZE+j];
                        selected[i*SIZE+j] = selected[i*SIZE+m];
                        selected[i*SIZE+m] = aux;
                     }
                } 
            }
        }
															dummyMethod2();
    }
}
void k_nearest_cpu(point *pivots, point *the_points, sel_points *selected)
{
    int i,j;
    #pragma acc data copy(pivots[0:64],the_points[0:128],selected[0:8320])
    #pragma acc kernels
    #pragma acc loop independent
							dummyMethod3();
    for(i=0;i<SIZE_2;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            float distance,x,y;
            x = pivots[i].x - the_points[j].x;
            y = pivots[i].y - the_points[j].y;
            x = x * x;
            y = y * y;
            
            distance = x + y;
            distance = sqrt(distance);
            
            selected[i*SIZE+j].value = distance;
            selected[i*SIZE+j].position = j;
        }
    }
							dummyMethod4();
    
    #pragma acc data copy(selected[0:8320])
    #pragma acc kernels
    #pragma acc loop independent
							dummyMethod3();
    for(i=0;i<SIZE_2;i++)
    {
        /// for each line in matrix
        /// order values
        int j;
        for(j=0;j<SIZE;j++)
        {
            int m;
            for(m=j+1;m<SIZE;m++)
            {
                if(selected[i*SIZE+j].value>selected[i*SIZE+m].value)
                {
                    sel_points aux;
                    aux = selected[i*SIZE+j];
                    selected[i*SIZE+j] = selected[i*SIZE+m];
                    selected[i*SIZE+m] = aux;
                }
            } 
           
        }
    }
							dummyMethod4();
}

void compareResults(sel_points* B, sel_points* B_GPU)
{
  int i, j, fail;
  fail = 0;
	
  // Compare B and B_GPU
  #pragma acc data copy(B[0:16512],B_GPU[0:16512])
  #pragma acc kernels
  #pragma acc loop independent
			dummyMethod3();
  for (i=0; i < SIZE; i++) 
    {
      for (j=0; j < SIZE; j++) 
	{
	  //Value
	  if (percentDiff(B[i*SIZE + j].value, B_GPU[i*SIZE + j].value) > ERROR_THRESHOLD) 
	    {
	      fail++;
	    }
	  //Position
	  if (percentDiff(B[i*SIZE + j].position, B_GPU[i*SIZE + j].position) > ERROR_THRESHOLD) 
	    {
	      fail++;
	    }
	}
    }
			dummyMethod4();
  // Print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", ERROR_THRESHOLD, fail);
	
}

int main(int argc, char *argv[])
{
    double t_start, t_end;	
    point *pivots;
    point *the_points;
    sel_points *selected_cpu, *selected_gpu;
    
    fprintf(stdout,"<< K-nearest >>\n");

    pivots = (point *) malloc(sizeof(point) * SIZE);
    the_points = (point *) malloc(sizeof(point) * SIZE);
    selected_cpu = (sel_points *)malloc(sizeof(sel_points) * SIZE * SIZE);   
    selected_gpu = (sel_points *)malloc(sizeof(sel_points) * SIZE * SIZE);

    init(pivots, the_points, selected_cpu, selected_gpu);

    t_start = rtclock();
    k_nearest_gpu(pivots, the_points, selected_gpu);
    t_end = rtclock();
    fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);	

    t_start = rtclock();
    k_nearest_cpu(pivots, the_points, selected_cpu);
    t_end = rtclock();
    fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);	

    compareResults(selected_cpu, selected_gpu);

    free(selected_cpu);
    free(selected_gpu);
    free(pivots);
    free(the_points);

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