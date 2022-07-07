#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

/*
Funcion que asigna memoria para una matriz de floats
Entrada: Alto y ancho de la matriz
Salida: Punteor a la matriz
*/
float** createMatrix(int width, int heigth){
    float** matrix = (float**)malloc(sizeof(float*)*heigth);
    if(matrix==NULL){
        printf("No se pudo asignar memoria\n");
        return NULL;
    }
    int i;
dummyMethod3();
    for(i = 0; i<heigth;i++){
        matrix[i] = (float*)malloc(sizeof(float)*width);
        if(matrix[i]==NULL){
            printf("No se pudo asignar memoria\n");
            return NULL;
        }
    }
dummyMethod4();
    return matrix;
}

/*
Crea archivo de salida con la matriz de los valores obtenidos del algoritmo
de mandelbrot
Entrada: Nombre del archivo, matriz, ancho y alto
Salida: void
*/
void createFile(char nombre[128],float** imagen, int width, int heigth){
    FILE* f = fopen(nombre, "wb");

    if(f==NULL){
        printf("No se pudo crear el archivo\n");
        return;
    }
    int i;

							dummyMethod3();
    for(i = 0; i < heigth; i++){
        fwrite(imagen[i],sizeof(float),width,f);
        
    }
							dummyMethod4();
    fclose(f);
    printf("Archivo %s escrito exitosamente\n",nombre);
}

/*
Implementa el algoritmo para encontrar los numeros de mandelbrot de forma paralela
Entrada: limite inferior y superior complejo, limite inferior y superior real, 
profundidad, tasa de muestreo, alto y ancho de la matriz, cantidad de hebras
Salida: Matriz con los valores obtenidos del algoritmo
*/
float** mandelbrot(float infRe, float supRe, float infIm, float supIm, int depth, float sampRate, int width, int heigth, int cantHebras){
    omp_set_num_threads(cantHebras);
    int i,j,n;
    float z0Re,z0Im,znRe,znIm,cRe,cIm,auxIm;
    float** matrix = createMatrix(width,heigth);
    if(matrix==NULL){
        return NULL;
    }
							dummyMethod1();
    #pragma omp parallel for shared(infRe, supRe, infIm, supIm, sampRate, width, heigth) private(j, n, z0Re, z0Im, znRe, znIm, cRe, cIm, auxIm)
    for(i = 0; i < heigth;i++){
        for(j = 0; j < width;j++){
            cRe = i*sampRate + infRe;
            cIm = j*sampRate + infIm;
            z0Re = 0;
            z0Im = 0;
            n = 0;
            znRe = z0Re + cRe;
            znIm = z0Im + cIm;
            while(sqrt(znRe*znRe + znIm*znIm) < 2 && n < depth){
                auxIm = 2*znRe*znIm + cIm;
                znRe = (znRe*znRe)-(znIm*znIm) + cRe;
                znIm = auxIm;
                n++;
            }
            matrix[i][j] = log(n)+1;
        }
    }
							dummyMethod2();
    return matrix;
}



int main(int argc, char **argv){
    float infRe = -1;
    float supRe = 1;
    float infIm = -1;
    float supIm = 1;
    int depth = 500;
    float sampRate = 0.001;
    char* sName = NULL;
    int cantHebras = 1;
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "i:a:b:c:d:s:f:t:")) != -1)
        switch (c)
        {
        case 'i':
            sscanf(optarg, "%d", &depth);
            break;
        case 'a':
            sscanf(optarg, "%f", &infRe);
            break;
        case 'b':
            sscanf(optarg, "%f", &infIm);
            break;
        case 'c':
            sscanf(optarg, "%f", &supRe);
			break;
        case 'd':
            sscanf(optarg, "%f", &supIm);
			break;
        case 's':
            sscanf(optarg, "%f", &sampRate);
			break;
        case 'f':
            sName = optarg;
			break;
        case 't':
            sscanf(optarg, "%d", &cantHebras);
			break;
        case ':':
            printf("Opcion necesita un valor\n");
            break;
        case '?':
            if (optopt == 'i' || optopt == 'a' || optopt == 'b' || optopt == 'c' || optopt == 'd' || optopt == 's' || optopt == 'f' || optopt == 't')
            fprintf (stderr, "Opcion -%c requiere un argumento\n", optopt);
            else if (isprint (optopt))
            fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
            else
            fprintf (stderr,
                    "Caracter desconocido`\\x%x'.\n",
                    optopt);
            return 1;
        default:
            abort ();
        }

							dummyMethod3();
    for (index = optind; index < argc; index++){
        printf ("Argumento sin opcion %s\n", argv[index]); 
        
    }
							dummyMethod4();

    printf("i: %d a: %f b: %f c: %f d: %f s: %f f: %s t:%d\n",depth,infRe,infIm,supRe,supIm,sampRate,sName,cantHebras);

    int width = round((supRe-infRe)/sampRate);
    int heigth = round((supIm-infIm)/sampRate);
    printf("width: %d heigth: %d\n",width,heigth);
    float** matrix = mandelbrot(infRe,supRe,infIm,supIm,depth,sampRate,width,heigth,cantHebras);
    createFile(sName,matrix,width,heigth);


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