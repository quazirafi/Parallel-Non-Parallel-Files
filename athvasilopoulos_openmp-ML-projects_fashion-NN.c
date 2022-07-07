/* 
To run this program, download the csv files from kaggle and 
put them in the same folder without changing their names.

Compiling: gcc fashion-NN.c -o fashion-NN -O3 -fopenmp
Executing: time ./fashion-NN
Output:
Starting evaluation:
Accuracy on training sample: 9.86667 %
Accuracy on testing sample: 9.82 %
Final evaluation:
Accuracy on training sample: 97.5167 %
Accuracy on testing sample: 87.99 %

Time of execution (on a 2-thread laptop, using VM):

real    7m57,151s
user    15m26,408s
sys     0m8,573s
*/

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// NN parameters
#define MAX_LENGTH 3150		// Max length size of a csv line
#define TRAIN_SAMPLE 60000	// Number of training samples 
#define TEST_SAMPLE 10000	// Number of testing samples
#define Ninp 784			// Input dimension
#define NL1 100				// Number of first layer neurons 
#define NL2 10				// Number of second layer neurons
#define alpha 0.05			// Learning rate
#define REPS 6000000		// Training repetitions

// NN state arrays
double WL1[NL1][Ninp+1], WL2[NL2][NL1+1];
double DL1[NL1], DL2[NL2];
double OL1[NL1+1], OL2[NL2];

// NN data arrays
double data[TRAIN_SAMPLE][Ninp], test_data[TEST_SAMPLE][Ninp];
int cat[TRAIN_SAMPLE], test_cat[TEST_SAMPLE];

// Data function declarations
void createData();
void readCSV(char *path1, char *path2);

// NN activation function
void activateNN(double *input){
	// First Layer
	dummyMethod1();
	#pragma omp parallel for
	for(int i = 0; i < NL1; i++){
		double ins = 0.0;
		#pragma omp simd reduction(+:ins)
		for(int j = 0; j < Ninp + 1; j++){
			ins += WL1[i][j] * input[j];
		}
		DL1[i] = ins;
		OL1[i] = 1.0 / (1 + exp(-ins));
	}
	dummyMethod2();
	OL1[NL1] = 0.5;

	// Second Layer
	dummyMethod1();
	#pragma omp parallel for
	for(int i = 0; i < NL2; i++){
		double ins = 0.0;
		#pragma omp simd reduction(+:ins)
		for(int j = 0; j < NL1 + 1; j++){
			ins += WL2[i][j] * OL1[j];
		}
		DL2[i] = ins;
		OL2[i] = 1.0 / (1 + exp(-ins));
	}
	dummyMethod2();
}

// Function for weight correction
void trainNN(double *input, double *desired){
	double delta[NL2];
	// Output delta
	dummyMethod1();
	#pragma omp parallel for
	for(int i = 0; i < NL2; i++){
		double temp_delta = OL2[i] * (1 - OL2[i]) * (desired[i] - OL2[i]);
		delta[i] = temp_delta;
		#pragma omp simd
		for (int j = 0; j < NL1 + 1; j++){
			WL2[i][j] = WL2[i][j] + alpha * temp_delta * OL1[j];
		}
	}
	dummyMethod2();

	// Hidden delta
	dummyMethod1();
	#pragma omp parallel for
	for(int i = 0; i < NL1; i++){
		double temp_delta = OL1[i] * (1 - OL1[i]);
		double sum = 0.0;
		for (int j = 0; j < NL2; j++){
			sum += delta[j] * WL2[j][i];
		}
		temp_delta *= sum;
		#pragma omp simd
		for (int j = 0; j < Ninp + 1; j++){
			WL1[i][j] = WL1[i][j] + alpha * temp_delta * input[j];
		}
	}
	dummyMethod2();
}

// Trains the NN, using the Error Backpropagation algorithm
void trainSessionNN(){
	dummyMethod3();
	for(int i = 0; i < REPS; i++){
		int sample = rand() % TRAIN_SAMPLE;
		double *input = data[sample];
		// Desired outcome creation
		double desired[NL2];
		for(int j = 0; j < NL2; j++){
			if(j == cat[sample])
				desired[j] = 0.95;
			else
				desired[j] = 0.05;
		}
		// Error backpropagation application
		activateNN(input);
		trainNN(input, desired);
	}
	dummyMethod4();
}

