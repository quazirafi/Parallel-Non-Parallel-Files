#include "headers.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Function to do scalar multiplication with integer matrix type*/
void intsm(int* row, int* col, int * val, int num_nonzeros, 
					FILE* fptr, int num_row, int num_col){
// omp_set_num_threads(input_num_threads);
#pragma omp parallel
	{
#pragma omp single
		{
			for (int common_index = 0; common_index < num_nonzeros; common_index++){
dummyMethod1();
#pragma omp parallel for collapse(2)
				for (int i = 0; i < num_row; i++){
					for(int j = 0 ; j < num_col; j++){
						{
							if(i == row[common_index] && j == col[common_index]){
								fprintf(fptr,"%d. ", val[common_index]*(int)input_scalar);
								if(!required_logging)printf("%d. ", val[common_index]*(int)input_scalar);
									common_index++;
							} else {
								fprintf(fptr,"%d. ", 0);
								if(!required_logging)printf("%d. ", 0);
							}
						}
					}			
				} // end of for collapse
dummyMethod2();
				
			}
		} // end of single region
	} // end of parallel region	
	fprintf(fptr,"\n");
	if(!required_logging)printf("\n");
	
}

/* Function to do scalar multiplication with float matrix type */
void floatsm(int* row, int* col, long double* val, 
			int num_nonzeros, FILE* fptr, int num_row, int num_col){
#pragma omp parallel
	{
#pragma omp single
		{
			for (int common_index = 0; common_index < num_nonzeros; common_index++){
							dummyMethod1();
#pragma omp parallel for collapse(2)
				for (int i = 0; i < num_row; i++){
					for(int j = 0 ; j < num_col; j++){
						if(i == row[common_index] && j == col[common_index]){
							fprintf(fptr,"%.10Lg ", val[common_index]*input_scalar);
							if(!required_logging) 
								{printf("%.10Lg ", val[common_index]*input_scalar);}
								common_index++;
						} else {
							fprintf(fptr,"%d. ", 0);
							if(!required_logging) printf("%d.%d ", 0,0);
						}
					}			
				}
							dummyMethod2();
			
			} // end of collapse
		} // end of omp single
		
	} // end of parallel region
	fprintf(fptr,"\n");
	if(!required_logging)printf("\n");
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