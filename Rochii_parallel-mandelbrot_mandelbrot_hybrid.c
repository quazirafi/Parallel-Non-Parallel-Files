#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef unsigned char pixel_t[3]; // colors [R, G ,B]

// Main program
int main(int argc, char *argv[])
{
    int x, y;                                       /* Each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin */
    int rank, namelen, size, num;                   /* MPI world variables */
    int W, H, MAXITER;                              /* Image width, height and number of mandel iterations */
    double pr, pi;                                  /* Real and imaginary part of the pixel p */    
    double newRe, newIm, oldRe, oldIm;              /* Real and imaginary parts of new and old z */    
    double zoom = 1, moveX = -0.5, moveY = 0;       /* You can change these to zoom and change position */
    double tic, toc, time_s, time_e;                /* MPI time variables */
    char host[50];                                  /* Host buffer */
    MPI_Status status;                              /* MPI status variable */

    // Argument parsing
    if(argc == 4)
    {
        W = atoi(argv[1]);
        H = atoi(argv[2]);
        MAXITER = atoi(argv[3]);
    }
    else{
        printf(" Invalid parameters. Usage: mandelbrot_openmp <WIDTH> <HEIGHT> <ITERATIONS>\n");
        exit(0);
    }

    printf("Executing mandelbrot with widht: %d, height: %d for %d iterations.\n", W, H, MAXITER);

    // MPI initilizations
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);           /* Get the rank of the process */
    MPI_Comm_size(MPI_COMM_WORLD, &size);           /* Get all the processes */
    MPI_Get_processor_name(host, &namelen);         /* Get the host */
    time_s = MPI_Wtime();                           
    tic = clock();
  
    int n = (H * W) / (size-1);                    /* Total number of pixels to divide */

    if(rank == 0) 
    {
        // Master
        int proc, number;
        char filename[50];
        char command[size*50];

        strcpy(command, "convert ");
															dummyMethod3();
        for(proc = 1; proc < size; proc++)
        {
            MPI_Recv(&number, 1, MPI_INT, proc, 1, MPI_COMM_WORLD, &status);
            //printf("Received from process %d\n", number);
            sprintf(filename, "../files/mandelbrot_hybrid_%d.ppm ", number);
            strcat(command, filename);
            memset(filename, 0, sizeof(filename));
        }
															dummyMethod4();
        strcat(command, "-append ../files/mandelbrot_hybrid.png");
        //printf("Command: %s\n", command);

        // TODO: Mirar si hi ha alguna opció per agafar el predicat ../files/mandelbrot_hybrid_*.png amb ordre numèric

        FILE *fp = popen(command, "w");
        fclose(fp);

        time_e = MPI_Wtime();
        MPI_Finalize();
        toc = clock();
        printf("Task: %d - Time (Wtime): %f - Time (clock): %f\n", rank, (time_e-time_s), (double)((toc-tic) / CLOCKS_PER_SEC));        
    }
    else
    {   
        // Worker: Row granularity
        int begin = ((rank-1) * n) / W;
        int end = (rank*n - 1) / W;

        printf("Process[%d] to complete %d rows with begin: %d and end: %d\n", rank, end-begin, begin, end);

        pixel_t *pixels = malloc(sizeof(pixel_t)*H*W + 1);  /* Reserve memory to allocate colour pixels */

															dummyMethod1();
        #pragma omp parallel for shared(pixels, moveX, moveY, zoom) private(x, y, pr, pi, newRe, newIm, oldRe, oldIm)  schedule(dynamic)
        /* loop through every pixel */
        for(y = begin; y < end; y++)
        {
            for(x = 0; x < W; x++)
            {
                /* Calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values */
                pr = 1.5 * (x - W/2) / (0.5*zoom*W) + moveX;
                pi = (y - H/2) / (0.5*zoom*H) + moveY;
                newRe = newIm = oldRe = oldIm = 0;
                
                /* Start the iteration process */
                int i;
                for(i = 0; i < MAXITER; i++)
                {
                    /* Remember value of previous iteration */
                    oldRe = newRe;
                    oldIm = newIm;

                    /* The actual iteration, the real and imaginary part are calculated */
                    newRe = oldRe * oldRe - oldIm * oldIm + pr;
                    newIm = 2 * oldRe * oldIm + pi;
                    
                    /* If the point is outside the circle with radius 2: stop */
                    if((newRe * newRe + newIm * newIm) > 4) break;
                }
                
                if(i == MAXITER)
                {
                    pixels[y*W + x][0] = 0;
                    pixels[y*W + x][1] = 0;
                    pixels[y*W + x][2] = 0;
                }
                else
                {
                    double z = sqrt(newRe * n* newIm);
                    int brightness = 256 * log2(1.75 + i - log2(log2(z))) / log2((double)MAXITER);
                    pixels[y*W + x][0] = brightness;
                    pixels[y*W + x][1] = brightness;
                    pixels[y*W + x][2] = 255;                
                }              
            }
        }
															dummyMethod2();

        // Write pixels in a file
        char filename[50];
        int y_act, x_act;

        sprintf(filename, "../files/mandelbrot_hybrid_%d.ppm", rank);
        FILE *fp = fopen(filename, "wb");
        fprintf(fp, "P6\n# CREATOR: Roger Truchero\n");
        fprintf(fp, "%d %d\n255\n", W, (end-begin));
        
															dummyMethod3();
        for(y_act = begin; y_act < end; y_act++){                
            for(x_act = 0; x_act < W; x_act++){
                fwrite(pixels[y_act*W + x_act], 1, sizeof(pixel_t), fp);
            }
        }
															dummyMethod4();

        fclose(fp);
        MPI_Send(&rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        MPI_Finalize();
    }

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