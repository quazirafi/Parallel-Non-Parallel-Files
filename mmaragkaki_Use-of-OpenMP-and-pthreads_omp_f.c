//
//  main.c
//  ReadingFiles
//
//  Created by Hera Katara on 16/03/2019.
//  Copyright © 2019 Hera Katara. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define MAX  2000

int INT1 , INT2, INT3, INT4 ;
char *ID,*PATH;
double cellstime,cellstime1,tracetime,tracetime1;
int traceback_steps;
int **Score;

typedef struct pos {
   int x;
   int y;
} pos;

static struct option long_options[] =
{
    {"name", required_argument, NULL, 'a'},
    {"input", required_argument, NULL, 'b'},
    {"match", required_argument, NULL, 'c'},
    {"mismatch", required_argument, NULL, 'd'},
    {"gap", required_argument, NULL, 'e'},
    {"threads", required_argument, NULL, 'f'},
    {NULL, 0, NULL, 0}
};
void SW_algorithm(char* X,char* Y,int lx,int ly);
int max_Score(int n1,int n2,int n3);
void print_table( int lx, int ly, int array[lx][ly]);
int Smith_Waterman(char* X, char* Y,int lx,int ly);
void matrix_initialization(int lx, int ly);
pos *max_pos_finder(int lx,int ly,int counter,pos arrayOfPos[counter],int max);
int traceback (char* X, char* Y,int ax,int by);
static void usage(const char *argv0);
double gettime(void);
FILE *fptr;
FILE *fid;


int main(int argc, char *argv[]){
  double time0 = gettime();

  long int numofcells = 0;
  int choise;

  while ((choise = getopt_long_only(argc, argv, "a:b:c:d:e:", long_options, NULL)) != -1)
  	{
  		switch(choise)
  		{
  			case 'a':
  				while (1){
  					ID = optarg;
  					if((fid = fopen(ID, "w")) != NULL) {
  						//printf("Succesful opening %s\n", ID);
  						//fclose(fid);
  						break;
  					}
  					else {
  						fprintf(stderr, "\nError openning file %s\n", ID);
  						continue;
  					}
  				}
  				break;
  			case 'b':
  				PATH = optarg;
  				if((fptr = fopen(PATH, "r")) != NULL) {
  					printf("Succesful opening %s\n", PATH);
  					//fclose(fptr);
  				}
  				else {
  					fprintf(stderr, "\nError openning file %s\n", PATH);
  				}
  				break;
  			case 'c':
  				INT1 = atoi(optarg);
  				break;
  			case 'd':
  				INT2 = atoi(optarg);
  				break;
  			case 'e':
  				INT3 = atoi(optarg);
  				break;
          case 'f':
          INT4 = atoi(optarg);
          break;
  			default:
  				usage(argv[0]);
  		}
  	}

      if (argc < 13)
      {
          fprintf(stderr, "%s: Too few arguments\n", argv[0]);
          usage(argv[0]);
      }


    int Pairs = 0, Qmin = 0, Qmax = 0, Dall = 0, prs = 0;


    fscanf(fptr, "Pairs: %d\nQ_Sz_Min: %d\nQ_Sz_Max: %d\nD_Sz_All: %d\n\n", &Pairs, &Qmin, &Qmax, &Dall);

    while(prs < Pairs){
      int i = 0, j = 0 ;
      char *Q ;
      char *D ;
      Q = NULL;
      D = NULL;
      Q = (char *) malloc((Qmax)*sizeof(char));
      D = (char *) malloc((Dall)*sizeof(char));


      while (j<Qmax) {
        Q[j] = fgetc(fptr);
        if(Q[j] == '\n'){
          continue;
        }
        if(Q[j] == 'D'){
          Q[j] = '\0';
          break;
        }

        if((Q[j] != '\n') && (Q[j] != 'Q') && (Q[j] != ':') && (Q[j] != '\t') && (Q[j] != 'D')){
          j++;
        }
      }

      while ( i < Dall) {
        D[i] = fgetc(fptr);
        if(D[i] == '\n' ){
          continue;
        }
        if((D[i] != '\n') && (D[i] != ':') && (D[i] != '\t')){
          i++;
        }
      }

      numofcells = numofcells +(j*Dall);
      fprintf(fid, "Q: %s\nD: %s\n", Q,D);

      SW_algorithm(D,Q,Dall,j);


      free(Q);
      Q = NULL;
      free(D);
      D = NULL;
      prs++;
  }

  //listOfPos = NULL;
	fclose(fptr);
  fclose(fid);
  double time1 = gettime();
  double  elapsedtime = 0, elapsedcells = 0, elapsedtrace = 0;
  long int cups = 0, cups8 = 0;
  elapsedtime = (time1-time0);
  cups = (numofcells/elapsedtime);
  elapsedcells = (cellstime1-cellstime);
  elapsedtrace = (tracetime1-tracetime);
  cups8 = (numofcells/elapsedcells);
  printf("Total number of pairs: %d\n", Pairs);
  printf("Total number of cells who takes value: %ld\n", numofcells );
  printf("Total number of traceback steps is: %d\n", traceback_steps);
  printf("Total time of program's execution: %lfs\n",elapsedtime);
  printf("Total time of cells's count: %lfs\n",elapsedcells);
  printf("Total traceback time: %lfs\n", elapsedtrace);
  printf("Total CUPS: %ld\n", cups);
  printf("CUPS based to total time of cells's count: %lds\n", cups8);


  return 0;
}

