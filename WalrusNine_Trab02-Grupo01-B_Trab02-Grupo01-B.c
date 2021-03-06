/*
**	Disciplina:	SSC-0143 Programacao Concorrente
**
**	Docente:	Prof. Julio Cezar Estrella
**
**	Discentes:	Andre Miguel Coelho Leite	8626249
**			Laerte Vidal Junior		7557800
**
**	Trabalho 2:	Smooth com/sem threads
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
#include "mpi.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define RGB 0
#define RBG 1
#define GRB 2
#define GBR 3
#define BRG 4 
#define BGR 5

/*
**	Image is stored in an array of PIXELs,
**	which have red, green and blue values
**	as unsigned chars (RGB) or just one
**	unsigned char(GRS).
**
**
**	SMOOTH
**	5x5
**	(i-2,j-2)	(i-1,j-2)	(i  ,j-2)	(i+1,j-2)	(i+2,j-2)
**	(i-2,j-1)	(i-1,j-1)	(i  ,j-1)	(i+1,j-1)	(i+2,j-1)
**	(i-2,  j)	(i-1,  j)	(i  ,  j)	(i+1,  j)	(i+2,  j)
**	(i-2,j+1)	(i-1,j+1)	(i  ,j+1)	(i+1,j+1)	(i+2,j+1)
**	(i-2,j+2)	(i-1,j+2)	(i  ,j+2)	(i+1,j+2)	(i+2,j+2)
*/

/* RGB PIXEL */
typedef struct{
	unsigned char r, g, b;
}PIXELRGB;

/* GRAYSCALE PIXEL */
typedef struct{
	unsigned char i;
}PIXELGRS;

/* UNION for keeping either grayscale or rgb PIXEL */
typedef union{
	PIXELGRS grs;
	PIXELRGB rgb;
} PIXEL;

typedef struct image{
	PIXEL* pixel;
	int width, height;
}IMAGE;

/* Prototypes */
IMAGE* read_ppm_image();
void write_ppm(const char *,IMAGE*,int);
void delete_image(IMAGE**);

MPI_Datatype create_mpi_struct_datatype();

void smooth_grs(PIXEL*,int, int, int);
void smooth_rgb(PIXEL*,int, int, int);

int timeval_subtract(struct timeval*, struct timeval*, struct timeval*);

/* Globals */
int grayscale = 0;

int main(int argc, char** argv)
{
	MPI_Datatype stype;
	
	int	rank, numtasks;
	int	lines_per_proc, total_size, lines, width;
	IMAGE* 	image;
	PIXEL*	gpixels;

	/* Time variables */
	struct timeval t_begin, t_end, t_diff;
	
	/* Initialize MPI */
	int rc = MPI_Init(&argc,&argv);
	if (rc != MPI_SUCCESS){
		return EXIT_FAILURE;
	}
	
	/* Get number of processess and rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	/* Create datatype for pixel */
	stype = create_mpi_struct_datatype();
	
	/*
	**	In root, read and create image.
	**	Also, initialize variables that will be used
	**	across all processess.
	*/
	if (rank == 0){
		image 		= read_ppm_image();
		total_size 	= image->width*image->height;
		lines 		= image->height;
		
		/* Each process will have n number of lines to process (0 - n*width...) */
		lines_per_proc 	= lines/numtasks;
		width 		= image->width;
		
		/* Save copy of pixels address for other processess */
		gpixels = image->pixel;

		/* Get time start */
		gettimeofday(&t_begin, NULL);
	}
	
	/* Broadcast variables needed in all processess */
	MPI_Bcast(&lines_per_proc, 	1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&width,		1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&total_size, 		1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&gpixels, 		1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&grayscale, 		1, MPI_INT, 0, MPI_COMM_WORLD);

	/* Each process creates an array of pixels for them */
	PIXEL* pa;
	pa = malloc(lines_per_proc*width*sizeof(PIXEL));
	
	/*
	**	Scatter - give each process a part of pixels array
	**	From gpixels, with lines_per_proc*width variables of type stype.
	**	To pa, with same legth and type.
	**	From root.
	*/
	MPI_Scatter(gpixels, lines_per_proc*width, stype, pa, lines_per_proc*width, stype, 0, MPI_COMM_WORLD);
	
	/* Run smooth */
	if (grayscale) smooth_grs(pa, 2, width, lines_per_proc);
	else smooth_rgb(pa, 2, width, lines_per_proc);

	/*
	**	Gather - each process gives back what it did.
	**	From pa, with lines_per_proc*width variables of type stype.
	**	To gpixels, with same legth and type.
	**	To root.
	*/
	MPI_Gather(pa, lines_per_proc*width, stype, gpixels, lines_per_proc*width, stype, 0, MPI_COMM_WORLD);
	
	/*
	**	Root runs smooth on the rest;
	**	Writes image to file;
	**	Free memory.
	*/
	if (rank == 0){
		if (lines%numtasks != 0){
			/* Work on rest */
			int rest 	= lines%numtasks;
			PIXEL* pm 	= image->pixel + (lines - rest)*width;
			
			if (grayscale) smooth_grs(pm, 2, width, rest);
			else smooth_rgb(pm, 2, width, rest);
		}

		/* Get time end */
		gettimeofday(&t_end, NULL);

		/* Get diff time and print in stderr */
		timeval_subtract(&t_diff, &t_end, &t_begin);
		fprintf(stderr, "%ld.%06ld\n", t_diff.tv_sec, t_diff.tv_usec);

		/* Write resulting image */
		write_ppm("out.ppm",image,RGB);
		
		delete_image(&image);
	}
	/* Each process cleans up "pa" */
	free(pa);
	
	/* Finalize, clearing up created type */
	MPI_Type_free(&stype);
	MPI_Finalize();
	
	return EXIT_SUCCESS;
}

