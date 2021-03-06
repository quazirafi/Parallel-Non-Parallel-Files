#include <stdio.h>
#include <immintrin.h>
#include "omp.h"
#include <time.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{ 
  //variable initialization...
  int iThreadCnt = 1, iLoopCntr = 1000*1000*1000;
  struct timeval start, end;
  float fTimeTaken = 0;
  int iCntr = 0;

  register __m256 vec1 = _mm256_setr_ps(4.0, 5.0, 13.0, 6.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec2 = _mm256_setr_ps(9.0, 3.0, 6.0, 7.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec3 = _mm256_setr_ps(1.0, 1.0, 1.0, 1.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec4 = _mm256_setr_ps(4.0, 5.0, 13.0, 6.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec5 = _mm256_setr_ps(9.0, 3.0, 6.0, 7.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec6 = _mm256_setr_ps(1.0, 1.0, 1.0, 1.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec7 = _mm256_setr_ps(4.0, 5.0, 13.0, 6.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec8 = _mm256_setr_ps(9.0, 3.0, 6.0, 7.0, 4.0, 5.0, 13.0, 6.0);
  register __m256 vec9 = _mm256_setr_ps(1.0, 2.0, 3.0, 4.0, 4.0, 5.0, 13.0, 6.0);

  //start timer..
  gettimeofday(&start, NULL);

  //Parallel block
			dummyMethod1();
  #pragma omp parallel for default(shared)	                
  for (iCntr=0; iCntr < iLoopCntr; iCntr++)
  {
	if(iCntr == 0)
	{
		iThreadCnt = omp_get_num_threads();
	}
	__m256 result1 = _mm256_fmadd_ps(vec1, vec2, vec3);
	__m256 result2 = _mm256_fmadd_ps(vec4, vec5, vec6);
	__m256 result3 = _mm256_fmadd_ps(vec7, vec8, vec9);
	__m256 result4 = _mm256_fmadd_ps(result1, result2, result3);		
	asm("");
  }
			dummyMethod2();

  //end timer..
  gettimeofday(&end, NULL);
	
  fTimeTaken = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)); //time in micro-sec
  
  // 2 for the no. of operations performed in one Fused Multiply add
  // 4 for the no. of FMAs performed inside the for loop
  // iLoopCntr is the number of times the loop executes
  // iThreadCnt is the number of threads used to execute the code in parallel
  // 256/32 because we are dealing with float values, and float is 8 bytes
  // fTimeTaken is the time taken in micro-sec
  printf("Number of flops = %f per sec.\n", (2 * 4 * (float)iLoopCntr * (float)iThreadCnt * (256./32.) * 1000000) / fTimeTaken);
  
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