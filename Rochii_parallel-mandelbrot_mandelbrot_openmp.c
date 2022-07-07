//
//  mandelbrot_openmp.c
//  
//
//  The Mandelbrot calculation is to iterate the equation
//  z = z*z + c, where z and c are complex numbers, z is initially
//  zero, and c is the coordinate of the point being tested. If
//  the magnitude of z remains less than 2 for ever, then the point
//  c is in the Mandelbrot set. In this code We write out the number of iterations
//  before the magnitude of z exceeds 2, or UCHAR_MAX, whichever is
//  smaller.//
//
//

// Includes
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef unsigned char pixel_t[3]; // colors [R, G ,B]

// Main program
int main(int argc, char *argv[])
{
    int x, y;                                       /* each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin */
    double pr, pi;                                  /* real and imaginary part of the pixel p */    
    double newRe, newIm, oldRe, oldIm;              /* real and imaginary parts of new and old z */    
    double zoom = 1, moveX = -0.5, moveY = 0;       /* you can change these to zoom and change position */     
    double wtime = omp_get_wtime();                 /* get start time */

    int W;          /* image width */
    int H;          /* image height */
    int MAXITER;    /* after how much iterations the function should stop */
    
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

    pixel_t *pixels = malloc(sizeof(pixel_t)*H*W);  /* reserve memory to allocate colour pixels */

							dummyMethod1();
    #pragma omp parallel for shared(pixels, moveX, moveY, zoom) private(x, y, pr, pi, newRe, newIm, oldRe, oldIm)  schedule(dynamic)
    /* loop through every pixel */
    for(y = 0; y < H; y++)
    {        
        for(x = 0; x < W; x++)
        {
            /*  calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values */
            pr = 1.5 * (x - W / 2) / (0.5 * zoom * W) + moveX;
            pi = (y - H / 2) / (0.5 * zoom * H) + moveY;
            newRe = newIm = oldRe = oldIm = 0; /* these should start at 0,0 */
            
            int i; /* "i" will represent the number of iterations */

            /* start the iteration process */
            for(i = 0; i < MAXITER; i++)
            {
                /* remember value of previous iteration */
                oldRe = newRe;
                oldIm = newIm;

                /* the actual iteration, the real and imaginary part are calculated */
                newRe = oldRe * oldRe - oldIm * oldIm + pr;
                newIm = 2 * oldRe * oldIm + pi;
                
                /* if the point is outside the circle with radius 2: stop */
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
                double z = sqrt(newRe * newRe + newIm * newIm);
                int brightness = 256 * log2(1.75 + i - log2(log2(z))) / log2((double)MAXITER);
                pixels[y*W + x][0] = brightness;
                pixels[y*W + x][1] = brightness;
                pixels[y*W + x][2] = 255;
            }                   
        }
    }
							dummyMethod2();

    fprintf(stderr, "\n Time = %g seconds.\n", omp_get_wtime() - wtime);
    FILE * fp = fopen("../files/mandelbrot_openmp.ppm","wb");

    fprintf(fp, "P6\n# CREATOR: Eric R. Weeks / mandel program\n");
    fprintf(fp, "%d %d\n255\n", W, H);

    int y_act, x_act;
							dummyMethod3();
    for(y_act = 0; y_act < H; y_act++){                
        for(x_act = 0; x_act < W; x_act++){
            fwrite(pixels[y_act*W + x_act], 1, sizeof(pixel_t), fp);
        }
    }
							dummyMethod4();

    fclose(fp);
    free(pixels);
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