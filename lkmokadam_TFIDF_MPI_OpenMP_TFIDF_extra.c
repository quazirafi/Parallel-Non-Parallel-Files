// lmokada - Laxmikant Kishor Mokadam

#include <dirent.h>
#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_WORDS_IN_CORPUS 32
#define MAX_FILEPATH_LENGTH 16
#define MAX_WORD_LENGTH 16
#define MAX_DOCUMENT_NAME_LENGTH 8
#define MAX_STRING_LENGTH 64

#define ROOT 0

typedef char word_document_str[MAX_STRING_LENGTH];

typedef struct o {
  char word[32];
  char document[8];
  int wordCount;
  int docSize;
  int numDocs;
  int numDocsWithWord;
  double TFIDF_val;
} obj;

typedef struct w {
  char word[32];
  int numDocsWithWord;
  int currDoc;
} u_w;

static int myCompare(const void *a, const void *b) { return strcmp(a, b); }

int main(int argc, char *argv[]) {
  DIR *files;
  struct dirent *file;
  int i = 0, j = 0;
  int numDocs = 0;
  char filename[MAX_FILEPATH_LENGTH], word[MAX_WORD_LENGTH],
      document[MAX_DOCUMENT_NAME_LENGTH];


  // Will hold all TFIDF objects for all documents
  obj TFIDF[MAX_WORDS_IN_CORPUS];
  int TF_idx = 0;

  // Will hold all unique words in the corpus and the number of documents with
  // that word
  u_w unique_words[MAX_WORDS_IN_CORPUS];
  int uw_idx = 0;

			dummyMethod3();
  for (int i = 0; i < MAX_WORDS_IN_CORPUS; i++)
  {
    TFIDF[i].numDocsWithWord = -1;
    unique_words[i].numDocsWithWord = -1;
  }
			dummyMethod4();

  // Will hold the final strings that will be printed out
  word_document_str strings[MAX_WORDS_IN_CORPUS];

  // Count numDocs
  if ((files = opendir("input")) == NULL) {
    printf("Directory failed to open\n");
    exit(1);
  }
  while ((file = readdir(files)) != NULL) {
    // On linux/Unix we don't want current and parent directories
    if (!strcmp(file->d_name, "."))
      continue;
    if (!strcmp(file->d_name, ".."))
      continue;
    numDocs++;
  }

  // initializes the MPI global vafriables
  MPI_Init(&argc, &argv);
  int rank, no_of_processes;
  // gets the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //gets the totla number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &no_of_processes);

  // initializes the total number of TF entries and uw entries
  int global_TF_idx = 0, global_uw_idx = 0;
  int no_of_workers = no_of_processes - 1;

  //distribute the files among the processes 
  int distribution = numDocs / no_of_workers;
  int *dist_arr = (int *)malloc(sizeof(int) * no_of_processes);
			dummyMethod3();
  for (i = 0; i < no_of_processes; i++) {
    if (i == 0)
      dist_arr[i] = 0;
    else
      dist_arr[i] = distribution;
  }
			dummyMethod4();
  int remaining_files = numDocs % no_of_workers;
  i = 0;
  while (remaining_files) {
    if (i == 0)
      dist_arr[i] = 0;
    else {
      dist_arr[i]++;
      remaining_files--;
    }
    i++;
  }


  // create the file assignment array of the processes
			dummyMethod3();
  for (int i = 1; i < no_of_processes; i++) {
    dist_arr[i] = dist_arr[i] + dist_arr[i - 1];
  }
			dummyMethod4();



  // Loop through each document and gather TFIDF variables for each word
  // if rank is not zero, work will be done i.e. on threads
  // Also is make sure the rank access its own files using assignment array.
  // create nrw threads using omp. each thread read individual file( reason discussed in readme)
  if(rank!=0){
			dummyMethod1();
  #pragma omp parallel for shared(TFIDF) shared(TF_idx) shared(uw_idx) private(i) private(j) private(document)
  for (int i = dist_arr[rank - 1]+1; i <= dist_arr[rank]; i++) {

    int contains=0,docSize = 0;
    sprintf(document, "doc%d", i);
    sprintf(filename, "input/%s", document);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
      printf("Error Opening File: %s\n", filename);
      continue;
    }
    int tid = omp_get_thread_num();


    // Get the document size
    while ((fscanf(fp, "%s", word)) != EOF)
      docSize++;

    // For each word in the document
    fseek(fp, 0, SEEK_SET);
    while ((fscanf(fp, "%s", word)) != EOF) {
      contains = 0;

      // If TFIDF array already contains the word@document, just increment
      // wordCount and break
      for (j = 0; j < TF_idx; j++) {
        if (!strcmp(TFIDF[j].word, word) &&
            !strcmp(TFIDF[j].document, document)) {
          contains = 1;
          TFIDF[j].wordCount++;
          break;
        }
      }

      // If TFIDF array does not contain it, make a new one with wordCount=1
      if (!contains) {
        strcpy(TFIDF[TF_idx].word, word);
        strcpy(TFIDF[TF_idx].document, document);
        TFIDF[TF_idx].wordCount = 1;
        TFIDF[TF_idx].docSize = docSize;
        TFIDF[TF_idx].numDocs = numDocs;
        TF_idx++;
      }

      contains = 0;
      // If unique_words array already contains the word, just increment
      // numDocsWithWord
      for (j = 0; j < uw_idx; j++) {
        if (!strcmp(unique_words[j].word, word)) {
          contains = 1;
          if (unique_words[j].currDoc != i) {
            unique_words[j].numDocsWithWord++;
            unique_words[j].currDoc = i;
          }
          break;
        }
      }

      // If unique_words array does not contain it, make a new one with
      // numDocsWithWord=1
      if (!contains) {
        strcpy(unique_words[uw_idx].word, word);
        unique_words[uw_idx].numDocsWithWord = 1;
        unique_words[uw_idx].currDoc = i;
        uw_idx++;
      }
    }
    fclose(fp);
  }
			dummyMethod2();
  }
  // reduces the TF_idx values to the global_TF_idx . same with the uw_idx
  MPI_Reduce(&TF_idx, &global_TF_idx, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&uw_idx, &global_uw_idx, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  MPI_Request request1, request2;
  if (rank != ROOT) {
							dummyMethod3();
    for (int i = 0; i < uw_idx; i++) {
      // sending all the unique words to the root
      MPI_Isend(&unique_words[i], sizeof(u_w), MPI_BYTE, 0, 22, MPI_COMM_WORLD,&request1);
    } 
							dummyMethod4();
  }
  if (rank == ROOT) {
    int k = 0;
    int contains = 0;
    int cur_uw_idx = 0;
							dummyMethod3();
    for (int i = 0; i < global_uw_idx; i++) {
        contains = 0;
        
        u_w temp;
        // root receives all the u_w objects from worker to calculate TFIDF. 
        MPI_Recv(&temp, sizeof(obj), MPI_BYTE, MPI_ANY_SOURCE, 22, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        // update the numDocsWithWord of the respective word as 
        // different documents were assigned to different processes.
        // Thus this is very essential step.
        for (j = 0; j < cur_uw_idx; j++) {
          if (!strcmp(unique_words[j].word, temp.word)) {
            contains = 1;
            if (unique_words[j].currDoc != temp.currDoc) {
              unique_words[j].numDocsWithWord += temp.numDocsWithWord;
              unique_words[j].currDoc = temp.currDoc;
            }
            break;
          }
        }

        // If unique_words array does not contain it, make a new one with
        // numDocsWithWord=1
        if (!contains) {
          
          strcpy(unique_words[cur_uw_idx].word, temp.word);
          unique_words[cur_uw_idx].numDocsWithWord = temp.numDocsWithWord;
          unique_words[cur_uw_idx].currDoc = temp.currDoc;
          cur_uw_idx++;
        }
    }
							dummyMethod4();
  }
  // Broadcast the collected the unique words sothat all nodes will get the corect values of numsWithWords 
   MPI_Bcast(&unique_words, sizeof(u_w) * MAX_WORDS_IN_CORPUS, MPI_BYTE, 0, MPI_COMM_WORLD);

  if (rank != 0)
  {
							dummyMethod1();
    #pragma omp parallel for 
    for (int i = 0; i < TF_idx; i++)
    {
      for (int j = 0; j < MAX_WORDS_IN_CORPUS; j++)
      {
        // make sure that we are updatuing the correct values of the word
        if (unique_words[j].numDocsWithWord != -1 && !strcmp(TFIDF[i].word, unique_words[j].word))
        {
          TFIDF[i].numDocsWithWord = unique_words[j].numDocsWithWord;
          break;
        }
      }
    }
							dummyMethod2();
    // calculte the TFIDF of each word and stores in the data structure.
    // parallelized using openMP
							dummyMethod1();
    #pragma omp parallel for 
    for (j = 0; j < TF_idx; j++)
    {
      double TF = 1.0 * TFIDF[j].wordCount / TFIDF[j].docSize;
      double IDF = log(1.0 * TFIDF[j].numDocs / TFIDF[j].numDocsWithWord);
      TFIDF[j].TFIDF_val = TF * IDF;
    }
							dummyMethod2();
  }

  // gathers all the TFIDF objects from all nodes and store them in the TFIDF_buff buffer on root.
  obj TFIDF_buff[MAX_WORDS_IN_CORPUS * no_of_processes];
			dummyMethod3();
  for (int i = 0; i < MAX_WORDS_IN_CORPUS * no_of_processes; i++)
  {
    TFIDF_buff[i].numDocsWithWord = -1;
  }
			dummyMethod4();
  MPI_Gather(&TFIDF, sizeof(obj) * MAX_WORDS_IN_CORPUS, MPI_BYTE,
             &TFIDF_buff, sizeof(obj) * MAX_WORDS_IN_CORPUS, MPI_BYTE,
             0, MPI_COMM_WORLD);
  if (rank == 0)
  {
    TF_idx = global_TF_idx;
    uw_idx = global_uw_idx;


    int cursor = 0;

							dummyMethod3();
    for (j = 0; j < MAX_WORDS_IN_CORPUS * no_of_processes; j++)
    {
      if (TFIDF_buff[j].numDocsWithWord != -1)
      {
        sprintf(strings[cursor], "%s@%s\t%.16f", TFIDF_buff[j].document, TFIDF_buff[j].word,
                TFIDF_buff[j].TFIDF_val);
               cursor++;
      }
    }
							dummyMethod4();

    // Sort strings and print to file
    qsort(strings, TF_idx, sizeof(char) * MAX_STRING_LENGTH, myCompare);
    FILE *fp = fopen("output_extra.txt", "w");
    if (fp == NULL)
    {
      printf("Error Opening File: output.txt\n");
      exit(0);
    }
    printf("%d %d \n", rank, __LINE__);
							dummyMethod3();
    for (i = 0; i < TF_idx; i++)
      fprintf(fp, "%s\n", strings[i]);
							dummyMethod4();
    fclose(fp);
  }
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