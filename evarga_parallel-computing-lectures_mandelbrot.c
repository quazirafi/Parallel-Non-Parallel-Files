/****************************************************************************
 * 
 * Original source: http://faculty.knox.edu/dbunde/teaching/mandelbrot/mandelbrot.c
 * 
 * mandelbot.c
 *
 * Creates a bitmap (.bmp) file displaying part of the Mandelbrot set.
 *
 * Based on bitmap code written by David J. Malan and code for
 * computing the Mandelbrot set from Wikipedia
 * (http://en.wikipedia.org/wiki/Mandelbrot_set).
 *
 * NOTE: implementation of the parallel version using OpenMP. Always set
 * in advance the OMP_NUM_THREADS environment variable to the number of threads.
 * Also, try setting the dimensions to 1200 x 12000 to better observe the difference
 * between the sequential and parallel versions. With 8 threads the speedup is
 * already remarkable. Of course, this same code base can be treated as a
 * sequential program if compiled without OpenMP support.
 *
 * To build this code using OpenMP on macOS High Sierra follow the instructions
 * at https://iscinumpy.gitlab.io/post/omp-on-high-sierra/ Provided that libomp
 * is already installed just execute the next command:
 * clang -Xpreprocessor -fopenmp -lomp -o mandelbrot mandelbrot.c
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "bmp.h"

enum Color { WHITE = 255, BLACK = 0 };
RGBTRIPLE** pixels;                // 2D array of pixels
const int DEFAULT_DIMENSION = 800;
int numRows = DEFAULT_DIMENSION;   // number of rows in image
int numCols = DEFAULT_DIMENSION;   // number of cols

double mandelbrot(double x, double y) {
    int maxIteration = 1000;
    int iteration = 0;

    double re = 0;   //current real part
    double im = 0;   //current imaginary part
    while (re * re + im * im <= 4 && iteration < maxIteration) {
        double temp = re * re - im * im + x;
        im = 2 * re * im + y;
        re = temp;

        iteration++;
    }

    if (iteration != maxIteration)
        return WHITE;
    else 
        return BLACK;
}

int save_image(char* filename, RGBTRIPLE** pixels) {
    FILE* outptr = fopen(filename, "w");

    if (outptr == NULL) {
        fprintf(stderr, "Could not create %s\n", filename);
        return 3;
    }

    // Padding for each row (each must be multiple of 4 bytes).
    int padding = (4 - (numCols * sizeof(RGBTRIPLE)) % 4) % 4;
    int fileSize = numRows * (numCols + padding) * 3 + 54;  // 54 is header size

    BITMAPFILEHEADER bf;
    bf.bfType = 0x4d42;     //"magic number"; type of file = bitmap
    bf.bfSize = fileSize;   //size of file in bytes
    bf.bfReserved1 = 0;     //application signature (matters for some reason)
    bf.bfReserved2 = 0;
    bf.bfOffBits = 54;      //location of pixels

    BITMAPINFOHEADER bi;
    bi.biSize = 40;         //header size
    bi.biWidth = numCols;   //image width in pixels
    bi.biHeight = numRows;  //image height in pixels
    bi.biPlanes = 1;        //single plane of image
    bi.biBitCount = 24;     //24 bits per pixel
    bi.biCompression = 0;   //no compression
    bi.biSizeImage = numRows * numCols * 3;  //number of bytes in image
    bi.biXPelsPerMeter = 2834;  //pixels per meter (!?) in X direction
    bi.biYPelsPerMeter = 2834;  //in Y direction
    bi.biClrUsed = 0;       //we don't use color table
    bi.biClrImportant = 0;  //ditto

    // write outfile's headers
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // write out the pixels
							dummyMethod3();
    for (int j = 0; j < numRows; j++) {
        for (int i = 0; i < numCols; i++)
            fwrite(&(pixels[i][j]), sizeof(RGBTRIPLE), 1, outptr); 

        for (int k = 0; k < padding; k++)  // add padding if necessary
            fputc(0x00, outptr);
    }
							dummyMethod4();

    fclose(outptr);
    return 0;
}

RGBTRIPLE** create_image() {
    // create array of pixels to store image
    pixels = malloc(numCols * sizeof(RGBTRIPLE*));
							dummyMethod3();
    for(int i = 0; i < numCols; i++)
        pixels[i] = malloc(numRows * sizeof(RGBTRIPLE));
							dummyMethod4();

    double x, y;
    enum Color color;

    // dynamic scheduling is good if the load isn't well-balanced
    // if static scheduling may ensure an acceptable load balancing, then
    // the dynamic variant may introduce unnecessary overhead
							dummyMethod1();
    #pragma omp parallel for private(x,y,color) schedule(dynamic)    

    // set pixels
    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            x = ((double)i / numCols -0.5) * 2;
            y = ((double)j / numRows -0.5) * 2;

            color = mandelbrot(x,y);

            pixels[i][j].rgbtBlue = color;
            pixels[i][j].rgbtGreen = color;
            pixels[i][j].rgbtRed = color;
        }
    }
							dummyMethod2();
    return pixels;
}

int main(int argc, char** argv) {
    if (argc != 2 && argc != 4) {
        fprintf(stderr, "Usage: %s filename [numRows numCols]\n", argv[0]);
        return 1;
    }

    if (argc > 2) {
        // don't use atoi() in production code, since it doesn't support any error handling
        numRows = atoi(argv[2]);
        numCols = atoi(argv[3]);
    }

    return save_image(argv[1], create_image());
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