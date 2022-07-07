#include <emmintrin.h> 
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void sgemm( int m, int n, float *A, float *C )
{
    /*
  __m128 answer_vector0;
  __m128 answer_vector1;
  __m128 answer_vector2;
  __m128 answer_vector3;
  __m128 column0;

  //row_inta_b: a is the column in A it corresponds to, b is the index within the column
  __m128 row_int0_0;
  __m128 row_int0_1;
  __m128 row_int0_2;
  __m128 row_int0_3;

  float* answer_address;
  float* row_int_addr0;
  float* col_addr0;

  int j_factor;
  int k_factor;
/*
  omp_set_num_threads(16);
  if(n%3==0 && m%4==0) {

  __m128 column1;
  __m128 column2;

  float* row_int_addr1;
  float* row_int_addr2;

  __m128 row_int1_0;
  __m128 row_int1_1;
  __m128 row_int1_2;
  __m128 row_int1_3;

  __m128 row_int2_0;
  __m128 row_int2_1;
  __m128 row_int2_2;
  __m128 row_int2_3;

  #pragma omp parallel for private (j_factor,answer_address,answer_vector0,answer_vector1,answer_vector2,answer_vector3,k_factor,row_int_addr0,row_int_addr1,row_int_addr2,col_addr0,column0,column1,column2,row_int0_0,row_int0_1,row_int0_2,row_int0_3,row_int1_0,row_int1_1,row_int1_2,row_int1_3,row_int2_0,row_int2_1,row_int2_2,row_int2_3)
  for( int j = 0; j < m/4*4; j+=4 ) {
    j_factor = j * m;
    for( int i = 0; i < m/4*4; i+=4 ) {
      answer_address = C+i+j_factor;
      
      answer_vector0 = _mm_setzero_ps(); //load a vector to total in, to solve a vector in answer matrix in its entirety
      answer_vector1 = _mm_setzero_ps();
      answer_vector2 = _mm_setzero_ps();
      answer_vector3 = _mm_setzero_ps();

     for( int k = 0; k < n/3*3; k+=3 ) {
	k_factor = k * m;
	row_int_addr0 = A+j+k_factor;
	row_int_addr1 = row_int_addr0 + m;
	row_int_addr2 = row_int_addr1 + m;
	col_addr0 = A+i+k_factor;

	column0 = _mm_loadu_ps(col_addr0); //load first column of A
	column1 = _mm_loadu_ps(col_addr0+m); //load second
	column2 = _mm_loadu_ps(col_addr0+2*m);

	row_int0_0 = _mm_load1_ps(row_int_addr0); //load first integer of corresponding column
	row_int0_1 = _mm_load1_ps(row_int_addr0+1); //load second integer
	row_int0_2 = _mm_load1_ps(row_int_addr0+2);
	row_int0_3 = _mm_load1_ps(row_int_addr0+3);

	row_int1_0 = _mm_load1_ps(row_int_addr1); //load first integer of corresponding column
	row_int1_1 = _mm_load1_ps(row_int_addr1+1);
	row_int1_2 = _mm_load1_ps(row_int_addr1+2);
	row_int1_3 = _mm_load1_ps(row_int_addr1+3);
	
	row_int2_0 = _mm_load1_ps(row_int_addr2); //load first integer of corresponding column
	row_int2_1 = _mm_load1_ps(row_int_addr2+1);
	row_int2_2 = _mm_load1_ps(row_int_addr2+2);
	row_int2_3 = _mm_load1_ps(row_int_addr2+3);
	
	answer_vector0 = _mm_add_ps(answer_vector0, _mm_mul_ps(column0, row_int0_0));  //grouped by calls to the same answer vector
	answer_vector0 = _mm_add_ps(answer_vector0, _mm_mul_ps(column1, row_int1_0));
	answer_vector0 = _mm_add_ps(answer_vector0, _mm_mul_ps(column2, row_int2_0));

	answer_vector1 = _mm_add_ps(answer_vector1, _mm_mul_ps(column0, row_int0_1));
	answer_vector1 = _mm_add_ps(answer_vector1, _mm_mul_ps(column1, row_int1_1));
	answer_vector1 = _mm_add_ps(answer_vector1, _mm_mul_ps(column2, row_int2_1));

	answer_vector2 = _mm_add_ps(answer_vector2, _mm_mul_ps(column0, row_int0_2));
	answer_vector2 = _mm_add_ps(answer_vector2, _mm_mul_ps(column1, row_int1_2));
	answer_vector2 = _mm_add_ps(answer_vector2, _mm_mul_ps(column2, row_int2_2));

	answer_vector3 = _mm_add_ps(answer_vector3, _mm_mul_ps(column0, row_int0_3));
	answer_vector3 = _mm_add_ps(answer_vector3, _mm_mul_ps(column1, row_int1_3));
	answer_vector3 = _mm_add_ps(answer_vector3, _mm_mul_ps(column2, row_int2_3));

     }
      _mm_storeu_ps(answer_address, answer_vector0);
      _mm_storeu_ps(answer_address+m, answer_vector1);
      _mm_storeu_ps(answer_address+2*m, answer_vector2);
      _mm_storeu_ps(answer_address+3*m, answer_vector3);
    }
  }
  }
*/
   //not multiple of 4 x 3
  int CACHE_SIZE=(256*32);
  int m_pad = m-m%64; //This is how many more rows of 0 we need
  int n_pad = n-n%64; //This is how many more columns of 0 we need
  int n_new = n+n_pad; //this is the new size of the padded matrix
  int m_new = m+m_pad; //This is the new m of the padded matrix
  

  int ARRAY_SIZE = ((m+m_pad)*(n+n_pad));
    
  float* A_T = malloc(ARRAY_SIZE*sizeof(float));//The Memory for the transposed matrix
  

  omp_set_num_threads(16);
							dummyMethod1();
  #pragma omp parallel for schedule(dynamic)
    for (int j=0; j<m; j++)
	for (int i=0; i<n; i++)
	{
	    memcpy(A_T+i+j*(n+n_pad),A+i*m+j,sizeof(float));//This will take the matrix and transpose it accounting for the new padded matrix
        }
							dummyMethod2();
							dummyMethod1();
  #pragma omp parallel for schedule(dynamic)
    for (int j=0; j<m; j++)
	for (int i=n; i<n+n_pad; i++)
	    memset(A_T+i+j*(n+n_pad),0,sizeof(float));//This will add zeros to the columns
							dummyMethod2();
  float* C_new = malloc(ARRAY_SIZE*sizeof(float));
//The goal of this transposing is to make m divisible by 4, so we can use vectors, and columns divisible by 16, so we can use all 16 threads

  #pragma omp parallel
  {

  /*#pragma omp for private (j_factor,answer_address,answer_vector0,answer_vector1,answer_vector2,answer_vector3,k_factor,row_int_addr0,column0,row_int0_0,row_int0_1,row_int0_2,row_int0_3)      // BEGIN HERE*/

  int ARRAY_SIZE=((m+m_pad)*(n+n_pad));
  
			dummyMethod3();
  for (int j = 0; j < m; j++) {
      for (int i = 0; i < m; i++) {
	for (int k = 0; k < n; k++ ) {
	  k_factor = k*m;
	  C[i+j*m] += A[i+k*m] * A[i+j*m
                               ];

	}
   	 }
 	}
			dummyMethod4();

   }	
}

