#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define K 1000//Number of Clusters
#define dim 3 //Dimensions of the dataset
#define NUM_THREADS 12
#define ITERATIONS 1000
 struct Point {
    int x[dim];     // dim-D coordinates
    int cluster;     // no default cluster
 };
 struct Point centroid[K];
 struct Point centroid_p[K];
 int centroid_assign(struct Point* p) {
     float result[K];
     //loop over K centroids can be parallelized, each thread takes n clusters
dummyMethod3();
     for (int i = 0; i < K; i++) {
         result[i] = 0;
         //loop over dim
         for (int j = 0; j < dim; j++) {
             result[i] += (p->x[j] - centroid[i].x[j]) * (p->x[j] - centroid[i].x[j]);
             
         } 

     } 
dummyMethod4();
     int location = 0;
dummyMethod3();
     for (int c = 0; c < K; c++)
         if (result[c] < result[location])
             location = c;
     return location;
dummyMethod4();
 }
 void centroid_recalc(struct Point* objects, int N) {
     //zeroing
     int count[K];
									dummyMethod3();
     for (int i = 0; i < K; i++) {
         for (int j = 0; j < dim; j++) {
             centroid[i].x[j] = 0;
         }
         count[i] = 0;
     }
									dummyMethod4();

     //centroid recalculation
									dummyMethod3();
     for (int i = 0; i < N; i++) {
         for (int j = 0; j < dim; j++) {
             centroid[objects[i].cluster].x[j] += objects[i].x[j];
         }
         count[objects[i].cluster]++;

     }
									dummyMethod4();
									dummyMethod3();
     for (int i = 0; i < K; i++) {
         for (int j = 0; j < dim; j++) {
             if (count[i]) {
                 centroid[i].x[j] /= count[i];
             }
             
         }
     }
									dummyMethod4();
 }
 void centroid_p_recalc(struct Point* objects, int N) {
     //zeroing
     int count[K];
									dummyMethod3();
     for (int i = 0; i < K; i++) {
         for (int j = 0; j < dim; j++) {
             centroid_p[i].x[j] = 0;
         }
         count[i] = 0;
     }
									dummyMethod4();

     //centroid recalculation
									dummyMethod3();
     for (int i = 0; i < N; i++) {
         for (int j = 0; j < dim; j++) {
             centroid_p[objects[i].cluster].x[j] += objects[i].x[j];
         }
         count[objects[i].cluster]++;

     }
									dummyMethod4();
									dummyMethod3();
     for (int i = 0; i < K; i++) {
         for (int j = 0; j < dim; j++) {
             if (count[i]) {
                 centroid_p[i].x[j] /= count[i];
             }

         }
     }
									dummyMethod4();
 }
  
 int main() {
#pragma region
     clock_t begin_s, end_s, begin_p, end_p;

     double time_spent_s, time_spent_p;


     //Centroid Random Initialization
     srand((unsigned int)time(NULL));
									dummyMethod3();
     for (int i = 0; i < K; i++) {
         for (int j = 0; j < dim; j++) {
             centroid[i].x[j] = (rand() % 1500) - 750;
             centroid_p[i].x[j] = centroid[i].x[j];
         }
     }
									dummyMethod4();
     /*************************************************************/
     //Reading Test points from text file
     FILE* dataset = fopen("test1.txt", "r");
     int N;
     fscanf(dataset, "%d", &N); //Get the size of the dataset
     struct Point* objects = malloc(sizeof(struct Point) * N); //Create array of 'Point' structs

									dummyMethod3();
     for (int i = 0; i < N; i++) {
         for (int j = 0; j < dim; j++) {
             fscanf(dataset, "%d", &objects[i].x[j]);
         }
     } //Read the coordinates from the file into each struct
									dummyMethod4();
     /************************************************************/
#pragma endregion 
     /************/
#pragma region
     begin_s = clock();
     
     // loop over iterations
									dummyMethod3();
     for (int m = 0; m < ITERATIONS; m++) {
         // loop over N datapoints
         for (int i = 0; i < N; i++) {
             objects[i].cluster = centroid_assign(&objects[i]);
         }
         centroid_recalc(objects, N);
     }     
									dummyMethod4();
									dummyMethod3();
     for (int i = 0; i < K; i++) {
         printf("%d %d %d\n", centroid[i].x[0], centroid[i].x[1], centroid[i].x[2]);
     }
									dummyMethod4();
     printf("//////////////////////////////////////////////////////////////\n");
     end_s = clock();
     

     /**********************************************************/
#pragma endregion   
     /************/
     
     begin_p = clock();
     

     // loop over iterations
     for (int m = 0; m < ITERATIONS; m++) {
         // loop over N datapoints
         int i;
																	dummyMethod1();
#pragma omp parallel for num_threads(NUM_THREADS)
         for (i = 0; i < N; i++) {
             float result[K];
             //loop over K centroids can be parallelized, each thread takes n clusters
             for (int m = 0; m < K; m++) {
                 result[m] = 0;
                 //loop over dim
                 for (int j = 0; j < dim; j++) {
                     result[m] += (objects[i].x[j] - centroid_p[m].x[j]) * (objects[i].x[j] - centroid_p[m].x[j]);

                 }

             }
             int location = 0;
             for (int c = 0; c < K; c++)
                 if (result[c] < result[location])
                     location = c;
             objects[i].cluster = location;

         }
																	dummyMethod2();
         //zeroing
         int count[K];
         for (int i = 0; i < K; i++) {
             for (int j = 0; j < dim; j++) {
                 centroid_p[i].x[j] = 0;
             }
             count[i] = 0;
         }

         //centroid recalculation

         for (i = 0; i < N; i++) {
             for (int j = 0; j < dim; j++) {
                 centroid_p[objects[i].cluster].x[j] += objects[i].x[j];
             }

             count[objects[i].cluster]++;

         }
         for (int i = 0; i < K; i++) {
             for (int j = 0; j < dim; j++) {
                 if (count[i]) {
                     centroid_p[i].x[j] /= count[i];
                 }

             }
         }
     }
     
     for (int i = 0; i < K; i++) {
         printf("%d %d %d\n", centroid_p[i].x[0], centroid_p[i].x[1], centroid_p[i].x[2]); 
     }
     end_p = clock();
     
     /*********************************************************/

     time_spent_s = (double)(end_s - begin_s) / CLOCKS_PER_SEC;// get processor time * 
     printf("Serial took %f seconds to execute\n", time_spent_s);
     

     time_spent_p = (double)(end_p - begin_p) / CLOCKS_PER_SEC;// get processor time * 
     printf("Parallel took %f seconds to execute\n", time_spent_p);

     double speedup = time_spent_s / time_spent_p;
     printf("Speed Up is %f\n", speedup);

     double eff = (time_spent_s / NUM_THREADS) / time_spent_p;
     printf("Effeciency is %f\n", eff);
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