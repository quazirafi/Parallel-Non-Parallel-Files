#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
        struct timeval start, endd;

        gettimeofday(&start, NULL);
        double arr[10];
        double max_val = 0;
        int arrival_time[10], burst_time[10], temp[10];
        int i, smallest, count = 0, time, limit;
        double wait_time = 0, turnaround_time = 0, end;
        float average_waiting_time, average_turnaround_time;
        printf("\nEnter the Total Number of Processes:\t");
        scanf("%d", &limit);
        printf("\nEnter Details of %d Processes\n", limit);
dummyMethod3();
        for (i = 0; i < limit; i++)
        {
                printf("\nEnter Arrival Time:\t");
                scanf("%d", &arrival_time[i]);
                printf("Enter Burst Time:\t");
                scanf("%d", &burst_time[i]);
                temp[i] = burst_time[i];
        }
dummyMethod4();
        burst_time[9] = 9999;
        for (time = 0; count != limit; time++)
        {
                smallest = 9;
																															dummyMethod1();
        #pragma omp parallel for shared(i) reduction(max : max_val)
                for (i = 0; i < limit; i++)
                {
                        if (burst_time[i] >= max_val && arrival_time[i] <= time)
                        {
                                smallest = i;
                                max_val=burst_time[smallest];
                        }
                }
																															dummyMethod2();
                burst_time[smallest]--;
                if (burst_time[smallest] == 0)
                {
                        count++;
                        end = time + 1;
                        wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                        turnaround_time = turnaround_time + end - arrival_time[smallest];
                }
        }
        average_waiting_time = wait_time / limit;
        average_turnaround_time = turnaround_time / limit;
        printf("\n\nAverage Waiting Time:\t%lf\n", average_waiting_time);
        printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);

        gettimeofday(&endd, NULL);
        long seconds = (endd.tv_sec - start.tv_sec);

        printf("Time elpased is %ld second", seconds);
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