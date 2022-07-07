#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "distances.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int N, M, P, rank, infinity, *a, *b;
int method = MANHATTAN;
int comFuncNumber = ALLTOALL_COMPRESS;
void (*comFunc) ();

int (*dist)(int, int, int);
int (*sepDist)(int, int, int, int, int);

inline void firstPhase();
inline int secondPhase();

inline void oneAllToAll ();
inline void allToAll ();
inline void scatter ();
inline void allToAllMany ();
inline void allToAllCompress ();


inline void input(char* filename);
inline void output(char* filename, int *array, int max);

int main(int argc, char* argv[]) {
	int flag, i, j;
	double t[7];

	t[0] = MPI_Wtime(); 

	char *inputImg = strdup("inpbm/2048.pbm");
	char *outputImg = strdup("outpgm/2048.pgm");
	
	while ( ( flag = getopt (argc, argv, "m:i:o:c:") ) != -1 ) {
		switch (flag) {
			case 'm':
				method = atoi(optarg);
				break;
			case 'i':
				inputImg = strdup(optarg);
				break;
			case 'o':
				outputImg = strdup(optarg);
				break;
			case 'c':
				comFuncNumber = atoi(optarg);
				break;
			default:
				abort ();
		}
	}
	switch(method) {
		case EUCLIDEAN:
			dist = EDTf;
			sepDist = EDTSep;
			break;
		case MANHATTAN:
			dist = MDTf;
			sepDist = MDTSep;
			break;
		case CHESSBOARD:
			dist = CDTf;
			sepDist = CDTSep;
			break;
		default:
			break;
	}
	switch(comFuncNumber) {
		case ONE_ALLTOALL:
			comFunc = oneAllToAll;
			break;
		case ALLTOALL:
			comFunc = allToAll;
			break;
		case SCATTER:
			comFunc = scatter;
			break;
		case ATA_MANY:
			comFunc = allToAllMany;
			break;
		case ALLTOALL_COMPRESS:
			comFunc = allToAllCompress;
			break;
		default:
			break;
	}

	MPI_Status status;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &P);

	MPI_Barrier(MPI_COMM_WORLD);
	t[1] = MPI_Wtime();

	input(inputImg);
	
	MPI_Barrier(MPI_COMM_WORLD);
	t[2] = MPI_Wtime();

	infinity = M*N;
	firstPhase();

	MPI_Barrier(MPI_COMM_WORLD);
	t[3] = MPI_Wtime();

	comFunc();
	
	MPI_Barrier(MPI_COMM_WORLD);
	t[4] = MPI_Wtime();

	int max = secondPhase ();

	MPI_Barrier(MPI_COMM_WORLD);
	t[5] = MPI_Wtime();


	if(strcmp(outputImg, strdup("none"))) {
		output(outputImg, b, max);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	t[6] = MPI_Wtime();
	
	if (rank==0)
		printf("%lf %lf %lf %lf %lf %lf\n", t[1]-t[0], t[2]-t[1], t[3]-t[2], t[4]-t[3], t[5]-t[4], t[6]-t[5]);
	
	MPI_Finalize();
	return 0;
}

inline void firstPhase() {
	int x, y, m, n;
	m = M/P;
	n = N;

	dummyMethod1();
	#pragma omp parallel for schedule(static)
	for ( x=0; x<m; x++ )
		a[x] = infinity - a[x]*infinity;
	dummyMethod2();

	for ( y=1; y<n; y++ ) {
			dummyMethod1();
		#pragma omp parallel for schedule(static)
		for ( x=0; x<m; x++ ) {
			int aa = a[x+(y-1)*m];
			a[x+y*m] = 1 + aa - a[x+y*m] * ( aa+1 );
		}
			dummyMethod2();
	}

	for ( y=n-2; y>=0; y-- ) {
			dummyMethod1();
		#pragma omp parallel for schedule(static)
		for ( x=0; x<m; x++ ) {
			int b = a[x+(y+1)*m];
			if ( b < a[x+y*m] )
				a[x+y*m] = b+1;
		}
			dummyMethod2();
	}
}

inline int secondPhase() {
	int x, y, n, m, max=0;
	m = M;
	n = N/P;

	dummyMethod1();
	#pragma omp parallel for private(x) schedule(dynamic) reduction(max:max)
	for(y=0; y<n; y++) {
		int q=0;
		int s[m], t[m];
		s[0]=0; t[0]=0;
		for( x=1; x<m; x++ ) {
			while(q >= 0 && ( dist(t[q], s[q], b[s[q]+y*m]) > dist(t[q], x, b[x+y*m]) )){
				q--;
			}
			if(q < 0){
				q = 0; s[0] = x;
			}
			else{
				int w = 1 + sepDist(s[q], x, b[s[q]+y*m], b[x+y*m], infinity);
				if(w < m){
					q++; s[q] = x; t[q] = w;
				}
			}
		}
		for(x = m-1; x >= 0; x--){
			int d = dist(x, s[q], b[s[q]+y*m]);
			if(method == 1)
				d = (int) sqrt((double)d);
			b[y*m+x] = d;
			if (d>max)
				max=d;
			if (x == t[q])
				q--;
		}
	}
	dummyMethod2();
	return max;
}

