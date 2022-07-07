//mpicc -o ex0 dna.c -fopenmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "mpi.h"
#include "omp.h"

#define TAM 1024 * 1024 * 1024

int NUMTHREAD;

//int qnt[24];
char comb[24][5];
int maiores[5];
//int nOpenMP;
//int quantidade2[5];

int *topDown(int start);
int *topDown2(int start, int maiores[]);
void swap();
void gerar();
void MostraMaiores(int a[], int t);

int main(int argc, char *argv[])
{

    int qnt[24];
    int quant[24];
    int quantmaior[5];
    int qntmaior[5];
    int i;
							dummyMethod3();
    for (i = 0; i < 5; i++)
    {
        maiores[i] = 0;
        quantmaior[i] = 0;
        qntmaior[i] = 0;
    }
							dummyMethod4();
							dummyMethod3();
    for (i = 0; i < 24; i++)
    {
        quant[i] = 0;
        qnt[i] = 0;
    }
							dummyMethod4();
    //se n�o for informado o N de Threads cria s� 1
    // NUMTHREAD = 1;

    // if (argv[1] > 0)
    // {
    //     NUMTHREAD = atoi(argv[1]);
    // }

    // printf("criando %d Threads \n \n",NUMTHREAD);

    char str[] = "AGTC";
    int n = strlen(str);
    int j = 0;
    gerar(str, 0, (n - 1));

    int myid, numprocs;
    MPI_Status status;
    int offset;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    offset = TAM / (numprocs - 1);
    NUMTHREAD = numprocs - 1;
    if (myid == 0)
    {
        //printf("Numero de threads no OPENMP\n");
        //scanf("%d",&nOpenMP);
        //printf("%d\n", nOpenMP);
        //for(i=1;i< numprocs;i++){
        //MPI_Send(&nOpenMP, 1, MPI_INT, i, 4, MPI_COMM_WORLD);
        // }
															dummyMethod3();
        for (i = 1; i < numprocs; i++)
        {
            MPI_Recv(&quant, 24, MPI_INT, i, 4, MPI_COMM_WORLD, &status);

            int y;
            for (y = 0; y < 24; y++)
            {
                int f = 0;
                f = *((int *)quant + y);
                qnt[y] = qnt[y] + f;
            }
        }
															dummyMethod4();

        MostraMaiores(qnt, 24);
															dummyMethod3();
        for (i = 1; i < numprocs; i++)
        {
            MPI_Send(maiores, 5, MPI_INT, i, 4, MPI_COMM_WORLD);
        }
															dummyMethod4();

															dummyMethod3();
        for (i = 1; i < numprocs; i++)
        {
            MPI_Recv(&quantmaior, 5, MPI_INT, i, 4, MPI_COMM_WORLD, &status);

            int y;
            for (y = 0; y < 5; y++)
            {
                int f = 0;
                f = *((int *)quantmaior + y);
                qntmaior[y] = f + qntmaior[y];
            }
        }
															dummyMethod4();

															dummyMethod3();
        for (j = 0; j < 5; j++)
        {
            printf("\n Sequencia %s quantidade dna1 %d quantidade dna2 %d\n", comb[maiores[j]], qnt[maiores[j]], qntmaior[j]);
        }
															dummyMethod4();
        printf("\n\n\n############\n\n\n");
    }
    else
    {

        //int nummp;
        //MPI_Recv(&nummp, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
        //nOpenMP = nummp;
        int *quan;

        int *quan1;

        int x = offset * (myid - 1);

        quan = topDown(x);

        MPI_Send(quan, 24, MPI_INT, 0, 4, MPI_COMM_WORLD);

        int biggest[5];

        MPI_Recv(&biggest, 5, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);

        quan1 = topDown2(x, biggest);
        MPI_Send(quan1, 5, MPI_INT, 0, 4, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

int *topDown(int start)
{

    int p = start;
    int num = 0;
    FILE *file;
    FILE *file2;

    file = fopen("DNA1.txt", "r");

    file2 = fopen("DNA2.txt", "r");

    int num1, qnt1[24];
    char c, c1, buf[4], buf1[4];

    static int quantidade[24];

    fseek(file, p, SEEK_SET);
    int j = 0;

							dummyMethod3();
    for (j = 0; j < 24; j++)
    {
        qnt1[j] = 0;
    }
							dummyMethod4();

    c = getc(file);
    buf[0] = c;

    c = getc(file);
    buf[1] = c;

    c = getc(file);
    buf[2] = c;

    int i;
    int x = p;

    //omp_set_num_threads (nOpenMP);
    //printf("%d\n", nOpenMP);
    //#pragma omp parallel private(c,num1,buf,i,x)
    //{

    //int id = omp_get_thread_num();
    //int NThread = omp_get_num_threads();
    //int x = id* ((TAM/NUMTHREAD)/NThread)+p;
    //int end = (id+1)* ((TAM/NUMTHREAD)/NThread)+p;
    //if (id==NThread-1){
    //    end=(TAM/NUMTHREAD+p);
    //}
    //printf("\n");
							dummyMethod1();
#pragma omp parallel for private(x, buf, c, i) shared(file)
    for (i = 0; i < 24; i++)
    {
        x = p;
        fseek(file, p, SEEK_SET);
        while (x < ((TAM / NUMTHREAD) + p) && ((c = getc(file)) != EOF))
        {

            buf[3] = c;

            if ((comb[i][0] == buf[0]) && (comb[i][1] == buf[1]) && (comb[i][2] == buf[2]) && (comb[i][3] == buf[3]))
            {
                num1 = num1 + 1;
                qnt1[i] = qnt1[i] + 1;

                //if (count == 3){printf("\n"); count =0;}
                //printf("|  %d Achou %s na posicao %d ",omp_get_thread_num(), comb[i], x); //PRA TESTAR QUAL THREAD ACHOU A COMB
            }

            buf[0] = buf[1];
            buf[1] = buf[2];
            buf[2] = buf[3];
            x++;
        }
        //#pragma omp taskwait
        num = num + num1;
    }
							dummyMethod2();

							dummyMethod3();
    for (i = 0; i < 24; i++)
    {
        quantidade[i] = quantidade[i] + qnt1[i];
    }
							dummyMethod4();
    fclose(file);
    fclose(file2);
    return quantidade;
}

int *topDown2(int start, int maiores[])
{

    int p = start;

    FILE *file;
    file = fopen("DNA2.txt", "r");

    int i, j, num1, qnt1[5];
    static int quantidade1[5];

							dummyMethod3();
    for (j = 0; j < 5; j++)
    {
        qnt1[j] = 0;
    }
							dummyMethod4();

    char c, buf[4];

    fseek(file, p, SEEK_SET);

    c = getc(file);
    buf[0] = c;

    c = getc(file);
    buf[1] = c;

    c = getc(file);
    buf[2] = c;

    int x = p;

    //omp_set_num_threads (nOpenMP);

    //#pragma omp parallel private(c,num1,buf,i)
    //{
    // count pra aquela parte de baixo la que mostra e pa

    //  int id = omp_get_thread_num();
    // int NThread = omp_get_num_threads();
    //  int x = id* ((TAM/NUMTHREAD)/NThread)+p;
    //  int end = (id+1)* ((TAM/NUMTHREAD)/NThread)+p;
    //  if (id==NThread-1){
    //     end=(TAM/NUMTHREAD+p);
    // }
    // printf("\n");

							dummyMethod1();
#pragma omp parallel for private(x, buf, c, i) shared(file)
    for (i = 0; i < 5; i++)
    {
        x = p;
        fseek(file, p, SEEK_SET);
        while (x < ((TAM / NUMTHREAD) + p) && ((c = getc(file)) != EOF))
        {
            buf[3] = c;

            if ((comb[maiores[i]][0] == buf[0]) && (comb[maiores[i]][1] == buf[1]) && (comb[maiores[i]][2] == buf[2]) && (comb[maiores[i]][3] == buf[3]))
            {

                qnt1[i] = qnt1[i] + 1;
            }

            buf[0] = buf[1];
            buf[1] = buf[2];
            buf[2] = buf[3];
            x++;
        }
    }
							dummyMethod2();
							dummyMethod3();
    for (i = 0; i < 5; i++)
    {

        quantidade1[i] = quantidade1[i] + qnt1[i];
    }
							dummyMethod4();
    fclose(file);
    return quantidade1;
}

void gerar(char *a, int l, int r)
{
    int i;
    static int k;
    if (l == r)
    {
        strcpy(comb[k++], a);
    }
    else
    {
															dummyMethod3();
        for (i = l; i <= r; i++)
        {
            swap((a + l), (a + i));
            gerar(a, l + 1, r);
            swap((a + l), (a + i));
        }
															dummyMethod4();
    }
}

void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

//mostra os maiores
void MostraMaiores(int a[], int t)
{
    int i, y, y2, y3, y4, y5, x1, x2, x3, x4, x5;

    x1 = x2 = x3 = x4 = x5 = y4 = y3 = y = y2 = y5 = 0;
							dummyMethod3();
    for (i = 0; i < 24; i++)
    {
        if (a[i] > y)
        {
            y5 = y4;
            x5 = x4;
            y4 = y3;
            x4 = x3;
            y3 = y2;
            x3 = x2;
            y2 = y;
            x2 = x1;
            y = a[i];
            x1 = i;
        }
        else if (a[i] > y2)
        {
            y5 = y4;
            x5 = x4;
            y4 = y3;
            x4 = x3;
            y3 = y2;
            x3 = x2;
            y2 = a[i];
            x2 = i;
        }
        else if (a[i] > y3)
        {
            y5 = y4;
            x5 = x4;
            y4 = y3;
            x4 = x3;
            y3 = a[i];
            x3 = i;
        }
        else if (a[i] > y4)
        {
            y5 = y4;
            x5 = x4;
            y4 = a[i];
            x4 = i;
        }
        else if (a[i] > y5)
        {
            y5 = a[i];
            x5 = i;
        }
    }
							dummyMethod4();
    maiores[0] = x1;
    maiores[1] = x2;
    maiores[2] = x3;
    maiores[3] = x4;
    maiores[4] = x5;

    printf("5 maiores s�o %s %s %s %s %s\n", comb[x1], comb[x2], comb[x3], comb[x4], comb[x5]);
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