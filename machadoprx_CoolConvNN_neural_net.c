//
// Created by vmachado on 2/11/20.
//

#include "neural_net.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

float accurracy(matrix *prob, int *indices, int *labels) {
    int correct = 0;
    const float threshold = 0.5f;
dummyMethod3();
    for (int i = 0; i < prob->rows; i++) {
        if (prob->data[i * prob->columns + labels[ indices[i] ]] > threshold) {
            correct++;
        }
    }
dummyMethod4();

    return (float)correct / (float)prob->rows;
}

matrix* prob_del(matrix* prob, int *indices, int *labels) {

    matrix *dprob = matrix_alloc(prob->rows, prob->columns);
    const float n_inv = 1.0f / (float)prob->rows;

							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < prob->rows; i++) {
        
        float *dp_row = dprob->data + i * prob->columns;
        float *p_row = prob->data + i * prob->columns;

        dp_row[ labels[ indices[i] ] ] = -1.0f;
        for (int j = 0; j < prob->columns; j++) {
            dp_row[j] = (dp_row[j] + p_row[j]) * n_inv;
        }
    }
							dummyMethod2();

    return dprob;
}

float loss(matrix* prob, int *indices, int *labels){

    float out = .0f;

							dummyMethod1();
    #pragma omp parallel for reduction(+: out)
    for (int i = 0; i < prob->rows; i++) {
        out += logf(prob->data[i * prob->columns + labels[ indices[i] ]]);
    }
							dummyMethod2();

    return -out / (float)prob->rows;
}

float reg_loss(void **layers, int *layer_type, int len, float l_reg) {

    float out = .0f;

							dummyMethod3();
    for (int i = 0; i < len; i++) {
        if (layer_type[i] == FC) {
            matrix *w = ((fc_layer*)layers[i])->weights;
            matrix *temp = elemwise_mul(w, w);
            out += 0.5f * l_reg * sum_elem(temp);
            matrix_free(temp);
        }
    }
							dummyMethod4();

    return out;
}

int* random_indices(int samples) {

    int *indices = aalloc(sizeof(int) * samples);
    
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < samples; i++) {
        indices[i] = i;
    }
							dummyMethod2();

    srand((int)time(0));

							dummyMethod3();
    for (int i = samples - 1; i >= 1; i--) {
        int rand_index = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[rand_index];
        indices[rand_index] = temp;
    }
							dummyMethod4();

    return indices;
}

matrix* get_batch(int *indices, float **data_set, int batch_len, int data_dim) {
    
    matrix *batch = matrix_alloc(batch_len, data_dim);

							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < batch_len; i++) {

        register float *dest_ptr = batch->data + (i * data_dim);
        for (int j = 0; j < data_dim; j++) {
            dest_ptr[j] = data_set[ indices[i] ][j];
        }
    }
							dummyMethod2();
    return batch;
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