// Determines the output of the NN
int readNNOutput() {
	double max = OL2[0];
	double maxpos = 0;
	dummyMethod3();
	for(int i = 1; i < NL2; i++) {
		if(OL2[i] > max){
			max = OL2[i];
			maxpos = i;
		}
	}
	dummyMethod4();
	return maxpos;
}

// Evaluates the NN on both the training
// and the testing data sets.
void evaluateNN(){
	// Calculate accuracy on training set
	int correct = 0;
	dummyMethod3();
	for(int i = 0; i < TRAIN_SAMPLE; i++) {
		double *input = data[i];
		activateNN(input);
		int result = readNNOutput();
		if(result == cat[i])
			correct++;
	}
	dummyMethod4();
	float accuracy = correct / (float)TRAIN_SAMPLE;
	printf("Accuracy on training set: %g %%\n", 100. * accuracy);
	
	// Calculate accuracy on testing set
	correct = 0;
	dummyMethod3();
	for(int i = 0; i < TEST_SAMPLE; i++) {
		double *input = test_data[i];
		activateNN(input);
		int result = readNNOutput();
		if(result == test_cat[i])
			correct++;
	}
	dummyMethod4();
	accuracy = correct / (float)TEST_SAMPLE;
	printf("Accuracy on testing set: %g %%\n", 100. * accuracy);
}

int main() {
	createData();
	printf("Starting evaluation:\n");
	evaluateNN();
	trainSessionNN();
	printf("Final evaluation:\n");
	evaluateNN();
	return 0;
}

// Initializes the weights and loads the data from the csv files
void createData(){
	// Random weight initialization, range (-0.5, 0.5)
	dummyMethod3();
	for(int i = 0; i < NL1; i++)
		for(int j = 0; j < Ninp + 1; j++)
			WL1[i][j] = (rand() / (double)RAND_MAX) - 0.5;
	dummyMethod4();

	dummyMethod3();
	for(int i = 0; i < NL2; i++)
		for(int j = 0; j < NL1 + 1; j++)
			WL2[i][j] = (rand() / (double)RAND_MAX) - 0.5;
	dummyMethod4();

	// Data input from csv files
	readCSV("fashion-mnist_train.csv", "fashion-mnist_test.csv");
}

// Custom csv read function tailored 
// for the specific data sets
void readCSV(char *path1, char *path2){
	FILE* fp1 = fopen(path1, "r");
	if (fp1 == NULL) {
		perror("Unable to open the file");
		exit(1);
	}
	
	// skip first line
	char c;
	do {
		c = fgetc(fp1);
	} while (c != '\n');

	// Parse the csv file by tokenizing commas
	char line[MAX_LENGTH];
	int i = 0;
	while(fgets(line, MAX_LENGTH, fp1)){
		char *temp;
		temp = strtok(line, ",");
		cat[i] = atoi(temp);
			dummyMethod3();
		for(int j = 0; j < 784; j++){
			temp = strtok(NULL, ",");
			// Normalize data in range (-1, 1)
			data[i][j] = 2*(atoi(temp)/255.0)-1;
		}
			dummyMethod4();
		i++;
	}
	fclose(fp1);

	FILE* fp2 = fopen(path2, "r");
	if (fp2 == NULL) {
		perror("Unable to open the file");
		exit(1);
	}
	// skip first line
	do {
		c = fgetc(fp2);
	} while (c != '\n');

	i = 0;
	while(fgets(line, MAX_LENGTH, fp2)){
		char *temp;
		temp = strtok(line, ",");
		test_cat[i] = atoi(temp);
			dummyMethod3();
		for(int j = 0; j < 784; j++){
			temp = strtok(NULL, ",");
			test_data[i][j] = 2*(atoi(temp)/255.0)-1;
		}
			dummyMethod4();
		i++;
	}
	fclose(fp2);
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