/*
 for (i=0; i<m  


for( int j = 0; j < m/4*4; j+=4 ) {
    j_factor = j * m;
    for( int i = 0; i < m/4*4; i+=4 ) {
      answer_address = C+i+j_factor;

      answer_vector0 = _mm_setzero_ps(); //load a vector to total in, to solve a vector in answer matrix in its entirety
      answer_vector1 = _mm_setzero_ps();
      answer_vector2 = _mm_setzero_ps();
      answer_vector3 = _mm_setzero_ps();
      for( int k = 0; k < n; k++ ) {
	k_factor = k * m;
	row_int_addr0 = A+j+k_factor;
	column0 = _mm_loadu_ps(A+i+k_factor); //load column of A

	row_int0_0 = _mm_load1_ps(row_int_addr0); //load first integer of corresponding column
	row_int0_1 = _mm_load1_ps(row_int_addr0+1);
	row_int0_2 = _mm_load1_ps(row_int_addr0+2);
	row_int0_3 = _mm_load1_ps(row_int_addr0+3);

	answer_vector0 = _mm_add_ps(answer_vector0, _mm_mul_ps(column0, row_int0_0));
	answer_vector1 = _mm_add_ps(answer_vector1, _mm_mul_ps(column0, row_int0_1));
	answer_vector2 = _mm_add_ps(answer_vector2, _mm_mul_ps(column0, row_int0_2));
	answer_vector3 = _mm_add_ps(answer_vector3, _mm_mul_ps(column0, row_int0_3));
      }

      _mm_storeu_ps(answer_address, answer_vector0);
      _mm_storeu_ps(answer_address+m, answer_vector1);
      _mm_storeu_ps(answer_address+2*m, answer_vector2);
      _mm_storeu_ps(answer_address+3*m, answer_vector3);
    }
    for (int i = m/4*4; i < m; i++) { //cover the edge case from vectorization naively; j not multiple of 4
      for (int k = 0; k < n; k++ ) {
	k_factor = k*m;
	C[i+j_factor] += A[i+k_factor] * A[j+k_factor];
	C[i+j_factor+m] += A[i+k_factor] * A[j+1+k_factor];
	C[i+j_factor+2*m] += A[i+k_factor] * A[j+2+k_factor];
	C[i+j_factor+3*m] += A[i+k_factor] * A[j+3+k_factor];
      }
    }
  }
  }
  for (int j = m/4*4; j < m; j++) {
      for (int i = 0; i < m; i++) {//cover the edge case from vectorization naively; i not multiple of 4
	for (int k = 0; k < n; k++ ) {
	  k_factor = k*m;
	  C[i+j*m] += A[i+k_factor] * A[j+k_factor];
	}
      }
  }
  }


	//C[i+j*m] += A[i+k*m] * A[j+k*m];


*/
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