#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "omp.h"
#include <xmmintrin.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double gettime(void)
{
	struct timeval ttime;
	gettimeofday(&ttime , NULL);
	return ttime.tv_sec + ttime.tv_usec * 0.000001;
}

int main(int argc, char ** argv)
{
	double timeTotal = 0.0f;
	double time0=gettime();
	
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int l = atoi(argv[3]);
	int threads = atoi(argv[4]);

	unsigned long long checksum = 0; 
	
	srand(0);
	
	
	if(m==1) //the same as fine-grained code (project_3_omp_fg.c)
	{
		int mset[m][l];
		int nset[n][l];
			dummyMethod3();
		for(int ki=0; ki<m; ki++){
			for(int kj=0; kj<l; kj++){
				mset[ki][kj] = (int)(rand()%2);
				nset[ki][kj] = (int)(rand()%2);
			}
		}
			dummyMethod4();

		unsigned long long ** mn = (unsigned long long**)malloc(sizeof(unsigned long long*)*m);
		assert(mn!=NULL);
		
			dummyMethod3();
		for(int i=0; i<m; i++){

			mn[i] = (unsigned long long*)malloc(sizeof(unsigned long long)*m);
		}
			dummyMethod4();
		
		omp_set_num_threads(threads);

		int y;

		unsigned long long d ;
		
		unsigned long long* partialDistVector = (unsigned long long*)malloc(sizeof(unsigned long long)*threads);
		assert(partialDistVector!=NULL);

			dummyMethod3();
		for(y=0;y<threads;y++){
			partialDistVector[y] = 0;
		}
			dummyMethod4();
	
		for(int i=0; i<m; i++){
		
			d = 0;
		
			for(int j=0; j<n; j++){
			
				d = 0; 
				
				int k=0;
				
							dummyMethod1();
				#pragma omp parallel for	
				for(k=0;k<l;k++){

						if(mset[i][k] != nset[j][k])
							partialDistVector[omp_get_thread_num()] += 1;
						else
							partialDistVector[omp_get_thread_num()] += 0;
					
					
				}
							dummyMethod2();
			
				for(y=0;y<threads;y++){
					d += partialDistVector[y]; //sum up all sums each thread has computed
					
					partialDistVector[y] = 0; //clean vectors threads use for the next step of the for loop
				}
				
				mn[i][j] = d; //write the sum of distances to the apropriate position in mn matrix (i.e. the comparison between mset[i] string and nset[j] string)
				
			}
			
		}
		
		//calculate the sum of Hamming distances stored in mn matrix
	
		omp_get_thread_num();
	
		int k;
		
		unsigned long long* partialSumVector = (unsigned long long*)malloc(sizeof(unsigned long long)*threads);
		assert(partialSumVector!=NULL);
	
		for(k=0;k<threads;k++){
			partialSumVector[k] = 0;
		}
	
		
		for(k=0;k<m;k++){
			
			int j;
			
					dummyMethod1();
			#pragma omp parallel for
			for(j=0; j<n; j++){
					
					partialSumVector[omp_get_thread_num()] += mn[k][j];
	
					}
					dummyMethod2();
			}
	
		for(k=0;k<threads;k++){
	
			checksum +=partialSumVector[k];
	
		}

	
		printf("Checksum is %lld\n", checksum);
		//free (mset);
		//free (nset);
		free (mn);
		free(partialSumVector);
		free(partialDistVector);
	}
		
	else {
		/*-------------memory allocation for m,n sets (64-byte aligned)--------------*/
		int ** mset = (int**)_mm_malloc(sizeof(int*)*(m+m%16),64);
		//int ** mset = (int**)malloc(sizeof(int*)*m);
		assert(mset!=NULL);
		
		int ** nset = (int**)_mm_malloc(sizeof(int*)*(m+m%16),64);
		//int ** nset = (int**)malloc(sizeof(int*)*m);
		assert(nset!=NULL);
		
		for(int ki=0; ki<m; ki++){
			//allocate memory for each string
			mset[ki] = (int*)_mm_malloc(sizeof(int)*(l+l%16),64);
			nset[ki] = (int*)_mm_malloc(sizeof(int)*(l+l%16),64);
	
			
			for(int kj=0; kj<l; kj++){
				//initialize each site of a string with random values (0 or 1)
				mset[ki][kj] = (int)(rand()%2);
				nset[ki][kj] = (int)(rand()%2);
				
			}
		}
		
		
		/*------memory allocation for a m*n matrix so as to store Hamming distances from string comparison (64-byte aligned)------*/
		
		unsigned long long ** mn = (unsigned long long**)_mm_malloc(sizeof(unsigned long long*)*(m+m%8),64);
		//unsigned long long ** mn = (unsigned long long**)malloc(sizeof(unsigned long long*)*m);
		assert(mn!=NULL);
		
		for(int i=0; i<m; i++){
	
			mn[i] = (unsigned long long*)_mm_malloc(sizeof(unsigned long long)*(m+m%8),64); 
		}
	
		
		int u_f1 = 64/sizeof(int); //step to read and compare each site of a string in mset and nset, so as each thread reads elements that fit in one cache line
						//(mset & nset elements are of type int, so 16 of them fit in one cache line (64 bytes long))
		
		int u_f2 = 64/sizeof(unsigned long long); //step to read and compute the sum of elements in mn matrix, so as each thread reads elements that fit in one cache line
						//(mn elements are of type unsigned long long, so 8 of them fit in one cache line (64 bytes long))
		
		
		/*-----------pairwise string comparison to compute Hamming distance and write it to mn matrix---------*/
		
		omp_set_num_threads(threads);
		
		
		unsigned long long* partialDistVector = (unsigned long long*)malloc(sizeof(unsigned long long)*threads);
		assert(partialDistVector!=NULL);
		
		int * thread_counter = (int*)malloc(sizeof(int)*threads);
		assert(thread_counter!=NULL);
		
		int y;
		
		unsigned long long d ;
		
		for(y=0;y<threads;y++){
				partialDistVector[y] = 0;
			}
		
		for(int i=0; i<m; i++){
			
			d = 0;
			
			for(int j=0; j<n; j++){
				
				d = 0; 
				
				//int kk=0; //a counter of k to use its index for the leftovers
				for(y=0;y<threads;y++){
					thread_counter[y] = 0;
				}
				
				int k=0;
				
				/*---------read data by blocks of 64 bytes (i.e. length of the cache line)--------*/
				
							dummyMethod1();
				#pragma omp parallel for
				for(k=0;k<(l/u_f1);k++){
	
					thread_counter[omp_get_thread_num()]+=1;
					
					
					for(int x=k*u_f1; x<(k+1)*u_f1; x++){
						__builtin_assume_aligned(mset, 64); //a clause for dynamically allocated arrays, informs the compiler that pointer mset is aligned at 64 bytes (https://software.intel.com/en-us/articles/data-alignment-to-assist-vectorization)
						__builtin_assume_aligned(nset, 64);
						
						if(mset[i][x] != nset[j][x])
							partialDistVector[omp_get_thread_num()] += 1;
						else
							partialDistVector[omp_get_thread_num()] += 0;
					}
					
				}
							dummyMethod2();
				
				for(y=0;y<threads;y++){
					d += partialDistVector[y]; //sum up all sums each thread has computed
					
					partialDistVector[y] = 0; //clean vectors threads use for the next step of the for loop
				}
				if(d>l) //check if sth goes wrong with the sum of distances
					printf("d=%lld for i=%d j=%d and k=%d\n", d,i,j,k);
				int c = 0;
				for(y=0;y<threads;y++){
					c += thread_counter[y];
					thread_counter[y] = 0;
				}
				//a for loop for the leftovers (equal to l%u_f1) or for l=10
			
				for(k=c*u_f1;k<l; k++){
					__builtin_assume_aligned(mset, 64);
					__builtin_assume_aligned(nset, 64);
					
					//printf("I'm in the parallel loop\n");
					//printf("j=%d k=%d\n",j,k);
	
					if(mset[i][k] != nset[j][k])
						d += 1;
					else
						d += 0;				
				}
			
				mn[i][j] = d; //write the sum of distances to the apropriate position in mn matrix (i.e. the comparison between mset[i] string and nset[j] string)
				
			}
			
		}
		
		//calculate the sum of Hamming distances stored in mn matrix
	
		omp_get_thread_num();
	
		int k;
		
		unsigned long long* partialSumVector = (unsigned long long*)malloc(sizeof(unsigned long long)*threads);
		assert(partialSumVector!=NULL);
		
		
	
		for(k=0;k<threads;k++){
			partialSumVector[k] = 0;
			thread_counter[k] = 0;
		}
	
		
		for(k=0;k<m;k++){
			
			int j;
			
			//int jj=0; // a counter for j to use it for the leftovers
			
					dummyMethod1();
			#pragma omp parallel for
			for(j=0; j<n/u_f2; j++){
				
				//jj+=1;
				thread_counter[omp_get_thread_num()] += 1;
									
					for(int x=j*u_f2; x<(j+1)*u_f2; x++){
						__builtin_assume_aligned(mn, 64);
						//unsigned long long a = partialSumVector[omp_get_thread_num()];
						partialSumVector[omp_get_thread_num()] += mn[k][x];
						//a += mn[k][x];
						//printf("partial sum vector= %lld, thread=%d\n", partialSumVector[omp_get_thread_num()], omp_get_thread_num() );
	
					}
					
			}
					dummyMethod2();
			int c = 0;
			
			for(int z=0;z<threads;z++){
			
				c += thread_counter[z];
				thread_counter[z] = 0;
			}
			//a for loop for the leftovers
			for(j=(c)*u_f2;j<n;j++){
				//printf("I'm in the parallel loop\n");
				//printf("k=%d j=%d\n",k,j);
				__builtin_assume_aligned(mn, 64);
	
				checksum += mn[k][j];
	
			}
			//printf("checksum from parallel loop is %lld\n", checksum);
		}
		//printf("checksum before adding is %lld\n", checksum);
		for(k=0;k<threads;k++){
	
			checksum +=partialSumVector[k];
	
		}
	
		
		printf("Checksum is %lld\n", checksum);
		_mm_free (mset);
		_mm_free (nset);
		_mm_free (mn);
		free(partialSumVector);
		free(partialDistVector);
		free(thread_counter);
	
	}
	
	double time1=gettime();
	timeTotal += time1-time0;
	
	printf("Time %f\n", timeTotal);
	

	
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