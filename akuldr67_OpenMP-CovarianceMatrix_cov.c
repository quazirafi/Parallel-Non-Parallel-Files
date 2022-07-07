#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//returns the value to placed in covarience matrix, given 2 arrays
double findCov(double x1[], double x2[], int n){
	double ans = 0;
dummyMethod1();
	#pragma omp parallel for reduction(+:ans)
	for(int i=0;i<n;i++){
		ans+=(x1[i]*x2[i]);
	}
dummyMethod2();
	return ans/((n-1)*1.0);
}

void main(){
	FILE *fp = fopen("iris.data","r");
	const char s[2] = ",";
	char *token;
	int i,j;
	int count=0;
	int rows=0;
	clock_t start, end;
 	double cpu_time_used;

	int t;
 	printf ("Ennter the number of threads: ");
	scanf("%d", &t);
	omp_set_num_threads(t);

	//will first count no of rows and columns, then initiate the array of exact size required
	if(fp!=NULL){
		//counting no of rows (stored in count)
			dummyMethod3();
		for (char c = getc(fp); c != EOF; c = getc(fp)){
        	if (c == '\n')
            	count = count + 1; 
    	}
			dummyMethod4();
	}
	fclose(fp);

	//now counting no of columns from the first line of file and storing it in "rows"
	fp = fopen("iris.data","r");
	char line[256];
	if(fgets(line, sizeof line, fp)!=NULL){
		token = strtok(line,s);
		i=0;
		while(token!=NULL){
			i++;
			token = strtok(NULL,s);
		}
		rows=i-1;
	}
	fclose(fp);

	//now inititating data and sum
	double data[count][rows];
	double sum[rows];
	int countIterator = 0;

	//reading data
	fp = fopen("iris.data","r");
	if(fp==NULL)
		printf("can't open dataset\n");
	else{
		//reading data
		char line[256];
		while(fgets(line, sizeof line, fp)!=NULL){
			//getting token by dividing line over every ','
			token = strtok(line,s);
			
			if(strcmp(line,"\n")!=0){

				i=0;
				//while there are more tokens present in that line
				while(1){
					//getting next token, so that last column could be ignored
					char *token2 = token;
					token = strtok(NULL,s);
					if(token!=NULL){
						float x = atof(token2);
						data[countIterator][i] = x; 	//storing data
						// sum[i]+=x;				//calculating sum for mean
					}
					else break;
					i++;
				}
				//counting no of rows (data enteries)
				countIterator++;

			}
		}
		fclose(fp);

		//printing total rows and columns
		// printf(" Total count: %d  rows: %d \n",count,rows);

		//initiating sum to 0
			dummyMethod3();
		for(i=0;i<rows;i++)
			sum[i] = 0;
			dummyMethod4();

		start = clock();
		
			dummyMethod1();
		#pragma omp parallel for reduction(+:sum[:rows]) private(j)
		for(i=0;i<count;i++){
			for(j=0;j<rows;j++){
				sum[j]+=data[i][j];
			}
		}
			dummyMethod2();
		
		//calculating mean
		double mean[rows];
			dummyMethod3();
		for(j=0;j<rows;j++){
			mean[j]=sum[j]/(count*1.0);
		}
			dummyMethod4();


		//printing mean
		printf(" Mean vector: [ ");
			dummyMethod3();
		for(i=0;i<rows;i++){
			if(i==rows-1)
				printf("%.2f ] \n", mean[i]);
			else printf("%.2f , ", mean[i]);
		}
			dummyMethod4();


		//making data for cov
			dummyMethod1();
		#pragma omp parallel for private(j)
		for(i=0;i<count;i++){
			for(j=0;j<rows;j++)
				data[i][j]-=mean[j];
		}
			dummyMethod2();

		double data2[rows][count];
		double cov[rows][rows];

		//data2 will store the transpose of the data
			dummyMethod1();
		#pragma omp parallel for private(i)
		for(j=0;j<count;j++){
			for(i=0;i<rows;i++)
				data2[i][j] = data[j][i];
		}
			dummyMethod2();

		//printing and calculating cov
		printf("\n Covarience matrix: \n");
			dummyMethod3();
		for(i=0;i<rows;i++){
			for(j=0;j<rows;j++){
				cov[i][j] = findCov(data2[i],data2[j],count);
				printf(" %.3f ",cov[i][j]);
			}
			printf("\n");
		}
			dummyMethod4();

		end = clock();
	 	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\nTime taken = %f\n",cpu_time_used);
	}
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