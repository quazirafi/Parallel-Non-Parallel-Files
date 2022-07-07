//
//  convolution.c
//
//
//  Created by Josep Lluis Lerida on 11/03/15.
//  Updated by Vitor da Silva on 17/04/2021
//
// This program allows you to apply the convolution to an image file with a * .ppm extension.
// The program receives the file with the source image, the file with the kernel for the convolution and the path of the output file.
// The 2D matrix of the image is represented by a 1D vector for each R, G and B channel. The convolution is applied for each channel separately.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <mpi.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Structure for storing the content of an image.
struct imagenppm{
    int height;
    int width;
    char *comment;
    int maxcolor;
    int P;
    int *R;
    int *G;
    int *B;
};
typedef struct imagenppm* ImagenData;

// Structure for storing the contents of a kernel.
struct structkernel{
    int kernelX;
    int kernelY;
    float *vkern;
};
typedef struct structkernel* kernelData;

// Definition of the main functions: reading an image, duplicating the image, reading the kernel, convolution, saving an image in PPM format, etc.
ImagenData readImage(char* name);
kernelData readKernel(char* name);
ImagenData duplicateImageData(ImagenData src);
int convolve2D(int*, int*, int, int, float*, int, int);
int saveFile(ImagenData Img, char* name);

// This Function allows us to read a ppm file and place the information: encoding, size, RGB, etc. of the image in a structure.
// The value of each RGB pixel in the 2D image is saved and represented by 1D vectors for each channel.
ImagenData  readImage(char* name){
    FILE *fp;
    char c;
    char comment[300];
    int i=0;
    ImagenData Img=NULL;

    // The ppm file is opened
    fp=fopen(name,"r");
    if(!fp){
        perror("Error");
    }
    else{
        // We reserve memory for the Image structure
        Img=(ImagenData) malloc(sizeof(struct imagenppm));

        //The magic number is read and saved
        fscanf(fp,"%c%d ",&c,&(Img->P));
        // The comment is read and saved character by character
        while((c=fgetc(fp))!= '\n'){comment[i]=c;i++;}
        Img->comment = calloc(strlen(comment),sizeof(char));
        strcpy(Img->comment,comment);
        // Read and save the width, height and maximum color
        fscanf(fp,"%d %d %d",&Img->width,&Img->height,&Img->maxcolor);
        // Memory is reserved in R, G and B according to width and height
        // And the values of R, G and B of the file are assigned
        if ((Img->R=calloc(Img->width*Img->height,sizeof(int))) == NULL) {return NULL;}
        if ((Img->G=calloc(Img->width*Img->height,sizeof(int))) == NULL) {return NULL;}
        if ((Img->B=calloc(Img->width*Img->height,sizeof(int))) == NULL) {return NULL;}
															dummyMethod3();
        for(i=0;i<Img->width*Img->height;i++){
            fscanf(fp,"%d %d %d ",&Img->R[i],&Img->G[i],&Img->B[i]);
        }
															dummyMethod4();
        fclose(fp);
    }
    return Img;
}

// This function allows us to read a kernel from a file, the kernel is represented by a 1D vector.
kernelData readKernel(char* name){
    FILE *fp;
    int i=0;
    kernelData kern=NULL;

    //Opening ppm file
    fp=fopen(name,"r");
    if(!fp){
        perror("Error: ");
    }
    else{
        //We reserve memory for the structure that the kernel will store
        kern=(kernelData) malloc(sizeof(struct structkernel));

        // We read the dimensions of the kernel.
        fscanf(fp,"%d,%d,", &kern->kernelX, &kern->kernelY);
        kern->vkern = (float *)malloc(kern->kernelX*kern->kernelY*sizeof(float));

        //kernel reading
															dummyMethod3();
        for (i=0;i<(kern->kernelX*kern->kernelY)-1;i++){
            fscanf(fp,"%f,",&kern->vkern[i]);
        }
															dummyMethod4();
        fscanf(fp,"%f",&kern->vkern[i]);
        fclose(fp);
    }
    return kern;
}

// This function allows you to copy the main data from the original image data structure into a second structure.
ImagenData duplicateImageData(ImagenData src){
    char c;
    char comment[300];
    unsigned int imageX, imageY;
    int i=0;
    // We reserve memory for the target Image structure
    ImagenData dst=(ImagenData) malloc(sizeof(struct imagenppm));
    //Magic number is copied
    dst->P=src->P;
    // Comment is copied
    dst->comment = calloc(strlen(src->comment),sizeof(char));
    strcpy(dst->comment,src->comment);
    // Width, height and maximum color are copied
    imageX=src->width;
    imageY=src->height;
    dst->width=imageX;
    dst->height=imageY;
    dst->maxcolor=src->maxcolor;
    // Memory is reserved in R, G and B according to width and height
    if ((dst->R=calloc(imageX*imageY,sizeof(int))) == NULL) {return NULL;}
    if ((dst->G=calloc(imageX*imageY,sizeof(int))) == NULL) {return NULL;}
    if ((dst->B=calloc(imageX*imageY,sizeof(int))) == NULL) {return NULL;}
    memcpy(dst->R, src->R, (imageX*imageY)*sizeof(int));
    memcpy(dst->G, src->G, (imageX*imageY)*sizeof(int));
    memcpy(dst->B, src->B, (imageX*imageY)*sizeof(int));
    return dst;
}

