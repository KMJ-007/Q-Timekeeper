#include<stdio.h>
#include"qtimekeeper.h"
// #include"ganttchart.h"

int main()
{
    printf("\nWelcome to Q-Timekepper \n");
    printf("job scheduling simulator \n");
    // qtimekeeper();
    
    // process_t processes[] = {
    //     {1, 0, 5, 1, 0, 5, 0, 0},
    //     {2, 2, 3, 2, 0, 3, 0, 0},
    //     {3, 3, 1, 3, 0, 1, 0, 0},
    //     {4, 5, 2, 4, 0, 2, 0, 0},
    //     {5, 6, 4, 5, 0, 4, 0, 0},
    // };

    int dummy_max_process = 5;
    int dummy_overhead_time = 2;
    float dummy_avg_waiting_time = 0;
    float dummy_avg_turnaround_time = 0;
    int dummy_total_time = 0;
    process_t *dummy_processes = malloc(sizeof(process_t) * dummy_max_process);

    // Initialize the dummy process data
    for(int i = 0; i < dummy_max_process; i++){
        dummy_processes[i].process_id = i;
        dummy_processes[i].arrival_time = i*2;
        dummy_processes[i].burst_time = i*3;
        dummy_processes[i].priority = (i % 3) + 1;
        dummy_processes[i].start_time = 0;
        dummy_processes[i].finish_time = (i+1) * 3;
        //update total time
        dummy_total_time += dummy_processes[i].burst_time;
    }

    // Call the function with the dummy variables
    draw_gantt_chart(dummy_processes, dummy_max_process, dummy_total_time, 10, 10);



    return 0;
}
