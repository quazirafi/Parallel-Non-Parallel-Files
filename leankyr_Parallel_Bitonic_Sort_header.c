#include"header.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int Initialize(FILE **data_fp, int argc){    if(argc != 1){
        printf("Usage:...");
        return 1;
    }
    *data_fp = fopen("B_mat.bin","rb");
    if(*data_fp == NULL){
        printf("Could not open data file. Exiting....\n");
        return 1;    } 
    return 0;
} 

float** memAlloc(int size){
    float** table = (float**)malloc(size*sizeof(float *));
    if(table == NULL){
        fprintf(stderr,"Could not allocate memory exiting");
        return NULL;
    }
    int line;
dummyMethod3();
    for (line = 0; line < size ; line++){
        table[line] = (float *)malloc(size*sizeof(float));
        if(table[line]==NULL){
            fprintf(stderr,"Could not allocate mmr for the line: %d\n""Exiting",line);
            return NULL;
        }
    }    
dummyMethod4();
    return table;
}

void matrixTranspose(const matrix* m){
    assert(m != NULL);
    float tmp = 0.0;
															dummyMethod3();
        for (unsigned int i = 0; i < m->size; ++i) {
            for (unsigned int j = i+1; j < m->size; ++j){
                tmp = m->elements[i][j];
                m->elements[i][j] = m->elements[j][i]; 
                m->elements[j][i] = tmp;
            }                
        }
															dummyMethod4();
}

void matrixDisplay(const matrix* m){
    assert(m != NULL);
							dummyMethod3();
    for (unsigned int i = 0; i < m->size; ++i){
        for(unsigned int j = 0; j < m->size; ++j){
            printf("|%.4f| ", m->elements[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
    printf("\n");
}

void Power_Method(vector* tmp, const matrix* m, vector* v){
    assert(tmp != NULL);
    assert (m != NULL);
    assert(v!= NULL);
    assert(tmp->size == v->size);
    assert(m->size == v->size);
    unsigned int size = tmp->size;
							dummyMethod1();
   #pragma omp parallel for num_threads(8)
    for (unsigned int i = 0; i < size; ++i){
        for (unsigned int j = 0; j < size; ++j){
            tmp->elements[i] += m->elements[i][j]*v->elements[j];        }
    }
							dummyMethod2();
}

void matrix_free(matrix* m){
    assert(m != NULL);
							dummyMethod3();
    for (unsigned int i = 0; i < m->size; ++i)
    {
        free(m->elements[i]);
    }
							dummyMethod4();
    free(m->elements);
    m->elements = NULL;
    m->size = 0;
    m = NULL;
}

unsigned int calculate_links(const matrix* m, unsigned int row){
    assert(m != NULL);
    assert(row <= m->size);
    unsigned int counter = 0;
							dummyMethod3();
    for (unsigned int i = 0; i < m->size; ++i){
        counter += m->elements[i][row];                           
    }
							dummyMethod4();
    if(counter == 0){
    return m->size;
    }
    assert(counter <= m->size);
    return counter;
}

float calculate_probability(const matrix* m, unsigned int i, unsigned int j){
    assert(m != NULL);
    float p = 1;
    unsigned int r = calculate_links(m, i);
    float a = (p * m->elements[i][j] / r) + ((1 - p) / m->size);
    return a;
}

void vector_init(vector* v, unsigned int size){
    assert(size > 0);
    v->size = size;
    v->elements = (float*)malloc(v->size*sizeof(float));
}

void vector_free(vector* v){
    assert(v != NULL);
    free(v->elements);
    v->elements = NULL;
    v->size = 0;
    v = NULL;
}

void vector_normalize(vector* v){
    assert(v != NULL);
    float sum = 0.0;
							dummyMethod3();
    for (unsigned int i = 0; i < v->size; ++i){
        sum += v->elements[i];
    }
							dummyMethod4();
							dummyMethod3();
    for (unsigned int i = 0; i < v->size; ++i){
        v->elements[i] /= sum;                       
    }
							dummyMethod4();
}

void vector_sort(vector* v){        
    assert(v != NULL);
    qsort(v->elements, v->size, sizeof(float), float_comparator);
}

void vector_display(vector* v) {
    assert (v != NULL);
							dummyMethod3();
    for (unsigned int i = 0; i < v->size; ++i){
        printf("|%.8f| \n", v->elements[i]);                  
    }
							dummyMethod4();
    printf("\n");
}


int float_comparator(const void* a, const void* b){
    float* arg1 = (float*) a;
    float* arg2 = (float*) b;
    if(*arg1 < *arg2){
        return -1;                    
    }
    else if(*arg1 == *arg2){
        return 0;              
    }
    else{
        return 1;                                
    }
}

int compare_floats(float a, float b){
    if (fabs(a - b) < 0.1) // just for unit testing, good enough
    {
        return 1;            
    }
    return 0;
}

void countOutlinks(matrix* A, vector* out_link, int size){
							dummyMethod3();
    for(int i = 0; i < size; i++){
        for(int j = 0; j< size; j++){
            if(A->elements[i][j] != 0.0){
                out_link->elements[i] += 1.0;
            } 
        }
    } 
							dummyMethod4();

}


void stochastiphyMatrix(matrix* A, vector* out_link, int size){
							dummyMethod3();
    for(int i = 0; i < size ; i++){
        if(out_link->elements[i] == 0){
            for (int j = 0; j < size ; j++){
                A->elements[i][j] = 1/size; 
            }        
        }
        else{
            for (int j = 0; j <size ; j++){
                if(A->elements[i][j] != 0){
                    A->elements[i][j] = A->elements[i][j] / out_link->elements[i];
                } 
            }
        }
    }
							dummyMethod4();

}


void setToZero(matrix* m, int size){
							dummyMethod3();
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            m->elements[i][j] = 0.0;
        }
    }
							dummyMethod4();
}


void gaussSiedel(vector* tmp, const matrix* A,vector* P){
    assert(tmp != NULL);
    assert (A != NULL);
    assert(P != NULL);
    int size = tmp->size;
							dummyMethod1();
    #pragma omp parallel for num_threads(8)
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++ ){
            if(tmp->elements[j] != 0){
                tmp->elements[i] += A->elements[i][j]*tmp->elements[j];}   
            else{
                tmp->elements[i] += A->elements[i][j]*P->elements[j];   
                }                    
        }           
    }   
							dummyMethod2();
}    
    
void createMatrixM(const matrix* A,float d ){
    int sz = A->size;
							dummyMethod3();
    for(int i=0;i<sz;i++){
        for(int j=0;j<sz;j++){
            A->elements[i][j] = d*A->elements[i][j] + (1.0-d)/sz;
            } 
        }
							dummyMethod4();
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