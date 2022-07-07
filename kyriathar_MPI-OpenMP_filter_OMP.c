#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


#include "filter.h"
#include "my_functions.h"

int init_filter(Filter * filter)               //init the struct
{
    int returnValue = 101;
    
    if( filter != NULL )
    {
        filter->array = NULL;
        filter->sum = 0;
        filter->s =0;
        returnValue = 0;
    }
    else
        returnValue = 1;
    
    return returnValue;
}

int create_s_filter(Filter * filter,int s)     //create and init the array( size = (s +2)*(s+2) )
{
    int i,j ;
    int returnValue = 101;
    
    if( filter != NULL )
    {
        if( s >= 1 )                           //filter wont  be created for s < 1
        {
            if(filter->array == NULL)
            {
                filter->s = s ;
                /*create filter*/
                filter->array = (int **)my_malloc((s+2)*sizeof(int *));           
																															dummyMethod3();
                for(i=0;i<s+2;i++)
                    filter->array[i] = (int *)my_malloc((s+2)*sizeof(int ));
																															dummyMethod4();
                /*init filter*/
																															dummyMethod3();
                for(i=0;i<s+2;i++)
                    for(j=0;j<s+2;j++)
                        filter->array[i][j] = 0 ;
																															dummyMethod4();
                
                returnValue = 0;
            }
            else
                returnValue = 3;            //3---> array already intitialized
        }
        else
            returnValue = 2;                //2---> s < 1
    }
    else
        returnValue = 1;                    //1--->filter==NULL
    
    return returnValue;
}

int value_filter(Filter * filter)              //values to filter via scanf
{
    int i,j,s;
    int returnValue = 101;
    
    s = filter->s ;
    if( filter != NULL )
    {
        if(filter->array != NULL)
        {
            filter->array[0][0]= 1;filter->array[0][1]= 2;filter->array[0][2]= 1;
            filter->array[1][0]= 2;filter->array[1][1]= 4;filter->array[1][2]= 2;
            filter->array[2][0]= 1;filter->array[2][1]= 2;filter->array[2][2]= 1;
            
             /*find sum*/
																							dummyMethod3();
            for(i=0;i<s+2;i++)
                for(j=0;j<s+2;j++)
                    filter->sum += filter->array[i][j];
																							dummyMethod4();
            
            returnValue =0;
        }
        else
            returnValue = 2;                    //2---> filter->array == NULL
    }
    else
        returnValue = 1;                        //1--->filter==NULL

    return returnValue ;
}

int normalize_filter(Filter * filter)          //just normalize the filter
{
    int i,j,s;
    int returnValue = 101;
    
    s = filter->s ;
    if( filter != NULL )
    {
        if(filter->array != NULL)
        {
																							dummyMethod3();
            for(i=0;i<s+2;i++)
                for(j=0;j<s+2;j++)
                    filter->array[i][j] /= filter->sum;
																							dummyMethod4();
            
            returnValue = 0 ;
        }
        else
            returnValue = 2;                    //2---> filter->array == NULL
    }
    else
        returnValue = 1;                        //1--->filter==NULL
    
    return returnValue;
}


int print_filter(Filter * filter)
{
    int i,j,s;
    int returnValue = 101;
    
    s = filter->s ;
    if( filter != NULL )
    {
        if(filter->array != NULL)
        {
            printf("printing the array...\n");
																							dummyMethod3();
            for(i=0;i<s+2;i++)
            {   
                for(j=0;j<s+2;j++)
                {
                    printf("%d ",filter->array[i][j]);
                }
                printf("\n");
            }
																							dummyMethod4();
            returnValue =0 ;
        }
        else
            returnValue =2 ;                    //2---> filter->array == NULL
    }
    else
        returnValue = 1;                        //1--->filter==NULL

    return returnValue ;
}