inline void oneAllToAll() {
	int i,j;
	int blockHeight = N/P; //nº linhas
	int blockWidth = M/P; //nº colunas
	int blockSize = blockWidth*blockHeight; //nº elementos 

	MPI_Datatype aCol, bCol;
	MPI_Datatype aType, bType;

	
	MPI_Type_vector( N/P, 1, M/P, MPI_INT, &aCol );
	
	MPI_Type_commit(&aCol);
	MPI_Type_create_resized(aCol, 0, 1*sizeof(float), &aType);
	MPI_Type_commit(&aType);

	MPI_Type_vector(N/P, 1,	M, MPI_INT, &bCol);	   
	MPI_Type_commit(&bCol);
	MPI_Type_create_resized(bCol, 0, 1*sizeof(int), &bType);
	MPI_Type_commit(&bType);
	
	int *count = (int*) malloc(sizeof(int) * P);
	int *dispA = (int*) malloc(sizeof(int) * P);
	int *dispB = (int*) malloc(sizeof(int) * P);

	for (i=0; i<P; i++) {
		count[i] = blockWidth;
		dispA[i] = blockSize*i;
		dispB[i] = blockWidth*i;
	}

	MPI_Alltoallv(a, count, dispA, aType, b, count, dispB, bType, MPI_COMM_WORLD);
	free(count); free(dispA); free(dispB);
}

inline void allToAll() {
	int i,j;
	int blockHeight = N/P; //nº linhas
	int blockWidth = M/P; //nº colunas
	int blockSize = blockWidth*blockHeight; //nº elementos 

	MPI_Alltoall(a, blockSize, MPI_INT, b, blockSize, MPI_INT, MPI_COMM_WORLD);// Troca os blocos entre processos

	for (i=0; i<P; i++) {
			dummyMethod1();
		#pragma omp parallel for schedule(dynamic)
		for (j=0; j<blockHeight; j++){
			int OffsetDest = ( (j*M) + (i*blockWidth) ); // Calcula onde vai escrever
			int OffsetSrc = ( (i*blockSize) + (j*blockWidth) ); // Calcula onde vai ler
			memcpy ( a+OffsetDest, b+OffsetSrc, blockWidth *sizeof(int) ); // Transfere para o sitio pretendido
		}
			dummyMethod2();
	}
	free(b); b=a; // Mantém os dados na variável b
}

inline void allToAllCompress() {
	int i,j;
	int blockHeight = N/P; //nº linhas
	int blockWidth = M/P; //nº colunas
	int blockSize = blockWidth*blockHeight; //nº elementos

	int *count = (int*) malloc(sizeof(int) * P);
	int *disp = (int*) malloc(sizeof(int) * P);
	int *dictSize = (int*) malloc(sizeof(int) * P);
	int *max = (int*) calloc(P ,sizeof(int));

	int *dataSend = (int*) calloc(P*3, sizeof(int));
	int *dataRecv = (int*) calloc(P*3, sizeof(int));

	dummyMethod1();
	#pragma omp parallel for private(j) schedule(dynamic)
	for (i=0; i<P; i++) {
		//find block max
		for (j=i*blockSize; j<(i+1)*blockSize; j++)
			if (a[j]>max[i]) max[i]=a[j];

		//compress block a[i] to b[i]
		compress( b+(i*blockSize), a+(i*blockSize), count+i, dictSize+i, blockSize, max[i] );

		// Espaçamento de i blocos - fica em branco o que não interessa
		disp[i] = blockSize*i;

		dataSend[i*3] = dictSize[i];// tamanho dicionario
		dataSend[i*3+1] = count[i];// tamanho comprimido
		dataSend[i*3+2] = max[i];// valor maximo antes da compressao
	}
	dummyMethod2();

	// alltoall do count dictSize e max
	MPI_Alltoall(dataSend, 3, MPI_INT, dataRecv, 3, MPI_INT, MPI_COMM_WORLD);

	int pos=0;
	for (i=1; i<3*P; i+=3) {
		max[pos++] = dataRecv[i];
	}

	// b is compressed, send b to a
	MPI_Alltoallv(b, count, disp, MPI_INT, a, max, disp, MPI_INT, MPI_COMM_WORLD);// Troca os blocos entre processos

	// a is compressed, uncompress to b
	dummyMethod1();
	#pragma omp parallel for schedule(dynamic)
	for (i=0; i<P; i++)
		uncompress ( b+(i*blockSize), a+(i*blockSize), dataRecv[3*i], dataRecv[3*i+1], dataRecv[3*i+2] );
	dummyMethod2();
	
	// swap from b to a
	for (i=0; i<P; i++) {
			dummyMethod1();
		#pragma omp parallel for schedule(static)
		for (j=0; j<blockHeight; j++) {
			int OffsetDest = ( (j*M) + (i*blockWidth) ); // Calcula onde vai escrever
			int OffsetSrc = ( (i*blockSize) + (j*blockWidth) ); // Calcula onde vai ler
			memcpy ( a+OffsetDest, b+OffsetSrc, blockWidth *sizeof(int) ); // Transfere para o sitio pretendido
		}
			dummyMethod2();
	}
	free(b); b=a; // Mantém os dados na variável b
	free(count); free(disp); free(dictSize); free(max); free(dataSend); free(dataRecv);
}