void SW_algorithm(char* X,char* Y,int lx,int ly){

 //  int lx = strlen(X);
 //  int ly = strlen(Y);
 //  int Score[lx+1][ly+1] ;
  Score = malloc((lx + 1)*sizeof(int *));
			dummyMethod3();
  for(int i = 0; i <= lx; i++){
    Score[i] = malloc((ly + 1)*sizeof(int));
  }
			dummyMethod4();
  int max_val = 0;
  int ax = 0 ,by = 0,counter = 0;

  //initialize matrix
  matrix_initialization(lx, ly);
  // Filling the array according Smith-Waterman Algorithm
  cellstime = cellstime + gettime();
  max_val = Smith_Waterman(X,Y,lx,ly);
  cellstime1 = cellstime1 + gettime();

			dummyMethod3();
  for(int i = 0; i <= lx; i++){
      for(int j = 0; j <= ly; j++){
          if(Score[i][j] == max_val)
              counter++;   // How many times we have max score??
      }
  }
			dummyMethod4();

   pos arrayOfPos[counter] ;
   //pos list[counter] ;

  pos* list = max_pos_finder(lx, ly,counter,arrayOfPos,max_val);

  int start = 0;
			dummyMethod3();
  for(int h = 0 ; h < counter; h++){
       ax = list[h].x;
       by = list[h].y;
      fprintf(fid, " Q D\n");
      tracetime = tracetime + gettime();
      start = traceback (X,Y,ax,by);
      tracetime1 = tracetime1 + gettime();
      fprintf(fid, "Match %d [Score: %d, Start: %d, Stop: %d]\n", h+1, max_val, start , by-1);
      fprintf(fid,"\n");
  }
			dummyMethod4();
			dummyMethod3();
  for(int i = 0; i <= lx; i++){
    free(Score[i]);
  }
			dummyMethod4();
  free(Score);
  Score = NULL;
//  free(list);
}

// Fuction for calcucation the max value out of the three shells
int max_Score(int n1,int n2,int n3){
    int result = 0;
    if(n1 > n2){
        if(n1 > n3){
            result = n1;
        }
        else{
            result = n3;
        }
    }
    else{
        if(n2 > n3){
            result = n2;
        }
        else{
            result = n3;
        }
    }
    if(result < 0){
        result = 0;
    }
    return (result);
}


void matrix_initialization(int lx, int ly){
			dummyMethod3();
  for(int i = 0; i <= lx; i++){
     for(int j = 0; j <= ly; j++){
         Score[i][j] = 0; // First column and first row full of zeros
     }
  }
			dummyMethod4();
}

