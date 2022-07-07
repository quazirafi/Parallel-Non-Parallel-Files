#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Source pour cette façon de faire le max:
// https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html#Statement-Exprs
#define maxint(a,b) ({int _a = (a), _b = (b); _a > _b ? _a : _b; })


/* *************Fonctions utiles********** */

int* createArray(int size) {
    return malloc(size * sizeof(int));
}

int* etapeZero(int* inputTable, int inputSize){
    
    int* a = createArray(2*inputSize);
    
dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < inputSize; i++)
    {
        a[inputSize + i] = inputTable[i];
    }
dummyMethod2();
    
    return a;
}

int* retrieveResult(int* b, int inputSize){
    int* result = createArray(inputSize);

							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < inputSize; i++) {
        result[i] = b[inputSize + i];
    }
							dummyMethod2();

    return result;    
}

int* flipArray(int* table, int size) {

    int* flipped = createArray(size);

							dummyMethod1();
    #pragma omp parallel for
    for (int i = 1; i <= size; i++) {
        flipped[size - i] = table[i - 1];
    }
							dummyMethod2();

    return flipped;
}


/* *************Partie Somme********** */

void monteeSomme(int* a, int m){

    for (int l = m-1; l >= 0; l--) {
        //pour eviter d'avoir a calculer ça a chaque test de j < end
        int end = pow(2, l+1);
        
															dummyMethod1();
        #pragma omp parallel for
        for (int j = pow(2, l); j < end; j++)
            a[j] = a[2 * j] + a[2 * j + 1];
															dummyMethod2();
    }
}

void descenteSomme(int* a, int* b, int m){

    b[1] = 0;

    for (int l = 1; l < m; l++) {
        int end = pow(2, l + 1);

															dummyMethod1();
        #pragma omp parallel for
        for (int j = pow(2, l); j < end; j++)
        {
            if (j % 2 == 0) {
                b[j] = b[j / 2];
            }
            else {
                b[j] = b[j / 2] + a[j - 1];
            }
        }
															dummyMethod2();
    }
}

void finaleSomme(int* a, int* b, int m) {
    
    int end = pow(2, m + 1);

							dummyMethod1();
    #pragma omp parallel for
    for (int j = pow(2, m); j < end; j++) {
        b[j] = b[j] + a[j];
    }
							dummyMethod2();
}


int* prefixSomme(int* inputTable, int inputSize) {

    int* a = etapeZero(inputTable, inputSize);
    int* b = createArray(2 * inputSize);
    int m = log2(inputSize); //input de taille 2^m

    monteeSomme(a, m);
    descenteSomme(a, b, m);
    finaleSomme(a, b, m);

    int* result = retrieveResult(b, inputSize);
    free(a);
    free(b);

    return result;
}

int* suffixSomme(int* inputTable, int inputSize) {
    int* flipped = flipArray(inputTable, inputSize);

    int* result = prefixSomme(flipped, inputSize);

    result = flipArray(result, inputSize);
    free(flipped);

    return result;

}

/* *************Partie Max ********** */

void monteeMax(int* a, int m){

    for (int l = m-1; l >= 0; l--) {
        //pour eviter d'avoir a calculer ça a chaque test de j < end
        int end = pow(2, l+1);
        int x = pow(2,l);
															dummyMethod1();
        #pragma omp parallel for
        for (int j = x; j < end; j++) {
            a[j] = MAX(a[2 * j], a[2 * j + 1]);
	}
															dummyMethod2();
    }
}

void descenteMax(int* a, int* b, int m){

    b[1] = INT_MIN;

    for (int l = 1; l < m; l++) {
        int end = pow(2, l + 1);

															dummyMethod1();
        #pragma omp parallel for
        for (int j = pow(2, l); j < end; j++)
        {
            if (j % 2 == 0) {
                b[j] = b[j / 2];
            }
            else {
                b[j] = MAX(b[j / 2], a[j - 1]);
            }
        }
															dummyMethod2();
    }
}

void finaleMax(int* a, int* b, int m) {
    
    int end = pow(2, m + 1);

							dummyMethod1();
    #pragma omp parallel for
    for (int j = pow(2, m); j < end; j++) {
        b[j] = MAX(b[j], a[j]);
    }
							dummyMethod2();
}


int* prefixMax(int* inputTable, int inputSize) {

    int* a = etapeZero(inputTable, inputSize);
    int* b = createArray(2 * inputSize);
    int m = log2(inputSize); //input de taille 2^m

    monteeMax(a, m);
    descenteMax(a, b, m);
    finaleMax(a, b, m);

    int* result = retrieveResult(b, inputSize);
    free(a);
    free(b);

    return result;
}

int* suffixMax(int* inputTable, int inputSize) {
    int* flipped = flipArray(inputTable, inputSize);

    int* result = prefixMax(flipped, inputSize);

    result = flipArray(result, inputSize);
    free(flipped);

    return result;
}


/* *************Partie Sous Tableau Maximal ********** */

void maxSubTable(int* inputTable, int inputSize, int* psum, int* ssum, int* pmax, int* smax) {

    int* M = createArray(inputSize);

							dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < inputSize; i++) {
        M[i] = pmax[i] - ssum[i] + smax[i] - psum[i] + inputTable[i];
    }
							dummyMethod2();
    

    int maxFound = INT_MIN;
    int seqStart = 0;
    int seqEnd = 0;
    int currentlyInSeq = 1; //booleen

    for (int i = 0; i < inputSize; i++) {
        if (M[i] > maxFound) {
            maxFound = M[i];
            seqStart = i;
            seqEnd = i;
            currentlyInSeq = 1;
        }
        else if ((currentlyInSeq) && (M[i]==maxFound)) {
            seqEnd++;
        }
        else if (M[i] != maxFound) {
            currentlyInSeq = 0;
        }
    }

    printf("%d ", maxFound);
    for (int i = seqStart; i <= seqEnd; i++) {
        printf("%d ", inputTable[i]);
    }
    printf("\n");
    
}

/* *************Partie Main ********** */
int main(int argc, char *argv[]) {
    //Sources pour cette façon de lire un fichier d'entiers:
    //https://stackoverflow.com/questions/4600797/read-int-values-from-a-text-file-in-c
    //https://stackoverflow.com/questions/34745278/how-to-count-the-number-of-integers-in-a-file-in-c
    FILE* file = fopen (argv[1], "r");
    
    // read once to find the number of ints
    int inputSize = 0; //we're going to add a 0 at the start
    int currentInt = 0;
    while(fscanf(file, "%d", &currentInt) == 1) {
        inputSize++;
    }

    // read a second time to put in array
    rewind (file); 
    int* inputTable = createArray(inputSize);
    currentInt = 0; //just in case
    int i = 0;
    while(fscanf(file, "%d", &currentInt) == 1) {
        inputTable[i] = currentInt;
        i++;
    }

    fclose(file);
    
    int* psum = prefixSomme(inputTable, inputSize);
    
    int* ssum = suffixSomme(inputTable, inputSize);
    
    int* smax = suffixMax(psum, inputSize);
       
    int* pmax = prefixMax(ssum, inputSize);
    
    maxSubTable(inputTable, inputSize, psum, ssum, pmax, smax);


    free(inputTable);
    free(psum);
    free(ssum);
    free(smax);
    free(pmax);

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