MPI_Datatype create_mpi_struct_datatype()
{
	MPI_Datatype new_type;
	
	/*
	**	New type will be either an unsigned char(grayscale)
	**	or 3 consecutive unsigned chars(rgb)
	*/
	
	if (grayscale)		/* 1 unsigned char */
		MPI_Type_contiguous(1, MPI_UNSIGNED_CHAR, &new_type);
	else				/* 3 unsigned chars */
		MPI_Type_contiguous(3, MPI_UNSIGNED_CHAR, &new_type);
	
	/* Save new type */
	MPI_Type_commit(&new_type);
	
	return new_type;
}



IMAGE* read_ppm_image()
{
	/*
	**	Snippet adapted from:
	**	http://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
	*/
	
	FILE* fp = fopen("in.ppm", "rb");
	
	/*
	**	PX
	**	n_columns m_rows
	**	max_color
	**	row_1 -> column_1  ...  column_n
	**	...
	**	row_n -> column_1  ...  column_n
	**
	**	each row is in format (255 255 255) => (R G B)
	*/

	/* Get Type PPM */
	char type[3];
	fscanf(fp, "%s\n", type);
	if (type[1] == '5') grayscale = 1;
	
	/* Check for comments */
	char c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n');
		c = getc(fp);
	}
	ungetc(c, fp);

	/* Get Size */
	int width, height;
	fscanf(fp, "%d %d\n", &width, &height);

	/* Get Max Color */
	fscanf(fp, "%*d\n");

	/* Create Image */
	IMAGE* image 	= malloc(sizeof(IMAGE));
	image->width 	= width;
	image->height 	= height;
	image->pixel 	= (PIXEL *)malloc(width*height*sizeof(PIXEL));

	/* Read image's pixel data */
	if (grayscale){
		int i, j;
			dummyMethod3();
		for (i = 0; i < height; ++i){
			for (j = 0; j < width; ++j){
				fread(&(image->pixel[i*width + j].grs.i), 1, 1, fp);
			}
		}
			dummyMethod4();
	}
	else fread(image->pixel, sizeof(PIXEL),width*height, fp);

	fclose(fp);

	return image;
}