int Smith_Waterman( char* X, char* Y,int lx,int ly){
  //#pragma omp parallel
  int max_val = 0;
  int n1 = 0, n2 = 0, n3 = 0;
  //int lx = strlen(X);
  //int ly = strlen(Y);
  int i, j;
  //int chunk = 0;

  //omp_set_num_threads(INT4);

  /*if(INT4>(lx+1))
    chunk = lx+1;
  else
    chunk = (lx+1)/INT4;*/

  //#pragma omp parallel for private(i,j) num_threads(INT4)
  //#pragma omp parallel for schedule(static) collapse(2)
  
  
  for( i = 0; i <= lx; i++){
							dummyMethod1();
    #pragma omp parallel  for private(j)  num_threads(INT4)
    for( j = 0; j <= i; j++){
      if(j <= ly){
        if((i-j)  != 0 && j != 0){
          // Match Case
          if(X[(i-j)-1] == Y[j-1]){
            n1 = Score[(i-j) -1][j-1] + INT1; //For match or mismatch
            n2 = Score[(i-j) -1][j] - INT3;
            n3 = Score[(i-j) ][j-1] - INT3;
            Score[(i-j) ][j] = max_Score(n1,n2,n3);
          }
          // Missmatch case
          if(X[(i-j) -1] != Y[j-1]){
            n1 = Score[(i-j) -1][j-1] + INT2; //For match or mismatch
            n2 = Score[(i-j) -1][j] - INT3;
            n3 = Score[(i-j) ][j-1] - INT3;
            Score[(i-j) ][j] = max_Score(n1,n2,n3);
          }
          if(Score[(i-j) ][j] >= max_val ){
            max_val = Score[(i-j)][j];
          }
        }
      }
      /*else{
        break;
      }*/
    }
							dummyMethod2();
  }

  int l = 0;
  
  for( l = ly; l>=1; l--){
    j = lx;
							dummyMethod1();
    #pragma omp parallel for private(i,j) num_threads(INT4)
    for( i = (l-1); i>=0; i--){
      if(X[j-1] == Y[(ly-i)-1]){
        n1 = Score[j -1][(ly-i)-1] + INT1; //For match or mismatch
        n2 = Score[j -1][(ly-i)] - INT3;
        n3 = Score[j][(ly-i)-1] - INT3;
        Score[j][(ly-i)] = max_Score(n1,n2,n3);
      }
      // Missmatch case
      if(X[j-1] != Y[(ly-i) -1]){
        n1 = Score[j -1][(ly-i)-1] + INT2; //For match or mismatch
        n2 = Score[j -1][(ly-i)] - INT3;
        n3 = Score[j ][(ly-i)-1] - INT3;
        Score[j ][(ly-i)] = max_Score(n1,n2,n3);
        //  printf("%d %d %d\n",(ly-i), j, Score[(ly-i)][j]);
       }

      if(Score[j][(ly-i)] >= max_val ){
        max_val = Score[j][(ly-i)];
      }
      j--;
    }
							dummyMethod2();
  }
  return max_val;
}

pos *max_pos_finder(int lx,int ly,int counter,pos arrayOfPos[counter],int max){
    int xpos = 0, ypos = 0, z = 0;

    // Find the pos of max val
    for(int i = 0; i <= lx; i++){
        for(int j = 0; j <= ly; j++){
            if(Score[i][j] == max){
                xpos = i;
                ypos = j;
                arrayOfPos[z].x = xpos;
                arrayOfPos[z].y = ypos;
                z++;
            }
        }
    }
    //Display the list of pos of max scores

    return arrayOfPos;
}

int traceback (char* X, char* Y,int ax,int by){
  traceback_steps++;
  if (Score[ax][by] == 0){
    return by;
  }
  int new_diagonal = 0, new_left = 0;

  //  new_above = array[ax-1][by] - INT3;
  new_left = Score[ax][by-1] - INT3;

  if(X[ax-1] == Y[by-1]){
    new_diagonal = Score[ax-1][by-1] + INT1;
    fprintf(fid, "%2c",X[ax-1] );
    fprintf(fid, "%2c\n",Y[by-1] );
  }
  else{
    fprintf(fid,"%2c",X[ax-1] );
    fprintf(fid," -\n" );
    new_diagonal = Score[ax-1][by-1] + INT2;
  }

  if (new_diagonal == Score[ax][by]){
    return traceback(X,Y, ax-1, by-1);
  }
  else if(new_left == Score[ax][by]){
    return traceback(X,Y, ax, by-1);
  }
  else {
    return traceback(X,Y, ax-1, by);
  }
  return 0;
}

static void usage(const char *argv0){
  fprintf(stderr, "Usage: %s [-name ID][-input PATH][-match INT1][-mismatch INT2][-gap INT3][-threads INT4]\n", argv0);
  exit(EXIT_FAILURE);
}

double gettime(void){
  struct timeval ttime;
  gettimeofday(&ttime,NULL);
  return ttime.tv_sec+ttime.tv_usec * 0.000001;
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