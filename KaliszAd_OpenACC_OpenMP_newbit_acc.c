#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define ASCENDING 1
#define DESCENDING 0

struct timespec startwtime, endwtime;
double seq_time;

int *genArray;
int arraySize;
int power = 0;

void generator(int size);
void printArray(int size);
char verify(int size);
void getPower(int size);

int main(int argc, char *argv[]){
	
	clock_gettime(CLOCK_REALTIME,&startwtime);
	srand((unsigned int)startwtime.tv_nsec);

	printf("The array size you want (integer): \n");
	scanf("%d", &arraySize);
	if(arraySize == 0){
		printf("Really, type in an integer larger 0...\n");
    	scanf("%d", &arraySize);
	}
    
	genArray = malloc(arraySize*sizeof(int));
	generator(arraySize);
	//printArray(arraySize);	
	
	clock_gettime(CLOCK_REALTIME,&startwtime);
	
	getPower(arraySize);
	
	if(power != 0){
	#pragma acc data copy(genArray[0:arraySize])
	for (int k = 2; k <= arraySize; k *= 2) //Parallel bitonic sort 
	{ 
		for (int j = k / 2; j>0; j /= 2) //Bitonic merge 
		{
			int cnt = arraySize;
			// because http://techenablement.com/pragma-puzzler-ambiguous-loop-trip-count-in-openmp-and-openacc/
					dummyMethod1();
			#pragma omp parallel for
			#pragma acc kernels loop independent present(genArray[0:arraySize])
			for (int threadid = 0; threadid < cnt; ++threadid)
			{	
				//#pragma acc atomic capture
				{
				int index = threadid ^ j; //XOR 
				if (index > threadid)     // segment of the array; is threadid < j? 
				{
					if ((threadid & k) == 0) // ascending – descending 
					{ 
						//#pragma acc atomic update 
						if (genArray[threadid] > genArray[index])
						{ 
							int t;
							t = genArray[threadid];
							genArray[threadid] = genArray[index];
							genArray[index] = t;
						}
					} 
					else 
					{ 
						//#pragma acc atomic update
						if (genArray[threadid] < genArray[index]) 
						{
							int t;
							t = genArray[threadid];
							genArray[threadid] = genArray[index];
							genArray[index] = t;	
						}
					}
				}
				}
			}
					dummyMethod2();
		}
	}
	}	

	clock_gettime(CLOCK_REALTIME,&endwtime);
	seq_time = (double)((endwtime.tv_nsec - startwtime.tv_nsec)/1.0e9
							      + endwtime.tv_sec - startwtime.tv_sec);

	//printArray(arraySize);
	if(verify(arraySize) == 1){

		printf("The array is verified to be sorted!\n"
				"It sorted in %f s\n", seq_time);
	} else{
		printf("Something went wrong, because the array isn't sorted!\n"
				"It still took %f s\n to complete", seq_time);
	}
	
	free(genArray);
	return 0;
}

// HELPER FUNCTIONS

void getPower(int size){
	int i;

	for(i=1; i<arraySize; i*=2){
		power += 1;
	}
}

void generator(int size){
    int i;

	for(i = 0; i < size; i++){
		genArray[i] = (int) rand() % 3571;
	}
}

/* Function to print an array */
void printArray(int size){
    int i;
    for (i=0; i < size; i++){
		if(i % 10 == 0)
    	printf("\n");
	    printf("%d\t", genArray[i]);
	}
}

char verify(int size){
	int i;
	for(i = 1; i < size; i++){
		if(genArray[i - 1] <= genArray[i]){
		} else {return 0;}
	}
	return 1;
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