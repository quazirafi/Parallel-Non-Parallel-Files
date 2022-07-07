#include <string.h> //Zawiera funkcje pomocnicze dla ciągów, korzystam tylko strlen,strcpy,strcat
#include <stdlib.h> //malloc
#include <stdio.h>
#include <time.h>
#include <dirent.h> //biblioteka POSIX (czytałem że dostępna dla windows również) do obsługi plików
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();



//Algorytm Knutha-Morrisa-Pratta
//https://pl.wikipedia.org/wiki/Algorytm_Knutha-Morrisa-Pratta

#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )

//Dynamicaly growing array implementation
typedef struct {
  char *fileName;
  int *array;
  size_t used;
  size_t size;
} FileFindings;

void initFileFindings(FileFindings *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertMatch(FileFindings *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeFileFindings(FileFindings *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

//Wyszukuje częściowych dopasowań
void checkPartialMatch(char* pattern, int T[]) {
    int position, t;
    int patternLen = strlen(pattern);

    T[0]=0; T[1]=0; t=0;
							dummyMethod3();
    for (position = 2; position <= patternLen; position++)
    {
        while ((t > 0) && (pattern[t] != pattern[position-1]))
        {
            t = T[t];
        }
        if (pattern[t] == pattern[position-1])
        {
            t++;
        }
        T[position]=t;
    }
							dummyMethod4();
}

//Pobiera liczbę plików w danym katalogu
size_t getFilesCount(char userPath[])
{
    struct dirent * file;
    DIR * path;
    size_t filesCount=0;
    if((path = opendir(userPath)))
    {
        while((file = readdir(path)))
        {
           char lastCharacter = file->d_name[strlen(file->d_name)-1];
           if(lastCharacter != '~' && file->d_type == DT_REG)
           {
                filesCount++;
           }
        }
    }
    return filesCount++;
}

//Znajdź ścieżki do wszystkich plików
FileFindings *fillFilePaths(char userPath[], int length)
{
    struct dirent * file;
    DIR * path;
    char userFilePath[1000];
    int i = 0;
    FileFindings* result = malloc(length * sizeof *result);


    if(result && (path = opendir(userPath)))
    {
        while((file = readdir(path)))
        {
            char lastCharacter = file->d_name[strlen(file->d_name)-1];
            if(lastCharacter != '~' && file->d_type == DT_REG)
            {
                strcpy(userFilePath, userPath);
                strcat(userFilePath, file->d_name);
                result[i].fileName = strdup(userFilePath);
                i++;
            }
        }
        closedir(path);
        return result;
    }
    else
    {
        return NULL;
    }
}

//Algorytm Knutha-Morrisa-Pratta
void kmp(int T[], char keyWord[], char searchString[], FileFindings *fileFinding)
{
    //patternLen - Długość wzorca
    //targetLen - Długość przeszukiwanego tekstu
    //position - zmienna pomocnicza do iterowania po szukanym tekście
    //matchesCount - zmienna pomocnicza określająca ilość dopasowanych liter od pozycji w tekście i
    int position = 1;
    int matchesCount = 0;
    unsigned int targetLen = strlen(searchString);
    int patternLen = strlen(keyWord);
    //przygotuj dynamiczy array dla wyników, na początku 1
    initFileFindings(fileFinding, 1);

							dummyMethod3();
    for(position = 1; position <= targetLen - patternLen + 1; position = position + max(1, matchesCount - T[matchesCount]))//dopóki mieścimy się w tekście
    {
        matchesCount = T[matchesCount];
        //dopóki kolejne znaki do siebie pasują i nie wykroczymy poza tekst
        while((matchesCount < patternLen) && (keyWord[matchesCount] == searchString[position + matchesCount - 1]))
        {
            matchesCount++;
        }
        if (matchesCount == patternLen)
        {
            insertMatch(fileFinding, position);
        }
        //jeśli nie ma dopasowania przesuwamy się o 1 znak do przodu, jeśli jakiekolwiek
        //dopasowanie było, możemy przesunąć się o długość wzorca minus częściowe dopasowanie wzorca jeśli istnieje
        //Przeniesiono do For! (kiedyś był while :))
    }
							dummyMethod4();
}

int main( int argc, char ** argv )
{
    FileFindings *fileFindings;

    char keyWord[100];
    char userPath[1000];
    int filesCount = 0;
    int T[100];//tablica częściowego dopasowania wzoru

    printf("Enter path to directory with files (ended with '/')\n");
    scanf(" %[^\n]s",userPath);
    printf("Keyword to search (max 100 characeters): ");
    scanf(" %[^\n]s",keyWord);

    checkPartialMatch(keyWord, T);
    if(strlen(userPath) < 2)
    {
        strcpy(userPath, "/home/marcin/Education/files/");
    }
    filesCount = getFilesCount(userPath);
    fileFindings = fillFilePaths(userPath, filesCount);

    //Seq measuring
    //clock_t start = clock();

    //OMP measuring
    double start_time = omp_get_wtime();

							dummyMethod1();
    #pragma omp parallel for default(none) shared(filesCount, fileFindings, T, keyWord)
    for(int i=0 ; i<filesCount ; i++)
    {
        FILE *f = fopen(fileFindings[i].fileName, "rb");//binary mode (najlepsza standaryzacja)
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);
        char *fileString = malloc(fsize + 1);
        fread(fileString, fsize, 1, f);
        kmp(T,keyWord, fileString, &fileFindings[i]);
        fclose(f);
        fileString[fsize] = 0;
        free(fileString);
    }
							dummyMethod2();

    //clock_t end = clock();
    //float time = (float)(end - start) / CLOCKS_PER_SEC;
    //OMP measuring
    double time = omp_get_wtime() - start_time;
    puts("wyniki wyszukiwania:");




    //Results
    int sumaWystapien = 0;
							dummyMethod3();
    for(int i=0; i< filesCount; i++) {
        //printf("========================\n");
        //puts(fileFindings[i].fileName);
        sumaWystapien += fileFindings[i].used;
        for(int i2 = 0; i2 < fileFindings[i].used; i2 ++)
        {
            //printf("%d\n", fileFindings[i].array[i2]);
        }
    }
							dummyMethod4();
    printf("Czas: ");
    printf("%f\n", time);
    printf("Suma wystąpień:");
    printf("%d\n", sumaWystapien);


    //clean up
							dummyMethod3();
    for(int i=0; i< filesCount; i++) {
        for(int i2 = 0; i2 < fileFindings[i].used; i2 ++)
        {
            freeFileFindings(&fileFindings[i]);
        }
    }
							dummyMethod4();
    free(fileFindings);

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