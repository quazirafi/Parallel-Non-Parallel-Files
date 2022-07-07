#include "omp.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
    The exercise was about experimenting with paralleled
    program by trying out different loop schemas and chunks.

    I decided to completely rebuild my exercise_4.c solutions
    to make it fully configurable(and train my C skills too ;). 
    Right now it's possible to experiment without recompiling it 
    every time when there is a need to change loop schema or 
    chunks amount.

    You can find the video with given exercise here:
    https://www.youtube.com/watch?v=8jzHiYo49G0#t=5m11s
*/
  
static long num_steps = 100000;
double step; 

void configure_parallel_environment();
void set_parallel_environment();
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

int main(int argc, char *argv)
{ 
    configure_parallel_environment();
    set_parallel_environment();
    calculate_the_integral();
    display_summary();
} 

void configure_parallel_environment()
{
    threads_amount = get_amount_of("threads");
    loop_schema = get_schema_of_loop();
    chunks_amount = get_amount_of("chunks");
}

void set_parallel_environment()
{
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