int free_filter(Filter * filter)
{
    int i,s;
    int returnValue = 101;
    
    s= filter->s;
    if( filter != NULL )
    {
        if(filter->array != NULL)
        {
																					dummyMethod3();
           for(i=0;i<s+2;i++)
           {
               free(filter->array[i]);
               filter->array[i]=NULL;
           }
																					dummyMethod4();
           free(filter->array);
           filter->array = NULL ;
           
           returnValue =0 ;
        }
        else
            returnValue =2 ;                    //2---> filter->array == NULL
    }
    else
        returnValue = 1;                        //1--->filter==NULL

    return returnValue ;
}


int filterise(Filter * filter,int inner_i,int inner_j,unsigned char * image_in ,unsigned char * image_out,const int option)
{
    int x=0 ;
    int y=0 ;
    int fx=0 ,fy=0 ;
    int sum=0 ;
    int returnValue=101 ;
    
    if(filter != NULL)
    {
        if(image_in != NULL && image_out != NULL && filter->array != NULL)
        {
            if(option == INNER)
            {
																															dummyMethod1();
#pragma omp parallel for private(y,fx,fy,sum)
                for(x=2;x<inner_i;x++)
                {
                    for(y=2; y<inner_j ;y++)          //y < 1920
                    {
                        sum = 0 ;
                        for(fx=-1;fx<=1;fx++)
                            for(fy=-1;fy<=1;fy++)
                                sum += image_in[(x-fx)*(inner_j+2)+(y-fy)]*filter->array[fx+1][fy+1];
                        image_out[x*(inner_j+2) + y] = (int)sum/filter->sum ;
                    }
                }
																															dummyMethod2();
            }
            else if(option == OUTER)
            {
                
                /*first row*/
                y = 1 ;
																															dummyMethod1();
#pragma omp parallel for private(fx,fy,sum)
                for(x=1;x<inner_i+1;x++)
                {
                    sum = 0 ;
                        for(fx=-1;fx<=1;fx++)
                            for(fy=-1;fy<=1;fy++)
                                sum += image_in[(x-fx)*(inner_j+2)+(y-fy)]*filter->array[fx+1][fy+1];
                        image_out[x*(inner_j+2) + y] = (int)sum/filter->sum ;
                }
																															dummyMethod2();
                /*last row*/
                y = inner_j ;
																															dummyMethod1();
#pragma omp parallel for private(fx,fy,sum)
                for(x=1;x<inner_i+1;x++)
                {
                    sum = 0 ;
                        for(fx=-1;fx<=1;fx++)
                            for(fy=-1;fy<=1;fy++)
                                sum += image_in[(x-fx)*(inner_j+2)+(y-fy)]*filter->array[fx+1][fy+1];
                        image_out[x*(inner_j+2) + y] = (int)sum/filter->sum ;
                }
																															dummyMethod2();
                /*first column - 2 corners */
                x = 1 ;
																															dummyMethod1();
#pragma omp parallel for private(fx,fy,sum)
                for(y=2;y<inner_j;y++)
                {
                    sum = 0 ;
                        for(fx=-1;fx<=1;fx++)
                            for(fy=-1;fy<=1;fy++)
                                sum += image_in[(x-fx)*(inner_j+2)+(y-fy)]*filter->array[fx+1][fy+1];
                        image_out[x*(inner_j+2) + y] = (int)sum/filter->sum ;
                }
																															dummyMethod2();
                /*last column - 2 corners */
                x = inner_i ;
																															dummyMethod1();
#pragma omp parallel for private(fx,fy,sum)
                for(y=2;y<inner_j;y++)
                {
                    sum = 0 ;
                        for(fx=-1;fx<=1;fx++)
                            for(fy=-1;fy<=1;fy++)
                                sum += image_in[(x-fx)*(inner_j+2)+(y-fy)]*filter->array[fx+1][fy+1];
                        image_out[x*(inner_j+2) + y] = (int)sum/filter->sum ;
                }
																															dummyMethod2();
            }
            else
            {
                printf("Invalid option\n");
            }
            returnValue = 0;
        }
        else
            returnValue = 2;
    }
    else
        returnValue = 1 ;
    
    return returnValue;
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