/*
 ============================================================================
 Name        : final_project.c
 Author      : Oren Vaknin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <mpi.h>
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "myProto.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
	int size, rank, i, numOfSeq, offset = 0, maxOffset, seq1Len, seq2Len,
			bestOffset, hyphen, bestMutant;
	char *seq1, *seq2, *mutant;
	char answer[70];
	double w[4], bestScore = 0;
	MutantData *mutantsData;
	MPI_Status status;

	//Reading shared data before the separation to many processes
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (size != 5) {
		printf("Run the example with five processes only\n");
		MPI_Abort(MPI_COMM_WORLD, __LINE__);
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		FILE *fp;
		fp = fopen("input.txt", "r");

		if (!fp) {
			printf("Fp failed");
		}
		fscanf(fp, "%lf %lf %lf %lf", &w[0], &w[1], &w[2], &w[3]);
		seq1 = (char*) malloc(SIZE * sizeof(char));
		seq2 = (char*) malloc(SIZE2 * sizeof(char));
		fscanf(fp, "%s", seq1);
		fscanf(fp, "%d", &numOfSeq);

		// Divides the tasks between all processes
			dummyMethod3();
		for (i = 1; i < numOfSeq + 1; i++) {
			fscanf(fp, "%s", seq2);
			MPI_Send(w, 4, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			MPI_Send(seq1, SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
			MPI_Send(seq2, SIZE2, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}
			dummyMethod4();
		fclose(fp);

		//Receives all answers from other processors and writes them into output.txt
		fp = fopen("output.txt", "w");
			dummyMethod3();
		for (i = 1; i < numOfSeq + 1; i++) {
			MPI_Recv(answer, 70, MPI_CHAR, i, 1, MPI_COMM_WORLD, &status);
			fprintf(fp, "%s\n", answer);
		}
			dummyMethod4();
		printf("All tasks have been completed successfully!\n");
		fclose(fp);

	} else {
		// Each process gets data and a different seq to calculate
		if ((seq2 = (char*) malloc(SIZE2 * sizeof(char))) == NULL || (seq1 =
				(char*) malloc(SIZE * sizeof(char))) == NULL)
			MPI_Abort(MPI_COMM_WORLD, __LINE__);
		MPI_Recv(w, 4, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(seq1, SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(seq2, SIZE2, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

		//running on the seq
		seq1Len = (int) (size_t) strlen(seq1);
		seq2Len = (int) (size_t) strlen(seq2);
		maxOffset = seq1Len - seq2Len;
		char results[maxOffset][seq2Len];
		double finalScores[seq2Len + 1][maxOffset];
		if ((mutant = (char*) malloc((SIZE2) * sizeof(char))) == NULL
				|| (mutantsData = (MutantData*) malloc(
						(seq2Len + 1) * sizeof(MutantData))) == NULL)
			MPI_Abort(MPI_COMM_WORLD, __LINE__);

			dummyMethod1();
#pragma omp parallel for private(i,offset,mutant,bestOffset,bestScore)
		for (hyphen = 0; hyphen < seq2Len + 1; hyphen++) {
			mutant = createNewMutant(seq2, seq2Len, hyphen);

			for (offset = 0; offset < maxOffset; offset++) {

				for (i = 0; i < seq2Len + 1; i++) {
					results[offset][i] = compareChars(seq1[i + offset],
							mutant[i]);

				}
				finalScores[hyphen][offset] = calculateScore(maxOffset, seq2Len,
						results, offset, w);

			}
			bestOffset = findOffsetWithHighestScore(seq2Len + 1, maxOffset,
					finalScores, hyphen);
			bestScore = finalScores[hyphen][bestOffset];
			mutantsData[hyphen].bestOffset = bestOffset;
			mutantsData[hyphen].bestScore = bestScore;

		}
			dummyMethod2();
		bestMutant = findMutantWithHighestScore(mutantsData, seq2Len + 1);
		snprintf(answer, 70,
				"Process: %d, Best Mutant: %d, Best Offset: %d, Best Score: %.1f",
				rank, bestMutant, mutantsData[bestMutant].bestOffset,
				mutantsData[bestMutant].bestScore);
		printf("%s\n", answer);
		MPI_Send(answer, 70, MPI_CHAR, 0, 1, MPI_COMM_WORLD);

	}

	MPI_Finalize();

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