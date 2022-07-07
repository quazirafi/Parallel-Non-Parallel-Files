/**

Apostolou Orestis
Aristotle University of Thessaloniki
Electrical Engineering Department
Parallel and Distributed Systems
AEM: 8587
August 2018
orestisapostolou@yahoo.gr

**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct timeval startwtime_p, endwtime_p,startwtime_g, endwtime_g, startresttime, endresttime;
double seq_time_p,seq_time_g, rest_time;

void printMatrix(int a, int b, double **matrix);
double **multiplyMatrix(int a, int b, int c, double **A, double **B, double **C);
void printSquareMatrix(int N, double **matrix);
double **multiplySquareMatrix(int N, double **A, double **B, double **C);
double **randomStochasticMatrix(int N, double **M);
double **randomStochasticSparseMatrix(int N, int percentage, double **M);
double **randomStochasticPropMatrix(int N,double *propArray, double **M);
double **randomStochasticPropMatrix2(int N,double *propArray, double **M);
double norm(double **a, double **b, int N, int grade);
int norm2(double **a, double **b, int N, double e);
int propabilityFunction(int percentage);
void checkSumOfV(int N, double e, double **v);
double *propMatrix(int N,double * matrix);
int norm3(double *a, double *b, int N, double e);
void checkResults(int N, double **v, double *R, double e);

int main(int argc, char **argv){
	if (1==argc){
		printf("Usage: %s, N, d, e, (p) where N is the number of the elements of the web,\nd is the dumping factor x0.01, e is the convergence factor x10^(-12)\n and p is the number of desired threads",argv[0]);
		printf("If no p is provided, it will be assumed that p is the number of proccessors\n");
		printf("The current is a test mode with parameters 10000, 80, 1000\n");

	}
	else if ((argc!=4) && (argc!=5)){
		printf("Usage: %s, N, d, e, where N is the number of the elements of the web,\nd is the dumping factor x0.01, e is the convergence factor x10^(-12)\n and p is the number of desired threads",argv[0]);
		printf("If no p is provided, it will be assumed that p is the number of proccessors\n");
		exit(1);
	}
	//         INITIALIZE VARIABLES         //

	gettimeofday (&startresttime, NULL);
	srand(time(NULL));
	int N,i,j,tempSum,iterations_p,iterations_g, flagNorm, p;
	int convergedFlag=0, sign=1;
	double **M, **M_hat, **v, **last_v, **vtemp, **E, *propM, *R, *last_R, *t;
	double e, d, factor;
	double tempV=0;
	if (argc>3){
		N=atoi(argv[1]);
		d=atoi(argv[2])*0.01;
		e=atoi(argv[3])*0.000000000001;
	}
	else{
		N=10000;
		d=0.8;
		e=0.000000000001*1000;
	}
	if (5==argc){
		p=atoi(argv[4]);
		omp_set_num_threads(p);
	}

	//           END OF VARIABLES' INITIALIZATION      //


	//           DEFINE MATRIXES            //

	M=malloc(N*sizeof *M);
	M_hat=malloc(N*sizeof *M_hat);
	E=malloc(N*sizeof *E);
	v=malloc(N*sizeof *v);
	R=malloc(N*sizeof(double));
	last_R=malloc(N*sizeof(double));
	vtemp=malloc(N*sizeof *vtemp);
	last_v=malloc(N*sizeof *last_v);
	propM=malloc(N*sizeof(double));
	t=malloc(N*sizeof(double));
	dummyMethod3();
	for (i=0;i<N;i++){
		v[i]=malloc(sizeof *v[i]);
		last_v[i]=malloc(sizeof *last_v[i]);
		vtemp[i]=malloc(sizeof *vtemp[i]);
	}
	dummyMethod4();
	dummyMethod3();
	for (i=0;i<N;i++){
		M[i]=malloc(N*sizeof *M[i]);
		E[i]=malloc(N*sizeof *E[i]);
		M_hat[i]=malloc(N*sizeof *M_hat[i]);
	}
	dummyMethod4();

	//         END OF MATRIXES' DEFINITION           //


	//         INITIALIZE MATRIXES              //

	dummyMethod3();
	for (i=0;i<N;i++){
		t[i]=0;
		R[i]=(double)1/N;
		last_R[i]=(double)1/N;
		v[i][0]=rand()%50;
		last_v[i][0]=10;
		for (j=0;j<N;j++){
			E[i][j]=1;        //E is a matrix of ones
		}
	}
	dummyMethod4();
	tempSum=0;
	iterations_p=0;
	iterations_g=0;
	dummyMethod3();
	for (i=0;i<N;i++){
		tempSum+=v[i][0];
	}
	dummyMethod4();
	dummyMethod3();
	for (i=0;i<N;i++){
		v[i][0]/=tempSum;
	}
	dummyMethod4();

	propM=propMatrix(N,propM);

	//            END OF MATRIXES' INITIALIZATION        //


	M=randomStochasticPropMatrix2(N,propM,M);	
	

	//          DEFAULT M     //  (for testing, same M matrix as in matlab file, wikipedia)
	/**
	M[0][0]=0;
	M[0][1]=0;
	M[0][2]=0;
	M[0][3]=0;
	M[0][4]=1;
	M[1][0]=0.5;
	M[1][1]=0;
	M[1][2]=0;
	M[1][3]=0;
	M[1][4]=0;
	M[2][0]=0.5;
	M[2][1]=0;
	M[2][2]=0;
	M[2][3]=0;
	M[2][4]=0;
	M[3][0]=0;
	M[3][1]=1;
	M[3][2]=0.5;
	M[3][3]=0;
	M[3][4]=0;
	M[4][0]=0;
	M[4][1]=0;
	M[4][2]=0.5;
	M[4][3]=1;
	M[4][4]=0;
	**/

	// END DEFAULT M //


	gettimeofday (&endresttime, NULL);


	//      POWER METHOD START     //

	gettimeofday (&startwtime_p, NULL);
	dummyMethod3();
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			M_hat[i][j]=M[i][j]*d;
			E[i][j]*=(1-d)/N;
		}
	}
	dummyMethod4();
	dummyMethod3();
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			M_hat[i][j]+=E[i][j];
		}
	}
	dummyMethod4();
	flagNorm=norm2(v,last_v,N,e);
	while (flagNorm>0){
		iterations_p+=1;
			dummyMethod3();
		for (i=0;i<N;i++){
			last_v[i][0]=v[i][0];
		}
			dummyMethod4();
		vtemp=multiplyMatrix(N,N,1,M_hat,v,vtemp);
			dummyMethod3();
		for (i=0;i<N;i++){
			v[i][0]=vtemp[i][0];
		}
			dummyMethod4();
		flagNorm=norm2(v,last_v,N,e);
	}
	gettimeofday (&endwtime_p, NULL);

	//       POWER METHOD ENDING     //


	//       FREE MATRICES           //

	dummyMethod3();
	for (i=0;i<N;i++){
		free(M_hat[i]);
		free(E[i]);
		free(vtemp[i]);
		free(last_v[i]);
	}
	dummyMethod4();

	free(M_hat);
	free(E);
	free(vtemp);
	free(last_v);
	free(propM);

	//       END OF MATRICES' FREEING        //	


	//      GAUSS-SEIDEL METHOD START     //

	gettimeofday (&startwtime_g, NULL);

	
	

	factor=(double)(1-d)/N;
	while ((0==convergedFlag)){
		#pragma omp parallel private(i,j)
		{
			#pragma omp for private(i,j) schedule(static)
					dummyMethod3();
			for (i=0;i<N;i++){
				R[i]=0;
				t[i]=0;
				for (j=i;j<N;j++){
					t[i]+=d*M[i][j]*last_R[j];
				}
			}
					dummyMethod4();
		}
		
		for (i=0;i<N;i++){
			tempV=0;
			if (i>1000){
							dummyMethod1();
				#pragma omp parallel for schedule(static) reduction(+:tempV)
				for (j=0;j<i;j++){
					tempV+=d*M[i][j]*R[j];
				}
							dummyMethod2();
			}
			else{
				for (j=0;j<i;j++){
					tempV+=d*M[i][j]*R[j];
				}
			}
			tempV+=factor;
			tempV+=t[i];
			R[i]=tempV;			
		}
		convergedFlag=norm3(R,last_R,N,e);
			dummyMethod1();
		#pragma omp parallel for schedule(static)
		for (i=0;i<N;i++){
			last_R[i]=R[i];
		}
			dummyMethod2();
		iterations_g++;
	}
	
	gettimeofday (&endwtime_g, NULL);

	//       GAUSS-SEIDEL METHOD ENDING     //



	seq_time_g = (double)((endwtime_g.tv_usec - startwtime_g.tv_usec)/1.0e6 + endwtime_g.tv_sec - startwtime_g.tv_sec);
	printf("Total multiplying time_gauss:%f\n",seq_time_g);
	printf("Total iterations_gauss:%d\n",iterations_g);
	//for (i=0;i<N;i++){
	//	printf("%f\n",R[i]);
	//}

	seq_time_p = (double)((endwtime_p.tv_usec - startwtime_p.tv_usec)/1.0e6 + endwtime_p.tv_sec - startwtime_p.tv_sec);
	printf("Total multiplying time_power:%f\n",seq_time_p);
	printf("Total iterations_power:%d\n",iterations_p);
	//printMatrix(N,1,v);

	rest_time=(double)((endresttime.tv_usec - startresttime.tv_usec)/1.0e6 + endresttime.tv_sec - startresttime.tv_sec);
	printf("Total rest time:             %f\n",rest_time);
	checkSumOfV(N,e,v);
	checkResults(N,v,R,e);
	
	//               FREE REST MATRICES       //

	for (i=0;i<N;i++){
		free(v[i]);
		free(M[i]);
	}
	free(v);
	free(M);
	free(R);
	free(t);
	free(last_R);

	//              END OF MATRICES' FREEING     //

	return 0;
}


