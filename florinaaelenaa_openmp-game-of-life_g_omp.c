/*
 *   OpenMP - Modelarea unui automat celular (Game of life)
 *  Barbu Florina
 *
 *	Varianta paralela
 */


#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void check_file(FILE *f, char *name)
{
	if(f == NULL)
	{
		printf("Error in opening file <%s>!\n", name);
		exit(1);
	}
}

char** aloc_mem_matrix(int rows, int columns)
{
	int i;
	char **matrix;

	matrix = (char**)calloc(rows, sizeof(char*));
dummyMethod3();
	for(i = 0; i < rows; ++i)
		matrix[i] = (char*)calloc(columns, sizeof(char));

	return matrix;
dummyMethod4();
}

void matrix_borders(char **matrix, int rows, int columns)
{
	int i, j;

			dummyMethod1();
	#pragma omp parallel for
		for(j = 1; j <= columns; ++j)
		{
			matrix[0][j] = matrix[rows][j];   					//first line
			matrix[rows + 1][j] = matrix[1][j];   				//last line
		}
			dummyMethod2();

			dummyMethod1();
	#pragma omp parallel for	
		for(i = 1; i <= rows; ++i)
		{
			matrix[i][0] = matrix[i][columns];					//first column
			matrix[i][columns + 1] = matrix[i][1];				//last column
		}
			dummyMethod2();
	
	matrix[0][0]                  = matrix[rows][columns];	//left-up edge
	matrix[0][columns + 1]        = matrix[rows][1];		//right-up edge
	matrix[rows + 1][0]           = matrix[1][columns];		//left-down edge
	matrix[rows + 1][columns + 1] = matrix[1][1];			//right-down edge
}

void copy_matrix(char **A, char **B, int rows, int columns)
{
	int i, j;
	
	dummyMethod3();
	for(i = 0; i < rows; ++i)
		for(j = 0; j < columns; ++j)
			A[i][j] = B[i][j];
	dummyMethod4();
}

int main(int argc, char *argv[])
{
	//-------> 	DECLARATIONS <-------
	int i, j, k, dir;
	int no_interations;
	int rows, columns;
	int no_alive, no_dead;							//number of dead/alive cells

	int lines[8] = {-1, -1, -1,  0, 0,  1, 1, 1};  //coordinate directions to check neighbours values
	int cols[8]  = {-1,  0,  1, -1, 1, -1, 0, 1};

	char file_in[20], file_out[20];
	char **matrix, **copy;
	char buf;

	FILE *f_in, *f_out;
	
	
	//-------> 	INITIAL SETUP <-------
	
	strcpy(file_in, argv[1]);				// input file name
	strcpy(file_out, argv[3]);				// output file name 
	no_interations = atoi(argv[2]);			// number of iterations 
	 
	f_in  = fopen(file_in, "rt");  check_file(f_in,  file_in);
	f_out = fopen(file_out, "wt"); check_file(f_out, file_out);
	
	fscanf(f_in, "%d", &rows);
	fscanf(f_in, "%d", &columns);

	matrix = aloc_mem_matrix(rows + 2, columns + 2);
	copy = aloc_mem_matrix(rows + 2, columns + 2);

	i = 1; 
	while(i <= rows)
	{
		j = 1;
		while(j <= columns)
		{
			fscanf(f_in, "%c", &buf);
			if((buf != ' ') && (buf != '\n'))
				matrix[i][j++] = buf;
		}
		i++;
	}
	
	//-------> 	FILLING THE MATRIX MARGINS <-------
	matrix_borders(matrix, rows, columns);

	//-------> 	CREATING A COPY OF THE MATRIX <-------
	copy_matrix(copy, matrix, rows + 2, columns + 2);


	//-------> APPLYING TRANSFORMATIONS <-------
	for(k = 0; k < no_interations; ++k)
	{
			dummyMethod1();
		#pragma omp parallel for private(dir, no_alive, no_dead) collapse(2)
		for(i = 1; i <= rows; ++i)
			for(j = 1; j <= columns; ++j)
			{
				no_dead = 0; no_alive = 0;

				for(dir = 0; dir < 8; ++dir)
				{
					if(copy[i + lines[dir]][j + cols[dir]] == 'X')
						no_alive++;
					else
						no_dead++;
				}
				
				if(no_alive < 2)							//If there are less then 2 neighbours alive, the cell will be DEAD
					matrix[i][j] = '.';
				
				if(copy[i][j] == 'X')						//If a cell which is ALIVE has 2/3 neighbours ALIVE, it will remain ALIVE
					if(no_alive == 2 || no_alive == 3)
						matrix[i][j] = 'X';
				
				if(no_alive > 3)							//If a cell has more than 3 neighbours ALIVE, it will be DEAD
					matrix[i][j] = '.';

				if(copy[i][j] == '.')						//If a cell which is DEAD has 3 neighbours ALIVE, it will be ALIVE
					if(no_alive == 3)
						matrix[i][j] = 'X'; 

			}
			dummyMethod2();

		#pragma omp barrier
		
		matrix_borders(matrix, rows, columns);	
		copy_matrix(copy, matrix, rows + 2, columns + 2);
	}

	
	for(i = 1; i <= rows; ++i)
	{
		for(j = 1; j <= columns; ++j)
			fprintf(f_out, "%c ", matrix[i][j]);
		fprintf(f_out,"\n");
	}

	fclose(f_in);
	fclose(f_out);
	

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