void smooth_rgb(PIXEL* pixel,int n, int width, int height){
	PIXEL* pixels = calloc(width*height, sizeof(PIXEL));
	PIXEL *p;
	int red,gre,blu;

	int i,j,k,l;
	
	#pragma omp parallel private(i, j, k, l, p, red, gre, blu) shared(pixel, pixels)
	dummyMethod1();
	#pragma omp parallel for
	for (j = 0; j < height; j++){
		for (i = 0; i < width; i++){
			red =gre = blu=0;
			for (k = -n; k <= n; k++){
				for (l = -n; l <= n; l++){
					if (i+k >= 0 && i+k < width && j+l >= 0 && j+l < height){
						p = &pixel[(j+l)*width + (i+k)];
						red += p->rgb.r;
						gre += p->rgb.g;
						blu += p->rgb.b;
					}
				}
			}
			p = &pixels[(j)*width + (i)];
			p->rgb.r = (red / ((2*n+1)*(2*n+1)));
			p->rgb.g = (gre / ((2*n+1)*(2*n+1)));
			p->rgb.b = (blu / ((2*n+1)*(2*n+1)));
		}
	}
	dummyMethod2();

	dummyMethod3();
	for (j = 0; j < height; ++j){
		for (i = 0; i < width; ++i){
			pixel[j*width + i].rgb.r = pixels[j*width + i].rgb.r;
			pixel[j*width + i].rgb.g = pixels[j*width + i].rgb.g;
			pixel[j*width + i].rgb.b = pixels[j*width + i].rgb.b;
		}
	}
	dummyMethod4();
	
	free(pixels);
}

void smooth_grs(PIXEL* pixel,int n, int width, int height){
	PIXEL* pixels = calloc(width*height, sizeof(PIXEL));
	PIXEL *p;
	int mean;

	int i,j,k,l;
	
	#pragma omp parallel private(i, j, k, l, p, mean) shared(pixel, pixels)
	dummyMethod1();
	#pragma omp parallel for
	for (j = 0; j < height; j++){
		for (i = 0; i < width; i++){
			mean = 0;
			for (k = -n; k <= n; k++){
				for (l = -n; l <= n; l++){
					if (i+k >= 0 && i+k < width && j+l >= 0 && j+l < height){
						p = &pixel[(j+l)*width + (i+k)];
						mean += p->grs.i;
					}
				}
			}
			p = &pixels[(j)*width + (i)];
			p->grs.i = (mean / ((2*n+1)*(2*n+1)));
		}
	}
	dummyMethod2();

	dummyMethod3();
	for (j = 0; j < height; ++j){
		for (i = 0; i < width; ++i){
			pixel[j*width + i].grs.i = pixels[j*width + i].grs.i;
		}
	}
	dummyMethod4();
	
	free(pixels);
}

void write_ppm(const char *fname,IMAGE* image,int m){
	FILE *fp = fopen(fname, "wb");
	
	/* Put header */
	if (grayscale) fprintf(fp, "P5\n");
	else fprintf(fp, "P6\n");

	/* Put size */
	fprintf(fp, "%d %d\n",image->width, image->height);
	int width = image->width, height = image->height;

	/* RGB component depth */
	fprintf(fp, "%d\n", 255);

	/* Pixel data */
	int i, j;
	dummyMethod3();
	for (j = 0; j < image->height; j++){
		for (i = 0; i < image->width; i++){
			if (grayscale){
				fwrite(&(((image->pixel)[j*image->width + i]).grs.i), sizeof(unsigned char),1, fp);
			} else{
				fwrite(&(image->pixel[j*width + i].rgb.r), sizeof(unsigned char),1, fp);
				fwrite(&(image->pixel[j*width + i].rgb.g), sizeof(unsigned char),1, fp);
				fwrite(&(image->pixel[j*width + i].rgb.b), sizeof(unsigned char),1, fp);
			}
		}
	}
	dummyMethod4();
	
	fclose(fp);
}

void delete_image(IMAGE** image){
	if (*image != NULL){
		free((*image)->pixel);
		free(*image);
		*image = NULL;
	}
}


/*
**	Snippet from:
**	http://stackoverflow.com/questions/1468596/calculating-elapsed-time-in-a-c-program-in-milliseconds
*/

/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
	long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
	result->tv_sec = diff / 1000000;
	result->tv_usec = diff % 1000000;

	return (diff<0);
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