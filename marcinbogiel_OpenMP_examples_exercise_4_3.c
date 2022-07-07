#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
    The exercise was about experimenting with the paralleled program
    by trying out different loop schemas and chunks amount. To make 
    it easier I created the program which allows putting necessary 
    numbers as parameters without necessary of compiling it after 
    making a particular change. 
    
    To run it more than once you can open a new Terminal window 
    (Linux / Mac OS) and put bash commands:

    for i in {1..10}; do ./program_name a b c; done;

    where:
        - program_name - compiled code given in this file;
        - a - number of threads - integer number which indicate
            how many threads will be used to compute the integral;
        - b - loop schema - id of openMP schema which will be
            used to parallel loop. Available values:
                - 1 (static)
                - 2 (dynamic)
                - 3 (guided)
                - 4 (auto)
        - c - number of chunks which iterations of parallel loop
            will be divided.

    Example use:
        for i in {1..10}; do ./program_name 4 2 3; done;

    will run the program_name with 4 threads, dynamic loop schema
    and 3 chunks.
    
    You can find the video with given exercise here:
    https://www.youtube.com/watch?v=8jzHiYo49G0#t=5m11s
*/
  
static long num_steps = 100000;
double step; 

void validate_input_data(int argc, char **argv);
void set_parallel_environment(char **argv);
void calculate_the_integral();
void display_summary();
omp_sched_t get_schema_of_loop();
int get_amount_of(char *picked_item);
const char * set_used_schema_type(omp_sched_t loop_schema);

int threads_amount;
omp_sched_t loop_schema;
int chunks_amount;
double program_result;
double start_time, end_time;
char str_used_schema_type[20];

int main(int argc, char **argv)
{ 
    validate_input_data(argc, argv);
    set_parallel_environment(argv);
    calculate_the_integral();
    display_summary();
} 

void validate_input_data(int argc, char **argv)
{
    if(argc!=4)
    {
        printf("\nERROR - 3 parameters are needed!");
        printf("\nPut them in console and run the program again...\n\n");
        exit(0);
    }
    else 
    {
        if( (isdigit(*argv[1])==0) || (isdigit(*argv[2])==0) || (isdigit(*argv[3])==0) )
        {
            printf("\nERROR - input value must be integer numbers!");
            printf("\nCorrect them and run the program again...\n\n");
            exit(0);
        }
        else
        {
            if( (atoi(argv[1])<1) || ((atoi(argv[2])<1) || (atoi(argv[2])>4)) || (atoi(argv[3])<1))
            {
                if(atoi(argv[1])<1)
                {
                    printf("\nERROR - number of threads must be bigger then 0!");
                    printf("\nCorrect it and run the program again...\n");
                } 

                if((atoi(argv[2])<1) || (atoi(argv[2])>4))
                {
                    printf("\nERROR - number of loop schema must be value between 1-4!");
                    printf("\nCorrect it and run the program again...\n");
                }

                if(atoi(argv[3])<1)
                {
                    printf("\nERROR - size of the chunk must be bigger then 0!");
                }
                
                printf("\n");
                exit(0);
            }     
        }   
    }
}

void set_parallel_environment(char **argv)
{
    threads_amount = atoi(argv[1]);
    loop_schema = atoi(argv[2]);
    chunks_amount = atoi(argv[3]);

    omp_set_num_threads(threads_amount);
    omp_set_schedule(loop_schema,chunks_amount);
}

void calculate_the_integral()
{
    double sum = 0.0;
    int i;
    step = 1.0/(double) num_steps;

    start_time = omp_get_wtime();
							dummyMethod1();
    #pragma omp parallel for reduction(+ : sum)
    for(i=0;i<num_steps;i++){
        sum += 4.0/(1.0+((i+0.5)*step)*((i+0.5)*step));
    }
							dummyMethod2();
    program_result = step * sum;
    end_time = omp_get_wtime();
}

void display_summary()
{
    omp_get_schedule(&loop_schema,&chunks_amount);  

    strcpy(str_used_schema_type,set_used_schema_type(loop_schema));

    printf("\nResult  is: %f. \nAnd it was counted in %f seconds.\n",program_result,end_time-start_time);
    printf("With %d threads, %s schema and %d chunks. \n\n",threads_amount,str_used_schema_type,chunks_amount);
}

omp_sched_t get_schema_of_loop()
{
    int user_pick = 0;

    while(user_pick<1 || user_pick>4)
    {
        system("@cls||clear");

        printf("\nPick schema type: \n  ");
        printf("    1) static");
        printf("    2) dynamic");
        printf("    3) guided");
        printf("    4) auto\n\n");

        printf("Your pick: ");
        scanf("%d",&user_pick);
    }

    switch(user_pick) 
        {
            case 1:
                return omp_sched_static;
                break;
            case 2: 
                return omp_sched_dynamic;
                break;
            case 3: 
                return omp_sched_guided;
                break;
            case 4: 
                return omp_sched_auto;
                break;
            default:
                system("pause");
                break;
        }
}

int get_amount_of(char *picked_item)
{
    int user_pick = 0;

    while(user_pick<1)
    {
        system("@cls||clear");

        printf("\nPick number of %s",picked_item);
        if(strcmp(picked_item,"threads")==0)
            printf("(suggested %d)",omp_get_max_threads());
        printf(": ",picked_item);

        scanf("%d",&user_pick);
    }

    return user_pick;
}

const char * set_used_schema_type(omp_sched_t loop_schema)
{
    switch(loop_schema)
    {
        case omp_sched_static:
            return "static";  
            break;
        case omp_sched_dynamic:
            return "dynamic";  
            break;
        case omp_sched_guided:
            return "guided"; 
            break;
        case omp_sched_auto:
            return "auto"; 
            break;
        default:
            return "not defined";
            break;
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