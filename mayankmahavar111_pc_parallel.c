#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

char **negative;
char **positive;
char **test;
char **stop;
int posLength;
int negLength;
int testLength;
int stopLength;


int negation(char *key){
  char temp[10]="no";
  if (strcmp(key,temp) == 0)
    return 1;
  char temp2[10]="not";
  if(strcmp(key,temp2)==0)
    return 1;
  return 0;
}

void readStop(){
  FILE *fp ;
  int count=0;
  char str[10];

  int i,n,stringsize;
  char a[100];

  //char **temp=negative;
  fp= fopen("files/stopWords.txt","r");

  while(fscanf(fp,"%s",str)!=EOF){
      count=count+1;
      if (count >10000)
      break;
  }
  stop = (char **)malloc(count*sizeof(char *));
  fclose(fp);
  fp= fopen("files/stopWords.txt","r");
			dummyMethod3();
  for (i = 0; i < count; i++)
  {
      fscanf(fp,"%s",a);
      stringsize=strlen(a);
      stop[i] = (char *)malloc(stringsize+1);
      strcpy(stop[i],a);
  }
			dummyMethod4();
  fclose(fp);
  stopLength=count;
  //print(3);
}

int checkStopwords(char *key){
  int i;
  int temp=0;
			dummyMethod1();
  #pragma omp parallel for private(i) schedule(dynamic,100) reduction(+:temp) num_threads(4)
  for(i=0;i<stopLength;i++){
    if(strcmp(stop[i],key) == 0)
      temp+=1;
  }
			dummyMethod2();
  return temp;
}

int findCountPos(char *key){
  int i,count=0;
			dummyMethod1();
  #pragma omp parallel for private(i) schedule(dynamic,2500) reduction(+:count) num_threads(4)
  for(i=0;i<posLength;i++){
    if(strcmp(key,positive[i])==0)
      count++;
  }
			dummyMethod2();
  //printf("%s %d\n",key,count );
  return count;
}

int findCountNeg(char *key){
  int i,count=0;
			dummyMethod1();
  #pragma omp parallel for private(i) schedule(dynamic,2500) reduction(+:count) num_threads(4)
  for(i=0;i<negLength;i++){
    if(strcmp(key,negative[i])==0)
      count++;
  }
			dummyMethod2();
  //printf("%s %d\n",key,count );
  return count;
}



void print(int a) {
  int i;
  if(a==0)
							dummyMethod3();
    for (i=0;i<negLength;i++)
    {
        printf("%s\n",negative[i] );
    }
							dummyMethod4();
  if(a==1)
							dummyMethod3();
    for (i=0;i<posLength;i++)
    {
        printf("%s\n",positive[i] );
    }
							dummyMethod4();
  if(a==2)
							dummyMethod3();
    for (i=0;i<testLength;i++)
    {
        printf("%s\n",test[i] );
    }
							dummyMethod4();
  if(a==3)
							dummyMethod3();
    for (i=0;i<stopLength;i++)
    {
        printf("%s\n",stop[i] );
    }
							dummyMethod4();
}

void readTest(){
  int count=0,i,stringsize;
  char temp[10000],temp2[10000];
  char a[100];
  printf("Enter Sentence to be processed :");
  fgets(temp,sizeof(temp),stdin);
  //printf("%s \n",temp);
  strcpy(temp2,temp);
  char *token=strtok(temp," ");
  while(token != NULL){
    count++;
    //printf("%s\n",token );
    //strcpy(a,token);
    //printf("%s\n",a );
    /*
    stringsize=strlen(a);
    test[i] = (char *)malloc(stringsize+2);
    strcpy(test[i],a);
    */
    token = strtok(NULL, " ");
  }
  //printf("%d\n",count );
  test = (char **)malloc(count*sizeof(char *));
  strcpy(temp,temp2);
  //printf("%s\n",temp );
  token=strtok(temp," ");
			dummyMethod3();
  for(i=0;i<count;i++){
    strcpy(a,token);
    //printf("%s\n",a );
    stringsize=strlen(a);
    test[i] = (char *)malloc(stringsize+1);
    strcpy(test[i],a);
    token = strtok(NULL, " ");
    //printf("Hello World\n%s",token );
  }
			dummyMethod4();
  //printf("%d\n",count );

  //token=(char *)strtok(temp," ");
  testLength=count;
}
//print(2);