inline void scatter() {
	int i;
	int blockHeight = N/P; //nº linhas
	int blockWidth = M/P; //nº colunas
	int blockSize = blockWidth*blockHeight; //nº elementos
	int stride = M; //largura matriz

	MPI_Datatype block;
	MPI_Type_vector(blockHeight, blockWidth, stride, MPI_INT, &block);
	MPI_Type_commit(&block);
	
	for (i=0; i<P; i++)
		MPI_Scatter(a, blockHeight*blockWidth, MPI_INT, b+(i*(M/P)), 1, block, i, MPI_COMM_WORLD);
}

inline void allToAllMany() {
	int i,j;
	/*
	Podem ser arrays na stack???
	*/
	int *buffSize = (int*) malloc(sizeof(int)*P);
	int *dispA = (int*) malloc(sizeof(int)*P);
	int *dispB =  (int*) malloc(sizeof(int)*P);
	
	for (i=0; i<N/P; i++) {

		for (j=0; j<P; j++){
			buffSize[j] = M/P; // Largura da coluna
			dispA[j] = (M/P)*(N/P)*j + (M/P)*i; // Lê do bloco j, linha i
			dispB[j] = M*i + (M/P)*j; // Escreve no "bloco" i, linha j ( nº "blocos" = nº linhas por bloco)
		}
		
		MPI_Alltoallv(a, buffSize, dispA, MPI_INT, b, buffSize, dispB, MPI_INT, MPI_COMM_WORLD);
	}
	free(buffSize);
	free(dispA);
	free(dispB);
}

inline void input(char* filename) {
 	MPI_Offset offset;
	MPI_File file;
	MPI_Status status;
	int i, j, chunkWidth, readHeadLn;

 	int dims[3];
 	if (rank==0) {
	 	char buf[256];
		FILE *fp = fopen(filename, "rb");
		if(!fp){
			printf("ESCAXOU LARGO\n");
			return;
		}
		dims[2]=3;
		if( fgets(buf, 256, fp) && fgets(buf, 256, fp) )
			sscanf(buf, "%u %u", dims, dims+1);
		dims[2]+=strlen(buf);	
		fclose(fp);
	}

	MPI_Bcast(dims, 3, MPI_INT, 0, MPI_COMM_WORLD );

	M = dims[0];
	N = dims[1];
	readHeadLn = dims[2];

	a = (int*) malloc( (N*M)/P *sizeof(int) );
	b = (int*) malloc( (N*M)/P *sizeof(int) );

	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY, MPI_INFO_NULL, &file);

	chunkWidth = 2*M/P;
	char* buf=(char*)malloc(chunkWidth*N + 1);

	MPI_Datatype filetype;
	MPI_Type_vector(N, chunkWidth, 2*M, MPI_CHAR, &filetype);
	MPI_Type_commit(&filetype);
	MPI_File_set_view(file, chunkWidth*sizeof(char)*rank + readHeadLn, MPI_CHAR, filetype,"native", MPI_INFO_NULL);
	MPI_File_read_all(file, buf, chunkWidth*N, MPI_CHAR, &status);
	buf[chunkWidth*N]='\0';

	int pos=0;
	for (i=0; i<=N*M/P; i++) {
		a[i] = buf[pos] -'0';
		pos+=2;
	}
	MPI_File_close(&file);
	free(buf);
}

inline void output(char* filename, int *array, int max) {
	MPI_Offset offset;
	MPI_File file;
	MPI_Status status;
	int chunksize, startingpos, *buf, headerlength, i, j, globalmax; 
	char header[64];
	unsigned char *array2;

	sprintf(header, "P5\n%d %d\n%d\n", M, N, 255);
	headerlength = strlen(header);
	
	chunksize = (N*M)/P;
	startingpos = chunksize * rank;

	offset = 1 * startingpos;
	offset += headerlength;

	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &file);

	if(rank==0){
		MPI_File_seek(file, 0, MPI_SEEK_SET);
		MPI_File_write(file, header, headerlength, MPI_CHAR, &status);
	}

	MPI_Allreduce(&max, &globalmax, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

	array2 = (unsigned char*) malloc((N*M)/P);

	for(i=0; i<N; i++){
		for(j=0; j<M/P; j++){
			array2[i*(M/P) + j] = (unsigned char)(array[i*(M/P) + j]*255/globalmax);
		}
	}

	MPI_File_seek(file, offset, MPI_SEEK_SET);
	MPI_File_write_all(file, array2, chunksize, MPI_CHAR, &status);
	MPI_File_close(&file);
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