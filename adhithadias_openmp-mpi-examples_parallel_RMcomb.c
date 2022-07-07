#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "omp.h"
#include "util/queue.h"
#include "util/hashTable.h"
#include "util/util.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

extern int errno;
int DEBUG_MODE = 0;
int PRINT_MODE = 0;

int main(int argc, char **argv)
{
    int NUM_THREADS = 16;
    int HASH_SIZE = 50000;
    int QUEUE_TABLE_COUNT = 1;
    char files_dir[FILE_NAME_BUF_SIZE] = "./files/";
    int file_count = 0;
    int repeat_files = 1;
    double global_time = -omp_get_wtime();
    double local_time;
    char csv_out[400] = "";
    char tmp_out[200] = "";  // Buffer was small. sprintf caused a buffer overflow and modified the inputs. 
    // https://stackoverflow.com/questions/3706086/using-sprintf-will-change-the-specified-variable

    // Parsing User inputs from run command with getopt
    int arg_parse = process_args(argc, argv, files_dir, &repeat_files, &DEBUG_MODE, &PRINT_MODE, &HASH_SIZE,
                                 &QUEUE_TABLE_COUNT, &NUM_THREADS);
    QUEUE_TABLE_COUNT = 1; // Forcing the count to 1
    if (arg_parse == -1)
    {
        printf("Check inputs and rerun! Exiting!\n");
        return 1;
    }

    omp_set_num_threads(NUM_THREADS);
    omp_lock_t writelock;
    omp_init_lock(&writelock);

    /********************** Creating and populating FilesQueue ************************************************/
    struct Queue *file_name_queue;
    file_name_queue = createQueue();

    if (DEBUG_MODE)
    {
        printf("\nQueuing files in Directory: %s\n", files_dir);
        printf("Queuing files %d time(s)\n", repeat_files);
    }
    local_time = -omp_get_wtime();
							dummyMethod3();
    for (int i = 0; i < repeat_files; i++)
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
    local_time += omp_get_wtime();
    sprintf(tmp_out, "%d, %d, %d, %.4f, ", file_count, HASH_SIZE, NUM_THREADS, local_time);
    strcat(csv_out, tmp_out);
    if (PRINT_MODE)
        printf("Done Queuing %d files! Time taken: %f\n", file_count, local_time);
    /**********************************************************************************************************/
    // TODO: This should be an array as in Prof's lecture (Week 4: Uniform distribution of Elements)
    int files_per_qt = file_count / (QUEUE_TABLE_COUNT * NUM_THREADS);
    if (PRINT_MODE)
    {
        printf("\nNumber of Queues and Tables: %d\n", QUEUE_TABLE_COUNT * NUM_THREADS);
        printf("Number of files per Q&T: %d\n", files_per_qt);
    }
    /********************** Queuing Lines by reading files in the FilesQueue **********************************/
    if (PRINT_MODE)
    {
        printf("\nQueuing Lines by reading files in the FilesQueue\n");
        printf("Hashing Words by reading words in the LinesQueue\n");
        printf("HASH_SIZE: %d\n", HASH_SIZE);
    }
    local_time = -omp_get_wtime();
    struct Queue **queues;
    queues = (struct Queue **)malloc(sizeof(struct Queue *) * NUM_THREADS);
    struct hashtable **hash_tables;
    hash_tables = (struct hashtable **)malloc(sizeof(struct hashtable *) * NUM_THREADS);
    #pragma omp parallel shared(queues) num_threads(NUM_THREADS)
    {
        int i = omp_get_thread_num();
        queues[i] = createQueue();
        hash_tables[i] = createtable(HASH_SIZE);
        char file_name[FILE_NAME_BUF_SIZE * 3];
        while(file_name_queue->front != NULL) {
            omp_set_lock(&writelock);
            if (file_name_queue->front == NULL) {
                omp_unset_lock(&writelock); 
                continue;
            }
            if (DEBUG_MODE)
                printf("thread: %d, filename: %s\n", i, file_name_queue->front->line);
            strcpy(file_name, file_name_queue->front->line);
            deQueue(file_name_queue);
            omp_unset_lock(&writelock);  

            populateQueue(queues[i], file_name);         
        }
        queues[i]->finished = 1; //TODO: What is this for?
        populateHashMap(queues[i], hash_tables[i]);
    }
    omp_destroy_lock(&writelock); // TODO: Can keep this lock if another queue needs to be locked below
    local_time += omp_get_wtime();
    sprintf(tmp_out, "%.4f, ", local_time);
    strcat(csv_out, tmp_out);
    if (PRINT_MODE)
        printf("Done Populating lines and Hashing words! Time taken: %f\n", local_time);
    /**********************************************************************************************************/

    // consider allocating the memory before execution and during execution
    // there maybe few cache misses depending on the 2 different approaches
    // consider using sections and run both the reading and mapping
    // at the same time, a variable can be used in the queue to
    // indicate the reader status -- whether reading is finished or not

    /********************** Reducing the populated words in HashTable *****************************************/
    if (PRINT_MODE)
        printf("\nReducing the populated words in HashTable\n");
    local_time = -omp_get_wtime();
    struct hashtable *final_table = createtable(HASH_SIZE);
    #pragma omp parallel shared(final_table, hash_tables)
    {
        int threadn = omp_get_thread_num();
        int tot_threads = omp_get_num_threads();
        int interval = HASH_SIZE / tot_threads;
        int start = threadn * interval;
        int end = start + interval;
        // Is hash_tables[threadn]->tablesize the same?
        if (end > final_table->tablesize)
        {
            end = final_table->tablesize;
        }
															dummyMethod3();
        for (int i = start; i < end; i++)
        {
            reduce(hash_tables, final_table, NUM_THREADS, i);
        }
															dummyMethod4();
    }
    local_time += omp_get_wtime();
    sprintf(tmp_out, "%.4f, ", local_time);
    strcat(csv_out, tmp_out);
    if (PRINT_MODE)
        printf("Done Reducing! Time taken: %f\n", local_time);
    /**********************************************************************************************************/

    // printTable(final_table);
    // writeTable(final_table, "output/parallel/0.txt");

    /********************** Writing Reduced counts to output file *********************************************/
    if (PRINT_MODE)
        printf("\nWriting Reduced counts to output file\n");
    local_time = -omp_get_wtime();
    #pragma omp parallel shared(final_table)
    {
        int threadn = omp_get_thread_num();
        int tot_threads = omp_get_num_threads();
        int interval = HASH_SIZE / tot_threads;
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
    local_time += omp_get_wtime();
    sprintf(tmp_out, "%.4f, ", local_time);
    strcat(csv_out, tmp_out);
    if (PRINT_MODE)
        printf("Done Writing! Time taken: %f\n", local_time);
    /**********************************************************************************************************/

    /********************** Clearing the heap allocations for Queues and HashTables ***************************/
    if (DEBUG_MODE)
        printf("\nClearing the heap allocations for Queues and HashTables\n");
    local_time = -omp_get_wtime();
							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < QUEUE_TABLE_COUNT * NUM_THREADS; i++)
    {
        free(queues[i]);
        // printTable(hash_tables[i]);
        free(hash_tables[i]);
    }
							dummyMethod2();
    free(queues);
    free(hash_tables);
    local_time += omp_get_wtime();
    if (DEBUG_MODE)
        printf("Done Clearing! Time taken: %f\n", local_time);
    /**********************************************************************************************************/

    global_time += omp_get_wtime();
    sprintf(tmp_out, "%.4f, ", global_time);
    strcat(csv_out, tmp_out);
    if (PRINT_MODE)
        printf("\nTotal time taken for the execution: %f\n", global_time);
    printf("Num_files, Hash_size, Num_Threads, Qfiles_time, Qlines_HashW_time, Reduce_time, Write_time, Total_time,\n%s\n\n", csv_out);

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