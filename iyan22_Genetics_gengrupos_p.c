/**********************************************************************************************************
 *                              AC - OpenMP -- PARALELA                                                   *
 *                  Compilar con el modulo fun_p.c y la opcion -lm                                        *
 *                                  gengrupos_s.c                                                         *
 *                                                                                                        *
 *      Entrada: dbgen.dat    fichero con la informacion vserie de cada muestra                           *
 *               dbenf.dat    fichero con la informacion sobre las enfermedades de cada muestra           *
 *      Salida:  dbgen_s.out  centroides, densidad, analisis                                              *
 **********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "defineg.h"
#include "fun.h"

float  elem[MAXE][NCAR];               // Elementos (muestras) a procesar
struct lista_grupos listag[NGRUPOS];   // Lista de elementos de los grupos

float  enf[MAXE][TENF];                // Enfermedades asociadas a las muestras
struct  analisis prob_enf[TENF];       // Analisis de los tipos de enfermedades


// Programa principal
int main (int argc, char *argv[]) {
    float   cent[NGRUPOS][NCAR], newcent[NGRUPOS][NCAR];    // Centroides
    float   densidad[NGRUPOS];	                            // Densidad de cada cluster

    int     popul[MAXE];                                    // Grupo de cada elemento
    double  additions[NGRUPOS][NCAR+1];

    int     i, j, nelem, grupo, num;
    int     fin = 0, num_ite = 0;
    double  discent;

    FILE   *fd;
    struct timespec  t1, t2, t3;
    double tlec, tclu, tord, tden, tenf, tesc, texe;

    if ((argc < 3)  || (argc > 4)) {
        printf("ERROR:  gengrupos bd_muestras bd_enfermedades [num_elem]\n");
        exit(-1);
    }

    printf("\n >> Ejecucion paralela\n");

    // Tiempo de inicio del programa
    clock_gettime(CLOCK_REALTIME, &t1);


    // Lectura de datos (muestras): elem[i][j]

    // Tiempo de inicio de lectura
    clock_gettime(CLOCK_REALTIME, &t2);

    fd = fopen(argv[1], "r");
    if (fd == NULL) {
        printf("Error al abrir el fichero %s\n", argv[1]);
        exit(-1);
    }

    // 4. parametro: Numero de elementos
    fscanf(fd, "%d", &nelem);
    if (argc == 4) {
        nelem = atoi(argv[3]);
    }

    // EXPLICACION
    // No se puede paralelizar el escaneo de un fichero, ya que a medida que el for va iterando, se van leyendo los nelem
    // elementos. No hay forma de acceder a los datos del fichero en forma de ??ndices, por lo que no se puede dividir la
    // carga de trabajo de este for.
							dummyMethod3();
    for (i = 0; i < nelem; i++) {
        for (j = 0; j < NCAR; j++) {
            fscanf(fd, "%f", &(elem[i][j]));
        }
    }
							dummyMethod4();

    fclose(fd);


    // Lectura de datos (enfermedades): enf[i][j]
    fd = fopen (argv[2], "r");
    if (fd == NULL) {
        printf("Error al abrir el fichero %s\n", argv[2]);
        exit(-1);
    }

    // EXPLICACION
    // No se puede paralelizar el escaneo de un fichero, ya que a medida que el for va iterando, se van leyendo los nelem
    // elementos. No hay forma de acceder a los datos del fichero en forma de ??ndices, por lo que no se puede dividir la
    // carga de trabajo de este for.
							dummyMethod3();
    for (i = 0; i < nelem; i++) {
        for (j = 0; j < TENF; j++)
            fscanf(fd, "%f", &(enf[i][j]));
    }
							dummyMethod4();
    fclose(fd);

    // Tiempo de finalizaci??n de lectura y c??lculo
    clock_gettime (CLOCK_REALTIME, &t3);
    tlec = (t3.tv_sec-t2.tv_sec) + (t3.tv_nsec-t2.tv_nsec)/(double)1e9;

    // Tiempo de inicio de clustering
    clock_gettime (CLOCK_REALTIME, &t2);
    // Generacion de los primeros centroides de forma aleatoria
    srand (147);
							dummyMethod3();
    for (i = 0; i < NGRUPOS; i++) {
        for (j = 0; j < NCAR / 2; j++) {
            cent[i][j] = (rand() % 10000) / 100.0;
            cent[i][j + (NCAR / 2)] = cent[i][j];
        }
    }
							dummyMethod4();


    // 1. fase: Clasificar los elementos y calcular los nuevos centroides
    num_ite = 0; fin = 0;
    while ((fin == 0) && (num_ite < MAXIT)) {
        // Calcular el grupo mas cercano
        grupo_cercano (nelem, elem, cent, popul);

#pragma omp parallel num_threads(32)
        {
            // Calcular los nuevos centroides de los grupos
            // Media de cada caracteristica
            // Acumular los valores de cada caracteristica (100); numero de elementos al final
#pragma omp for private(i, j)  schedule(dynamic,2)
																							dummyMethod3();
            for (i = 0; i < NGRUPOS; i++) {
                for (j = 0; j < NCAR + 1; j++) {
                    additions[i][j] = 0.0;
                }
            }
																							dummyMethod4();

#pragma omp single
            {
																															dummyMethod3();
                for (i = 0; i < nelem; i++) {
                    for (j = 0; j < NCAR; j++) {
                        additions[popul[i]][j] += elem[i][j];
                    }
                    additions[popul[i]][NCAR]++;
                }
																															dummyMethod4();

                fin = 1;
            }
            // Calcular los nuevos centroides y decidir si el proceso ha finalizado o no (en funcion de DELTA)
#pragma omp for private(i, j, discent) schedule(dynamic,2)
																							dummyMethod3();
            for (i = 0; i < NGRUPOS; i++) {
                // Ese grupo (cluster) no esta vacio
                if (additions[i][NCAR] > 0) {
                    for (j = 0; j < NCAR; j++) {
                        newcent[i][j] = additions[i][j] / additions[i][NCAR];
                    }

                    // Decidir si el proceso ha finalizado
                    discent = gendist (&newcent[i][0], &cent[i][0]);
                    // En alguna centroide hay cambios; continuar
                    if (discent > DELTA) {
                        fin = 0;
                    }

                    // Copiar los nuevos centroides
                    for (j = 0; j < NCAR; j++) {
                        cent[i][j] = newcent[i][j];
                    }
                }
            }
																							dummyMethod4();
#pragma omp single
            {
                num_ite++;
            }
        }
    } // while

    // Tiempo de finalizaci??n de clustering y c??lculo
    clock_gettime(CLOCK_REALTIME, &t3);
    tclu = (t3.tv_sec-t2.tv_sec) + (t3.tv_nsec-t2.tv_nsec)/(double)1e9;



    // 2. fase: Numero de elementos de cada grupo; densidad; analisis enfermedades
    // Tiempo de inicio de ordenacion
    clock_gettime(CLOCK_REALTIME, &t2);
							dummyMethod1();
#pragma omp parallel for private(i) schedule(static,2) num_threads(8)
    for (i = 0; i < NGRUPOS; i++) {
        listag[i].nelemg = 0;
    }
							dummyMethod2();

    // Numero de elementos y su clasificacion
    // EXPLICACION
    // Debido a las dependencias sucesivas entre todos los elementos del for, no es posible paralelizarlo ya que tendr??amos
    // que utilizar diversas secciones cr??tcas.
							dummyMethod3();
    for (i = 0; i < nelem; i++) {
        grupo = popul[i];
        num = listag[grupo].nelemg;
        listag[grupo].elemg[num] = i;	// Elementos de cada grupo (cluster)
        listag[grupo].nelemg++;
    }
							dummyMethod4();

    // Tiempo de finalizaci??n de ordenaci??n y c??lculo
    clock_gettime(CLOCK_REALTIME, &t3);
    tord = (t3.tv_sec-t2.tv_sec) + (t3.tv_nsec-t2.tv_nsec)/(double)1e9;

    // Densidad de cada cluster: media de las distancias entre todos los elementos
    // Tiempo de inicio de densidad
    clock_gettime(CLOCK_REALTIME, &t2);
    calcular_densidad (elem, listag, densidad);
    // Tiempo de finalizaci??n de densidad y c??lculo
    clock_gettime(CLOCK_REALTIME, &t3);
    tden = (t3.tv_sec-t2.tv_sec) + (t3.tv_nsec-t2.tv_nsec)/(double)1e9;

    // Analisis de enfermedades
    // Tiempo de inicio de enfermedades
    clock_gettime(CLOCK_REALTIME, &t2);
    analizar_enfermedades (listag, enf, prob_enf);
    // Tiempo de finalizaci??n de enfermedades y c??lculo
    clock_gettime(CLOCK_REALTIME, &t3);
    tenf = (t3.tv_sec-t2.tv_sec) + (t3.tv_nsec-t2.tv_nsec)/(double)1e9;

    // Escritura de resultados en el fichero de salida

    // Tiempo de inicio de escritura
    clock_gettime(CLOCK_REALTIME, &t2);
    fd = fopen ("dbgen_p.out", "w");
    if (fd == NULL) {
        printf ("Error al abrir el fichero dbgen_p.out\n");
        exit (-1);
    }

    fprintf (fd,">> Centroides de los clusters\n\n");
							dummyMethod3();
    for (i=0; i<NGRUPOS; i++) {
        for (j=0; j<NCAR; j++) fprintf (fd, "%7.3f", cent[i][j]);
        fprintf (fd,"\n");
    }
							dummyMethod4();

    fprintf (fd,"\n\n>> Numero de elementos de cada cluster y densidad del cluster\n\n");
							dummyMethod3();
    for (i=0; i<NGRUPOS; i++) {
        fprintf(fd, " %6d  %.3f \n", listag[i].nelemg, densidad[i]);
    }
							dummyMethod4();

    fprintf (fd,"\n\n>> Analisis de enfermedades en los grupos\n\n");
							dummyMethod3();
    for (i=0; i<TENF; i++) {
        fprintf(fd, "Enfermedad: %2d - max: %4.2f (grupo %2d) - min: %4.2f (grupo %2d)\n",
                i, prob_enf[i].max, prob_enf[i].gmax, prob_enf[i].min, prob_enf[i].gmin);
    }
							dummyMethod4();

    fclose (fd);
    // Tiempo de finalizaci??n de escritura, total y c??lculos
    clock_gettime(CLOCK_REALTIME, &t3);
    tenf = (t3.tv_sec-t2.tv_sec) + (t3.tv_nsec-t2.tv_nsec)/(double)1e9;
    texe = (t3.tv_sec-t1.tv_sec) + (t3.tv_nsec-t1.tv_nsec)/(double)1e9;



    // Mostrar por pantalla algunos resultados
    printf ("\n>> Centroides 0, 40 y 80, y su valor de densidad\n ");
							dummyMethod3();
    for (i = 0; i < NGRUPOS; i+=40) {
        printf("\n  cent%2d -- ", i);
        for (j = 0; j < NCAR; j++) {
            printf("%5.1f", cent[i][j]);
        }
        printf("\n          %5.6f\n", densidad[i]);
    }
							dummyMethod4();

    printf("\n>> Tamano de los grupos \n");
							dummyMethod3();
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%7d", listag[10*i+j].nelemg);
        }
        printf("\n");
    }
							dummyMethod4();

    printf ("\n>> Analisis de enfermedades en los grupos\n");
							dummyMethod3();
    for (i = 0; i < TENF; i++) {
        printf("Enfermedad: %2d - max: %4.2f (grupo %2d) - min: %4.2f (grupo %2d)\n",
               i, prob_enf[i].max, prob_enf[i].gmax, prob_enf[i].min, prob_enf[i].gmin);
    }
							dummyMethod4();
    printf ("\n >> Numero de iteraciones: %d\n", num_ite);
    printf ("\n >> Tiempos de ejecuci??n: ");
    printf ("\n    - Lectura: %11.3f s", tlec);
    printf ("\n    - Clustering: %8.3f s", tclu);
    printf ("\n    - Ordenaci??n: %8.3f s", tord);
    printf ("\n    - Densidad: %10.3f s", tden);
    printf ("\n    - Enfermedades: %6.3f s", tenf);
    printf ("\n    - Escritura: %9.3f s", tesc);
    printf ("\n    - Total: %13.3f s\n\n", texe);

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