// This function stores the new Image data in a ppm file.
int saveFile(ImagenData  Img, char* name){
    int i,j;
    FILE *fp;
    // Resulting image is created
    if (!(fp=fopen(name,"w"))) {
        printf("Error opening the result file: %s\n",name);
        return -1;
    }
    //The magic number, comment, width, height and maximum color are written to the file
    fprintf(fp,"P%d\n%s\n%d %d\n%d\n",Img->P,Img->comment,Img->width,Img->height,Img->maxcolor);
    //Pixels are written
							dummyMethod3();
    for(i=0;i<Img->width*Img->height;i++){
            fprintf(fp,"%d %d %d ",Img->R[i],Img->G[i],Img->B[i]);
            if (i%Img->height==0) fprintf(fp,"\n");
    }
							dummyMethod4();
    fclose(fp);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// 2D convolution
// 2D data are usually stored in c
//uter memory as contiguous 1D array.
// So, we are using 1D array for 2D data.
// 2D convolution assumes the kernel is center originated, which means, if
// kernel size 3 then, k[-1], k[0], k[1]. The middle of index is always 0.
// The following programming logics are somewhat complicated because of using
// pointer indexing in order to minimize the number of multiplications.
//
//
// signed integer (32bit) version:
///////////////////////////////////////////////////////////////////////////////
int convolve2D(int* in, int* out, int dataSizeX, int dataSizeY,
                float* kernel, int kernelSizeX, int kernelSizeY)
{
    int i, j, m, n;
    int *inPtr, *inPtr2, *outPtr;
    float *kPtr;
    int kCenterX, kCenterY;
    int rowMin, rowMax;                             // to check boundary of input array
    int colMin, colMax;                             //
    float sum;                                      // temp accumulation buffer

    // check validity of params
    if(!in || !out || !kernel) return -1;
    if(dataSizeX <= 0 || kernelSizeX <= 0) return -1;

    // find center position of kernel (half of kernel size)
    kCenterX = (int)kernelSizeX / 2;
    kCenterY = (int)kernelSizeY / 2;

    // init working  pointers
    inPtr = inPtr2 = &in[dataSizeX * kCenterY + kCenterX];  // note that  it is shifted (kCenterX, kCenterY),
    outPtr = out;
    kPtr = kernel;

    // start convolution
															dummyMethod1();
    #pragma omp parallel for schedule(dynamic) shared(inPtr,inPtr2,outPtr,kPtr,kCenterX,kCenterY) private(i,j,m,n,rowMax,rowMin,colMin,colMax,sum) num_threads(4)
    
        //#pragma omp for schedule(dynamic) 
        for(i= 0; i < dataSizeY; ++i)                   // number of rows
        {
            // compute the range of convolution, the current row of kernel should be between these
            rowMax = i + kCenterY;
            rowMin = i - dataSizeY + kCenterY;
            for(j = 0; j < dataSizeX; ++j)              // number of columns
            {
                // compute the range of convolution, the current column of kernel should be between these
                colMax = j + kCenterX;
                colMin = j - dataSizeX + kCenterX;

                sum = 0;                                // set to 0 before accumulate

                // flip the kernel and traverse all the kernel values
                // multiply each kernel value with underlying input data
                for(m = 0; m < kernelSizeY; ++m)        // kernel rows
                {
                    // check if the index is out of bound of input array
                    if(m <= rowMax && m > rowMin)
                    {
                        for(n = 0; n < kernelSizeX; ++n)
                        {
                            // check the boundary of array
                            if(n <= colMax && n > colMin)
                                sum += *(inPtr - n) * *kPtr;

                            ++kPtr;                     // next kernel
                        }
                    }
                    else
                        kPtr += kernelSizeX;            // out of bound, move to next row of kernel

                    inPtr -= dataSizeX;                 // move input data 1 raw up
                }

                // convert integer number
                if(sum >= 0) *outPtr = (int)(sum + 0.5f);
                //else *outPtr = (int)(sum - 0.5f)*(-1);
                // For using with image editors like GIMP or others...
                else *outPtr = (int)(sum - 0.5f);
                // For using with a text editor that read ppm images like libreoffice or others...
                // else *outPtr = 0;

                kPtr = kernel;                          // reset kernel to (0,0)
                inPtr = ++inPtr2;                       // next input
                ++outPtr;                               // next output
            }
        }
															dummyMethod2();
        
    
        return 0;
    
}

int main(int argc, char **argv)
{
    int i=0,j=0,k=0;
    int imagesize, partitions, partsize, chunksize, halo, halosize;
    double start, tstart=0, tend=0, tread=0, tcopy=0, tconv=0, tstore=0, treadk=0;
    long position=0;
    int rank,nproc;

	MPI_Status status;

  	MPI_Request send_request, recv_request;
  	MPI_Init(&argc,&argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    struct timeval tim;
    ImagenData  source=NULL, output=NULL, output1=NULL , output2=NULL;
    //partitions = atoi(argv[4]);
    //partitions = 1; //vitor: I used this to test....
    gettimeofday(&tim, NULL);
    start = tim.tv_sec+(tim.tv_usec/1000000.0);
    start = tim.tv_sec+(tim.tv_usec/1000000.0);
    kernelData kern=NULL;

    if(argc != 5) //vitor: this verification must be done before any use of argv
    {
        printf("Usage: %s <image-file> <kernel-file> <result-file>\n", argv[0]);

        printf("\n\nError, missing parameters:\n");
        printf("format: image_file kernel_file result_file partition_number\n");
        printf("- image_file : source image path (*.ppm)\n");
        printf("- kernel_file: kernel path (text file with 1D kernel matrix)\n");
        printf("- result_file: result image path (*.ppm)\n");
        printf("- partition_number: number of partition (integer)\n\n"); //vitor change
        return -1;
    }

    partitions = atoi(argv[4]); //vitor change, put after the parameters verification

    if ( (kern = readKernel(argv[2]))==NULL) {
        free(source);
        free(output);
        return -1;
    }
    if (partitions==1) halo=0;
    else halo = (kern->kernelY/2)*2;
    gettimeofday(&tim, NULL);
    treadk = treadk + (tim.tv_sec+(tim.tv_usec/1000000.0) - start);

    //Read the source image.
    gettimeofday(&tim, NULL);
    start = tim.tv_sec+(tim.tv_usec/1000000.0);
    if ( (source=readImage(argv[1]))==NULL) {
        return -1;
    }

    gettimeofday(&tim, NULL);
    tread = tread + (tim.tv_sec+(tim.tv_usec/1000000.0) - start);

    // Duplicate the image in a new structure that will contain the output image
    gettimeofday(&tim, NULL);
    start = tim.tv_sec+(tim.tv_usec/1000000.0);
    if ( (output = duplicateImageData(source)) == NULL) {
        return -1;
    }
    gettimeofday(&tim, NULL);
    tcopy = tcopy + (tim.tv_sec+(tim.tv_usec/1000000.0) - start);

    // Image writing
     gettimeofday(&tim, NULL);
    start = tim.tv_sec+(tim.tv_usec/1000000.0);
    if (saveFile(output, argv[3])!=0) {
        printf("Error saving the image\n");
        free(source);
        free(output);
        return -1;
    }
     gettimeofday(&tim, NULL);
    tstore = tstore + (tim.tv_sec+(tim.tv_usec/1000000.0) - start);


    //master



	if (rank==0){
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // CHUNK READING
    //////////////////////////////////////////////////////////////////////////////////////////////////

	  gettimeofday(&tim, NULL);
	  start=tim.tv_sec+(tim.tv_usec/1000000.0);
	  tstart = start;

	 int c=0, offset=0;
	long chunksize1=0;
	int newOffset=0;
	int *BufferR=NULL, *BufferG=NULL, *BufferB=NULL;
	 int *BufferR1=NULL, *BufferG1=NULL, *BufferB1=NULL;
	newOffset=source->height/nproc;

	imagesize=source->height*source->width;
	chunksize1=(newOffset*source->width)/partitions;
	partsize  = (source->height*source->width)/partitions;

	BufferR=source->R;
	BufferG=source->G;
	BufferB=source->B;


	BufferR1=source->R;
        BufferG1=source->G;
        BufferB1=source->B;

    while (c < partitions) {
        ////////////////////////////////////////////////////////////////////////////////
        //Reading Next chunk.
        gettimeofday(&tim, NULL);
        start = tim.tv_sec+(tim.tv_usec/1000000.0);
        if (c==0) {
            halosize  = halo/2;
            chunksize = partsize + (source->width*halosize);
            offset   = 0;
        }
        else if(c<partitions-1) {
            halosize  = halo;
            chunksize = partsize + (source->width*halosize);
            offset    = (source->width*halo/2);

        }
        else {
            halosize  = halo/2;
            chunksize = partsize + (source->width*halosize);
            offset    = (source->width*halo/2);
        }


        gettimeofday(&tim, NULL);
        tread = tread + (tim.tv_sec+(tim.tv_usec/1000000.0) - start);


	int value=0;
	int i=1;



        BufferR=BufferR+chunksize1;
        BufferG=BufferG+chunksize1;
        BufferB=BufferB+chunksize1;

	dummyMethod3();
	for ( i; i<nproc; i++){
	MPI_Send(BufferR, chunksize1, MPI_INT, i, 1, MPI_COMM_WORLD);
	MPI_Send(BufferG, chunksize1, MPI_INT, i, 2, MPI_COMM_WORLD);
	MPI_Send(BufferB, chunksize1, MPI_INT, i, 3, MPI_COMM_WORLD);


        BufferR=BufferR+chunksize1;
        BufferG=BufferG+chunksize1;
        BufferB=BufferB+chunksize1;



	}
	dummyMethod4();


	  printf("ChunkSizeX : %d\n", source->width);
	  printf("ChunkSizeY : %d\n", newOffset);
          printf("kSizeX : %d\n", kern->kernelX);
          printf("kSizeY : %d\n", kern->kernelY);

/*#pragma omp parallel sections num_threads(4)
        {
    #pragma omp section 
                {
                    convolve2D(source->R, output->R, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);
                }
    #pragma omp section 
                {
                    convolve2D(source->G, output->G, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);
                    }
    #pragma omp section 
                {
                    convolve2D(source->B, output->B, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);
                }
        }*/

        convolve2D(source->R, output->R, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);
        convolve2D(source->G, output->G, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);
        convolve2D(source->B, output->B, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);

        gettimeofday(&tim, NULL);
        tconv = tconv + (tim.tv_sec+(tim.tv_usec/1000000.0) - start);

         printf("the master (%d) :took  %.6lf seconds elapsed for make the convolution.\n",rank, tconv);

	printf("----------------------------------------------------------\n");


	int endj=nproc;

	int j=1;

    	printf("Master Receiving from slaves\n");
	dummyMethod3();
	for (j; j<nproc; j++){
        	printf("receive from %d\n", j);
        	MPI_Recv(output->R+j*chunksize1, chunksize1, MPI_INT, j, 1,  MPI_COMM_WORLD, &status);
        	MPI_Recv(output->G+j*chunksize1, chunksize1, MPI_INT, j,2, MPI_COMM_WORLD, &status);
        	MPI_Recv(output->B+j*chunksize1, chunksize1, MPI_INT, j, 3, MPI_COMM_WORLD, &status);
	}
	dummyMethod4();

	c++;

	}


	gettimeofday(&tim, NULL);
        tend = tim.tv_sec+(tim.tv_usec/1000000.0);



	printf("the needed time of the Master : %.6lf\n", tend-tstart);

}
	if (rank!=0){


	int offset=0;
        int newOffset;
	long chunksize1;
        newOffset=source->height/nproc;
        chunksize1=(newOffset*source->width);


	output1=(ImagenData)malloc(sizeof(struct imagenppm));

	 output1->R=calloc(chunksize1,sizeof(int));
	 output1->G=calloc(chunksize1,sizeof(int));
	 output1->B=calloc(chunksize1,sizeof(int));

	output2=(ImagenData)malloc(sizeof(struct imagenppm));

         output2->R=calloc(chunksize1,sizeof(int));
         output2->G=calloc(chunksize1,sizeof(int));
         output2->B=calloc(chunksize1,sizeof(int));




	MPI_Recv(output1->R, chunksize1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
	MPI_Recv(output1->G, chunksize1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
	MPI_Recv(output1->B, chunksize1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);

        ///////////////////////////////////////////////////////////////

        // CHUNK CONVOLUTION
        //////////////////////////////////////////////////////////////////////////////////////////////////
        gettimeofday(&tim, NULL);
        start = tim.tv_sec+(tim.tv_usec/1000000.0);

	    convolve2D(source->R, output->R, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);
        convolve2D(source->G, output->G, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);
        convolve2D(source->B, output->B, source->width, source->height, kern->vkern, kern->kernelX, kern->kernelY);

        gettimeofday(&tim, NULL);
        tconv = tconv + (tim.tv_sec+(tim.tv_usec/1000000.0) - start);

	MPI_Send(output2->R, chunksize1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	MPI_Send(output2->G, chunksize1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	MPI_Send(output2->B, chunksize1, MPI_INT, 0, 3, MPI_COMM_WORLD);

    gettimeofday(&tim, NULL);
    tend = tim.tv_sec+(tim.tv_usec/1000000.0);
     printf("i am worker number %d and my cunk is  %d\n", rank, chunksize1);

    printf("worker(%d) : took  %.6lf seconds elapsed for make the convolution.\n", rank, tconv);


    printf("-------------------------------------------------------------\n");




	}

	MPI_Finalize();

	return 0;

}
//done
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