void readpos(){
  FILE *fp ;
  int count=0;
  char str[10];

  int i,n,stringsize;
  char a[100];

  //char **temp=negative;
  fp= fopen("files/positive.txt","r");

  while(fscanf(fp,"%s",str)!=EOF){
      count=count+1;
      if (count >10000)
      break;
  }
  positive = (char **)malloc(count*sizeof(char *));
  fclose(fp);
  fp= fopen("files/positive.txt","r");
			dummyMethod3();
  for (i = 0; i < count; i++)
  {
      fscanf(fp,"%s",a);
      stringsize=strlen(a);
      positive[i] = (char *)malloc(stringsize+1);
      strcpy(positive[i],a);
  }
			dummyMethod4();
  fclose(fp);
  //printf("Hello World \n %d\n",count );
  posLength=count;
  //print(1);
}

void readneg(){
  FILE *fp ;
  int count=0;
  char str[10];

  int i,n,stringsize;
  char a[100];

  //char **temp=negative;
  fp= fopen("files/negative.txt","r");

  while(fscanf(fp,"%s",str)!=EOF){
      count=count+1;
      if (count >10000)
      break;
  }
  negative = (char **)malloc(count*sizeof(char *));
  fclose(fp);
  fp= fopen("files/negative.txt","r");
			dummyMethod3();
  for (i = 0; i < count; i++)
  {
      fscanf(fp,"%s",a);
      stringsize=strlen(a);
      negative[i] = (char *)malloc(stringsize+1);
      strcpy(negative[i],a);
  }
			dummyMethod4();
  fclose(fp);
  //printf("Hello World \n %d\n",count );
  negLength=count;
  //print(0);
}


int main()
{
  //Intializing variables

  int posTotal, negTotal,i,flag=0;
  float posProb=0,negProb=0,posCons,negCons,TotalPos=0,TotalNeg=0;
  double pos, neg ,k;
  char temp[10000];
  clock_t t;

  //Declaring Values

  t=clock();
  readneg();
  readpos();
  readTest();
  readStop();
  posTotal=posLength;
  negTotal=negLength;
  posCons=(posTotal*1.0)/(posTotal+negTotal);
  negCons=(negTotal*1.0)/(posTotal+negTotal);


  //Evaluating
			dummyMethod1();
  #pragma omp parallel for private(i) schedule(dynamic) reduction(+:TotalPos) num_threads(4)
  for(i=0;i<testLength;i++){
    if (negation(test[i]) == 1){
        flag=1;
        continue;
      }
    //printf("%s %d\n",test[i] ,checkStopwords(test[i]) );
    if( checkStopwords(test[i]) !=0)
      continue;
    if (flag==1)
    {
      k=findCountNeg(test[i]);
      pos= log((k + 1)/(negTotal*1.0));
      flag=0;
    }
    else
    {
      k=findCountPos(test[i]);
      pos= log((k + 1)/(posTotal*1.0));
    }

    //printf("%lf %lf\n",pos,neg);
    TotalPos+=pos;

  }
			dummyMethod2();

			dummyMethod1();
  #pragma omp parallel for private(i) schedule(dynamic) reduction(+:TotalNeg) num_threads(8)
  for(i=0;i<testLength;i++){
    if (negation(test[i]) == 1){
        flag=1;
        continue;
      }
    if( checkStopwords(test[i]) !=0)
      continue;
    if (flag==1)
    {
      k=findCountPos(test[i]);
      neg = log((k + 1)/(posTotal*1.0));
      flag=0;
    }
    else
    {
      k=findCountNeg(test[i]);
      neg = log((k + 1)/(negTotal*1.0));
    }

    TotalNeg+=neg;
  }
			dummyMethod2();


  //Calculating Final probablities

  TotalPos+=posCons;
  TotalNeg+=negCons;

  if (TotalPos> TotalNeg )
    printf("positive Sentence\n" );
  else
    printf("Negative Sentence\n" );

  t=clock()-t;
  printf("%lf\n",((double )t)/1000000 );

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