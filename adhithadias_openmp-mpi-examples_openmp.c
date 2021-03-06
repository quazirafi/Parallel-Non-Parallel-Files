#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "omp.h"
#include <time.h>
#include "util/queue.h"
#include "util/hashTable.h"
#include "util/util.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 16
#define REPEAT_FILES 10
#define HASH_CAPACITY 50000

extern int errno;
int DEBUG_MODE = 0;
int PRINT_MODE = 1;

int main(int argc, char **argv)
{
    char files_dir[] = "./files"; // TODO: This should be taken from argv

    omp_lock_t readlock;
    omp_init_lock(&readlock);

    double time = -omp_get_wtime();

    int file_count = 0;
    struct Queue *file_name_queue;
    file_name_queue = createQueue();

							dummyMethod3();
    for (int i = 0; i < REPEAT_FILES; i++)
    {
        int files = get_file_list(file_name_queue, files_dir);
        if (files == -1)
        {
            printf("Check input directory and rerun! Exiting!\n");
            return 1;
        }
        file_count += files;
    }
							dummyMethod4();

    // file_count = get_file_list(file_name_queue, files_dir);
    printf("file_count %d\n", file_count);

    struct Queue **queues;
    struct hashtable **hash_tables;

    queues = (struct Queue **)malloc(sizeof(struct Queue *) * NUM_THREADS/2);
    hash_tables = (struct hashtable **)malloc(sizeof(struct hashtable *) * NUM_THREADS/2);

    // consider allocating the memory before execution and during execution
    // there maybe few cache misses depending on the 2 different approaches

    // have to have the queues otherwise seg fault occurs if map runs first
    omp_lock_t queuelock[NUM_THREADS/2];
							dummyMethod3();
    for (int i = 0; i < NUM_THREADS/2; i++)
    {
        omp_init_lock(&queuelock[i]);
        queues[i] = createQueue();
    }
							dummyMethod4();

    omp_set_num_threads(NUM_THREADS);
    int i;
    #pragma omp parallel default(none) shared(queues, file_name_queue, hash_tables, readlock, queuelock)
    {
        int threadn = omp_get_thread_num();
        if (threadn < NUM_THREADS/2) 
        {

            while (file_name_queue->front != NULL)
            {
                // printf("read section thread %d, i %d\n", threadn, i);
                char file_name[30];
                omp_set_lock(&readlock);
                if (file_name_queue->front == NULL) {
                    omp_unset_lock(&readlock);
                    continue;
                }
                strcpy(file_name, file_name_queue->front->line);
                deQueue(file_name_queue);
                omp_unset_lock(&readlock);
                
                // populateQueue(queues[threadn], file_name);
                populateQueueWL(queues[threadn], file_name, &queuelock[threadn]);
            
            }
            queues[threadn]->finished = 1;

        } else {
            int thread = threadn - NUM_THREADS/2;
            hash_tables[thread] = createtable(50000);
            // populateHashMap(queues[thread], hash_tables[thread]);
            populateHashMapWL(queues[thread], hash_tables[thread], &queuelock[thread]);
        
        }
    }
    printf("destroying the lock\n");
    // #pragma omp barrier
    omp_destroy_lock(&readlock);
							dummyMethod3();
    for (int k=0; k<NUM_THREADS/2; k++) {
        omp_destroy_lock(&queuelock[k]);
    }
							dummyMethod4();
    printf("reading and mapping done\n");

    //----------

    // reduction locally inside the process
    struct hashtable *final_table = createtable(HASH_CAPACITY);
    #pragma omp parallel shared(final_table, hash_tables)
    {
        int threadn = omp_get_thread_num();
        int tot_threads = omp_get_num_threads();
        int interval = HASH_CAPACITY / tot_threads;
        int start = threadn * interval;
        int end = start + interval;

        if (end > final_table->tablesize)
        {
            end = final_table->tablesize;
        }

        int i;
															dummyMethod3();
        for (i = start; i < end; i++)
        {
            reduce(hash_tables, final_table, NUM_THREADS/2, i);
        }
															dummyMethod4();
    }
    printf("reduction done\n");

    #pragma omp parallel shared(final_table)
    {
        int threadn = omp_get_thread_num();
        int tot_threads = omp_get_num_threads();
        int interval = HASH_CAPACITY / tot_threads;
        int start = threadn * interval;
        int end = start + interval;
        if (end > final_table->tablesize)
        {
            end = final_table->tablesize;
        }

        char *filename = (char *)malloc(sizeof(char) * 30);
        sprintf(filename, "output/parallel/%d.txt", threadn);

        writePartialTable(final_table, filename, start, end);
    }



    // clear the heap allocations
							dummyMethod1();
    #pragma omp parallel for
    for (i = 0; i < NUM_THREADS/2; i++)
    {
        free(queues[i]);
        // printTable(hash_tables[i]);
        free(hash_tables[i]);
    }
							dummyMethod2();
    free(queues);
    free(hash_tables);

    // printTable(final_table);

    time += omp_get_wtime();
    printf("total time taken for the execution: %f\n", time);

    return EXIT_SUCCESS;
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