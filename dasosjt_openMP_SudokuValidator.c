#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define GRIDN 9

int fd_sudoku;
char *addr_sudoku, *sudoku_grid[GRIDN][GRIDN];
struct stat s;
int matrix_index[3] = {0, 3, 6};

int check_column(int coord)
{
  //printf("check column \n");
  int column[GRIDN] = { 0 }, sum = 0;

  //check column
			dummyMethod1();
  #pragma omp parallel for shared(column)
  for(int i = 0; i < GRIDN; i++){
    printf("%d \n", (*(sudoku_grid[coord][i]) - '0') - 1);
    int temp_index;

    temp_index = (*(sudoku_grid[coord][i]) - '0') - 1;

    //if column has repeated values
    if(column[temp_index] == 1){
      //TODO: return error
      printf("repetead value, index %d \n", temp_index);
    }

    column[temp_index] = 1;
  }
			dummyMethod2();

  //check sum
			dummyMethod3();
  for(int i = 0; i<GRIDN; i++){
    sum += column[i];
  }
			dummyMethod4();

  if(sum == GRIDN){
    //TODO: return success
    printf("check_column result %d\n", sum);
  }else{
    //TODO: return error
    printf("error, check_column result %d\n", sum);
  }

  return 1;
}

int check_row(int coord)
{
  //printf("check row \n");
  int row[GRIDN] = { 0 }, sum = 0;

  //check row
			dummyMethod1();
  #pragma omp parallel for shared(row)
  for(int i = 0; i < GRIDN; i++){
    printf("%d \n", (*(sudoku_grid[i][coord]) - '0') - 1);
    int temp_index;

    temp_index = (*(sudoku_grid[i][coord]) - '0') - 1;

    //if row has repeated values
    if(row[temp_index] == 1){
      //TODO: return error
      printf("repetead value, index %d \n", temp_index);
    }

    row[temp_index] = 1;
  }
			dummyMethod2();

  //check sum
			dummyMethod3();
  for(int i = 0; i<GRIDN; i++){
    sum += row[i];
  }
			dummyMethod4();

  if(sum == GRIDN){
    //TODO: return success
    printf("check_row result %d\n", sum);
  }else{
    //TODO: return error
    printf("error, check_row result %d\n", sum);
  }

  return 1;
}

int check_matrix(int coord_x, int coord_y)
{
  //printf("check matrix \n");
  int mapped_matrix[GRIDN] = { 0 }, sum = 0;

			dummyMethod1();
  #pragma omp parallel for shared(mapped_matrix)
  for(int i = coord_y; i < coord_y + 3; i++){
    for(int j = coord_x; j < coord_x + 3; j++){
      int temp_index = (*(sudoku_grid[i][j]) - '0') - 1;

      if(mapped_matrix[temp_index] == 1){
        //TODO: return error
        printf("repetead value, index %d \n", temp_index);
      }

      mapped_matrix[temp_index] = 1;
    }
  }
			dummyMethod2();

			dummyMethod3();
  for(int i = 0; i<GRIDN; i++){
    sum += mapped_matrix[i];
  }
			dummyMethod4();

  if(sum == GRIDN){
    //TODO: return success
    printf("check_row result %d\n", sum);
  }else{
    //TODO: return error
    printf("error, check_row result %d\n", sum);
  }

  return 1;
}

int main(int argc, char *argv[])
{
  if(argc != 2)
    return -1;

  if((fd_sudoku = open(argv[1], O_RDONLY)) < 0)
    return -1;

  if(fstat(fd_sudoku, &s) < 0)
    return -1;

  addr_sudoku = (char *)mmap(0, s.st_size, PROT_READ, MAP_SHARED, fd_sudoku, 0);
			dummyMethod3();
  for(int i = 0; i<s.st_size; i++){
    sudoku_grid[(int)floor(i/GRIDN)][i%GRIDN] = &addr_sudoku[i];
  }
			dummyMethod4();

			dummyMethod3();
  for(int i = 0; i<GRIDN; i++){
    check_column(i);
    check_row(i); 
  }
			dummyMethod4();

  close(fd_sudoku);
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