void checkResults(int N, double **v, double *R, double e){
	
	// Used to compare the results of power method
	// to the results of the Gauss-Seidel method

	int i;
	int flag=0;
	for (i=0;i<N;i++){
		if (fabs(R[i]-v[i][0])>(5*e)){
			flag=1;
			break;
		}
	}
	if (1==flag){
		printf("The results of the 2 methods don't match\n");
	}
}

void printMatrix(int a, int b, double **matrix){

	// Used for testing, it prints an axb matrix

	int i, j;
	for (i=0;i<a;i++){
		for (j=0;j<b;j++){
			printf("%f ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printSquareMatrix(int N, double **matrix){

	// Used for testing, it prints an NxN square matrix

	int i, j;
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			printf("%f ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

double **multiplyMatrix(int a, int b, int c, double **A, double **B, double **C){

	// This function multiplies an axb "A" matrix to a bxc "B" matrix
	// by the traditional way, and stores the result to an axc "C" matrix

	int i,j,k;
	double temp;
	for (i=0;i<a;i++){
		for (j=0;j<c;j++){
			temp=0;
			for (k=0;k<b;k++){
				temp+=A[i][k]*B[k][j];
			}
			C[i][j]=temp;
		}
	}
	return C;
}

double **multiplySquareMatrix(int N, double **A, double **B, double **C){

	// This function multiplies an NxN "A" matrix to an NxN "B" matrix
	// by the traditional way, and stores the result to an NxN "C" matrix

	int i,j,k;
	double temp;
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			temp=0;
			for (k=0;k<N;k++){
				temp+=A[i][k]*B[k][j];
			}
			C[i][j]=temp;
		}
	}
	return C;
}

double **randomStochasticMatrix(int N, double **M){

	// Not used

	// Creates a matrix of random elements, whose columns' sum is 1

	int i,j,colSum;
	for (j=0;j<N;j++){
		colSum=0;
		for (i=0;i<N;i++){
			M[i][j]=rand()%N;
			colSum+=M[i][j];
		}
		for (i=0;i<N;i++){
			M[i][j]/=colSum;
		}
	}
	return M;
}

double **randomStochasticPropMatrix2(int N,double *propArray, double **M){

	// Creates a stochastic Matrix M, a matrix that its columns have a sum of 1.
	// The propArray is the vector who gives the propability of a random node
	// giving a link to the ith element. For example, if propArray[2]=0.25, 
	// about 25% of the nodes will send a link to the 3rd element.

	int i,j,k,*colSum,per;
	colSum=malloc(N*sizeof(int));
	for (j=0;j<N;j++){
		colSum[j]=0;
	}
	for (i=0;i<N;i++){
		per=(int)(100*propArray[i]);
		for (j=0;j<N;j++){
			if (i!=j){
				M[i][j]=propabilityFunction(per);
				colSum[j]+=M[i][j];
			}
			else{
				M[i][j]=0;
			}
		}
	}

	// From here and on, we control the case that a column has only zeroes.

	for (j=0;j<N;j++){
		if (0==colSum[j]){
			for (i=0;i<N;i++){
				if (i!=j){
					M[i][j]=propabilityFunction(50);
					colSum[j]+=M[i][j];
				}
			}
		}
		if (0==colSum[j]){
			k=rand()%N;
			if (k==j){
				if (j!=(N-1)){
					k++;
				}
				else{
					k--;
				}
			}
			M[k][j]=1;
			colSum[j]=1;
		}
	}
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			M[i][j]/=colSum[j];
		}
	}
	free(colSum);
	return M;
	
}

double **randomStochasticPropMatrix(int N,double *propArray, double **M){

	// Not used

	// Has the same use with randomStochasticPropMatrix2, but it is much 
	// slower, because it reads and writes to the matrix with a not efficient way

	int i,j,colSum,per;
	for (j=0;j<N;j++){
		colSum=0;
		for (i=0;i<N;i++){
			if (i!=j){
				per=(int)(100*propArray[i]);
				M[i][j]=propabilityFunction(per);
				//printf("M[i][j]=%f, per=%d\n",M[i][j],per);
				colSum+=M[i][j];
			}
			else{
				M[i][j]=0;
			}
		}
		if (0==colSum){
			for (i=0;i<N;i++){
				if (i!=j){
					M[i][j]=propabilityFunction(50);
					colSum+=M[i][j];
				}
			}
		}
		if (0==colSum){
			per=rand()%N;
			if (per==j){
				if (j!=(N-1)){
					per++;
				}
				else{
					per--;
				}
			}
			M[per][j]=1;
			colSum=1;
		}
		for (i=0;i<N;i++){
			M[i][j]/=colSum;
		}
	}
	return M;
}

double **randomStochasticSparseMatrix(int N, int percentage, double **M){

	// Not used

	int i,j,colSum;
	for (j=0;j<N;j++){
		colSum=0;
		for (i=0;i<N-1;i++){
			M[i][j]=propabilityFunction(percentage);
			colSum+=M[i][j];
		}
		if (colSum==0){
			M[N-1][j]=1;
			colSum=1;
		}
		else{
			M[N-1][j]=propabilityFunction(percentage);
			colSum+=M[N-1][j];
		}
		for (i=0;i<N;i++){
			M[i][j]/=colSum;
		}
	}
	return M;
}

double norm(double **a, double **b, int N, int grade){

	// Not used

	double temp=0;
	int i;
	for (i=0;i<N;i++){
		temp+=pow((a[i][0]-b[i][0]),grade);
	}
	temp=sqrt(temp);
	return temp;
}

int norm2(double **a, double **b, int N, double e){

	// Not used

	int ret=0;
	int i;
	for (i=0;i<N;i++){
		if (fabs(a[i][0]-b[i][0])>e){
		//if (sqrt(pow((a[i][0]-b[i][0]),2))>e){
			ret=1;
			return ret;
			break;
		}
	}
	return ret;
}

int norm3(double *a, double *b, int N, double e){

	// This function checks the absolute differences between a[i] and b[i].
	// If all of the differences are smaller than e, it returnes 1. Else, it returns 0
	// *fabs() is abs() for doubles

	int ret=1;
	int i;
	for (i=0;i<N;i++){
		if (fabs(a[i]-b[i])>e){
			ret=0;
			return ret;
			break;
		}
	}
	return ret;
}

int propabilityFunction(int percentage){

	// Not used
	int a,b;
	a=rand()%100;
	if (a>percentage){
		b=0;
	}
	else{
		b=1;
	}
	return b;
}

void checkSumOfV(int N, double e, double **v){

	// Checks if the sum of a 1-column matrix is 1

	int i;
	double temp=0;
	for (i=0;i<N;i++){
		temp+=v[i][0];
	}
	if ((temp>e+1)||(temp<1-e)){
		printf("There is a problem in the sum, check your code\n");
	}
}

double *propMatrix(int N,double *matrix){

	// It creates a matrix with the propability distribution that is used in
	// randomStochasticPropMatrix2(). It is a function of type "1/x", meaning
	// that the most elements will have a low probality, and very few elements 
	// will have high propability.

	int i,m;
	for (i=0;i<N;i++){
		m=rand()%N+1;
		matrix[i]=((double)1/(1+(double)(200*m)/N));
	}
	return matrix;
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