#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_ITERATIONS 1000
#define WIDTH 1536
#define HEIGHT 1024
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 1536
#define NUM_JOBS 256

double When()
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

void fileWrite(int* pixels) {
	
	int i, j;
	FILE *fp;
	fp = fopen("test.pgm", "w");
	
	if (fp == NULL) {
		perror ( "Unable to open file" );
		exit (EXIT_FAILURE);
	}
	
	fprintf(fp,"P2\n");
	fprintf(fp,"%d %d\n",WIDTH,HEIGHT);
	fprintf(fp,"%d\n",MAX_ITERATIONS);
	
	
	dummyMethod3();
	for (j = 0; j < HEIGHT; j++) {
		for (i = 0; i < WIDTH; i++) {
			fprintf(fp,"%d ",pixels[i + j * WIDTH]);
		}
		fprintf(fp,"\n");
	}
	dummyMethod4();
	
	
	//fprintf(fp, "Testing...\n");
	
	fclose(fp);
}

int computePoint(int _x, int _y) {
	
	int iteration, color;
	double xtemp;
	double x0, y0, x, y;
		
	x0 = (((double)_x - 1024) / ((double)1024 / (double)2));
	y0 = (((double)_y - 512) / ((double)HEIGHT / (double)2));
	
	/*
	if ((_x == 0) && (_y == 1023)) {
		fprintf(stderr,"X: %d, Y: %d, ScaledX: %lf, ScaledY: %lf\n",_x,_y,x0,y0);
	}
	if ((_x == 1023) && (_y == 1023)) {
		fprintf(stderr,"X: %d, Y: %d, ScaledX: %lf, ScaledY: %lf\n",_x,_y,x0,y0);
	}
	if ((_x == 1024) && (_y == 1023)) {
		fprintf(stderr,"X: %d, Y: %d, ScaledX: %lf, ScaledY: %lf\n",_x,_y,x0,y0);
	}
	if ((_x == 1535) && (_y == 1023)) {
		fprintf(stderr,"X: %d, Y: %d, ScaledX: %lf, ScaledY: %lf\n",_x,_y,x0,y0);
	}
	*/
	
	iteration = 0;
	x = 0;
	y = 0;
	
	while (((x*x + y*y) < 4) && (iteration < MAX_ITERATIONS)) //Remember: 4 == (2*2)
	{
		xtemp = x*x - y*y + x0;
		y = 2*x*y + y0;
		
		x = xtemp;
		
		iteration++;
	}
	
	color = MAX_ITERATIONS - iteration;
	return color;
	
}



