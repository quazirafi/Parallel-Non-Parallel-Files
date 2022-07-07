#include "omp.h"
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUM_THREADS 2

int main(void)
{  
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
   printf("Files in this directory\n");
	char files[1000][1000];
	int count=0;
	if (d)
    { 
        while ((dir = readdir(d)) != NULL)
        {   
        	strcpy(files[count++],dir->d_name);
        
    	}
    	
    	closedir(d);
    }
    //printf("count =%d\n",count-2);
            //printf("%s\n", dir->d_name);
		

	
//	omp_set_nested(1);

	 clock_t tic = clock();

	
	dummyMethod3();
	for(int i=4;i<count;i++)
	{
		puts(files[i]);
		printf("\n");
	}	
	dummyMethod4();
			
			dummyMethod1();
	#pragma omp parallel for num_threads(8) 
		for(int i=4;i<count;i++)
		{
			//int id=omp_get_thread_num();
			FILE * fp1;
			fp1 = fopen(files[i], "r");
			
				
			#pragma omp parallel for num_threads(count)
			for(int j=i+1;j<count;j++)
			{
				
			 FILE * fp2;
			 char c1[100], c2[100];
			 int cmp;
			 
			 
			 fp2 = fopen(files[j], "r");
			 
			 if((fp1 == NULL) || (fp2 == NULL))
			 {
			  //printf("Error in the file \n");
			 }
			 else
			 {
			  fgets(c1 , 100, fp1) != NULL;    
			   //puts(c1);        
			    
			  fgets(c2 , 100, fp2) != NULL;
			   //puts(c2);
			   
			  if((cmp = strcmp(c1, c2)) == 0)
			  {
			   printf("Files \t%s \t& \t%s \tDUPLICATE \n",files[i],files[j]);
			  }
			  else
			  {
			   printf("Files \t%s \t& \t%s \t\n",files[i],files[j]);
			  }  
			 }			
				
			}
		}
			dummyMethod2();
	
        clock_t toc = clock();
        printf("count =%d\n",count-2);

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return(0);
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