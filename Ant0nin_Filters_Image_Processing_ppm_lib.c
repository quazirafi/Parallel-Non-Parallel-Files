#include <stdio.h>
#include <stdlib.h>
#include "ppm_lib.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Adapted from RPFELGUEIRAS */

#define CREATOR "PARALLELISME2OPENMP"

PPMImage* clonePPM(PPMImage *image) {

	PPMImage *clone = (PPMImage *)malloc(sizeof(PPMImage));
	clone->w = image->w;
	clone->h = image->h;

	int totalSize = clone->w*clone->h;
	clone->data = (PPMPixel*)malloc(sizeof(PPMPixel)*totalSize);

	int i;
dummyMethod1();
	#pragma omp parallel for shared(image)
	for (i = 0; i < totalSize; i++)
		clone->data[i] = image->data[i];

	return clone;
dummyMethod2();
}

void freePPM(PPMImage *image) {
	free(image->data);
	free(image);
}

PPMImage *importPPM(const char *imageName)
{
         char buff[16];
         PPMImage *img;
         FILE *fp;
         int c, rgb_comp_color;

		 char filename[64] = PPM_IMAGES_FOLDER_PATH;
		 strcat(filename, imageName);
		 strcat(filename, PPM_IMAGES_FILE_EXTEND);

         //open PPM file for reading
         fp = fopen(filename, "rb");
         if (!fp) {
              fprintf(stderr, "Unable to open file '%s'\n", filename);
              exit(1);
         }

         //read image format
         if (!fgets(buff, sizeof(buff), fp)) {
              perror(filename);
              exit(1);
         }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    //alloc memory form image
    img = (PPMImage *)malloc(sizeof(PPMImage));
    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }

    ungetc(c, fp);
    //read image size information
    if (fscanf(fp, "%d %d", &img->w, &img->h) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    img->data = (PPMPixel*)malloc(img->w * img->h * sizeof(PPMPixel));

    if (!img) {
         fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    //read pixel data from file
    if (fread(img->data, sizeof(PPMPixel)*img->w, img->h, fp) != img->h) {
         fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    fclose(fp);
    return img;
}

void exportPPM(const char *imageName, PPMImage *img)
{
	char filename[64] = PPM_IMAGES_FOLDER_PATH;
	strcat(filename, imageName);
	strcat(filename, PPM_IMAGES_FILE_EXTEND);

    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //write the header file
    //image format
    fprintf(fp, "P6\n");

    //comments
    fprintf(fp, "# Created by %s\n",CREATOR);

    //image size
    fprintf(fp, "%d %d\n",img->w,img->h);

    // rgb component depth
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // pixel data
    fwrite(img->data, 3 * img->w, img->h, fp);
    fclose(fp);
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