int main(int argc, char** argv) {

	// mandelbrot
	int* pixels;
	int i, j;
	int color;
	
	// mpi
	int nproc, iproc;
	int* mySendArr;
	int* myRecvArr;
	MPI_Status status;
	
	// miscellaneous
	int loop; // used as boolean
	int loopCount;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &iproc);
	
	// everyone needs a send and a recv array
	// the extra 1 is for the start location
	mySendArr = (int*)malloc((BLOCK_WIDTH * BLOCK_HEIGHT + 1) * sizeof(int));
	myRecvArr = (int*)malloc((BLOCK_WIDTH * BLOCK_HEIGHT + 1) * sizeof(int));
	
	
	if (iproc == 0) {	// master code
		int numJobs;
		int jobCount;
		int jobStart;
		double timestart, timefinish, timetaken;
		
		numJobs = NUM_JOBS;
		jobCount = 0;
		
		//fprintf(stderr,"(%d) I'm the master\n",iproc);
		pixels = (int*)malloc(WIDTH * HEIGHT * sizeof(int));
		
		timestart = When();
		
	/*
		for (j = 0; j < HEIGHT; j++) {
			for (i = 0; i < WIDTH; i++) {
				pixels[i + j * WIDTH] = computePoint(i, j);
			}
		}
	*/	
		//loop = 1;
			dummyMethod3();
		for (loopCount = 0; loopCount < (NUM_JOBS * 2 + nproc - 1); loopCount++) {
			//fprintf(stderr,"(%d) I'm waiting\n",iproc);
			
			MPI_Recv(myRecvArr,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
		//	fprintf(stderr,"(%d) %d sent me a message: %lf\n",iproc,status.MPI_SOURCE,myRecvArr[0]);
			
			if (myRecvArr[0] == -1) {	// worker wants more work
				//fprintf(stderr,"(%d) %d wants more work\n",iproc,status.MPI_SOURCE);
				
				if (numJobs > 0) {
					// tell worker there is a job starting at numJobs - 1 * BLOCK_WIDTH
					mySendArr[0] = jobCount * BLOCK_WIDTH;
					jobCount++;
					MPI_Send(mySendArr,1,MPI_INT,status.MPI_SOURCE,0,MPI_COMM_WORLD);
					numJobs--;
				}
				else {
					// tell worker there isn't any more
					mySendArr[0] = -1;
					MPI_Send(mySendArr,1,MPI_INT,status.MPI_SOURCE,0,MPI_COMM_WORLD);
				}
				
				
			}
			else if (myRecvArr[0] == -2) {	// worker wants to send finished work
				//fprintf(stderr,"(%d) %d wants to send me their work\n",iproc,status.MPI_SOURCE);
			
				MPI_Recv(myRecvArr,BLOCK_WIDTH * BLOCK_HEIGHT + 1,MPI_INT,status.MPI_SOURCE,0,MPI_COMM_WORLD,&status);
				
				// worker sent work with start number
				//fprintf(stderr,"(%d) %d sent me their work starting at %d\n",iproc,status.MPI_SOURCE,myRecvArr[0]);
				
				// copy work into pixel array
				jobStart = myRecvArr[0];
				for (i = 1; i < BLOCK_WIDTH * BLOCK_HEIGHT + 1; i++) {
					pixels[i-1 + jobStart] = myRecvArr[i];
					//fprintf(stderr,"%d ",pixels[i-1 + jobStart]);
				}
			}

			
			//loop = 0;
		}
			dummyMethod4();
		
		
		timefinish = When();
		timetaken = timefinish - timestart;
		//fprintf(stderr,"(%d) I'm finished\n",iproc);
		fprintf(stdout,"(%d) Time taken: %lf\n",iproc,timetaken);
	
		fileWrite(pixels);
		free(pixels);
	
	
	}
	else {	// worker code
		int myJobStart;
		//fprintf(stderr,"\t(%d) I'm a worker\n",iproc);
		pixels = (int*)malloc(BLOCK_WIDTH * BLOCK_HEIGHT * sizeof(int));
		
		loop = 1;
		while (loop) {
			// ask master for work
			mySendArr[0] = -1;
			MPI_Send(mySendArr,1,MPI_INT,0,0,MPI_COMM_WORLD);
			
			// recv response (starting number or -1)
			MPI_Recv(myRecvArr,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
			
			if (myRecvArr[0] == -1) {	// -1 means no more
				//fprintf(stderr,"\t(%d) Master says no more work\n",iproc);
				loop = 0;
				
			}
			else {
				//fprintf(stderr,"\t(%d) Master gave me start of %d\n",iproc,myRecvArr[0]);
				myJobStart = myRecvArr[0];
				
				
				// do work
							dummyMethod1();
				#pragma omp parallel for private(i, j)
				for (j = 0; j < BLOCK_HEIGHT; j++) {
					for (i = 0; i < BLOCK_WIDTH; i++) {
						pixels[i + j * BLOCK_WIDTH] = computePoint(i, j + myJobStart / 1536);
						//fprintf(stderr,"%d ",pixels[i + j * BLOCK_WIDTH]);
					}
				}
							dummyMethod2();
				
				
				// tell master work is done and ready to send
				mySendArr[0] = -2;
				MPI_Send(mySendArr,1,MPI_INT,0,0,MPI_COMM_WORLD);
				
				// send work
				mySendArr[0] = myJobStart;
							dummyMethod3();
				for (i = 1; i < BLOCK_WIDTH * BLOCK_HEIGHT + 1; i++) {
					mySendArr[i] = pixels[i-1];
				}
							dummyMethod4();
				
				MPI_Send(mySendArr,BLOCK_WIDTH * BLOCK_HEIGHT + 1,MPI_INT,0,0,MPI_COMM_WORLD);
				
			}

			
		}
		
		
		//fprintf(stderr,"\t(%d) I'm finished\n",iproc);
		
	}

	
	
	MPI_Finalize();
	
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