#include<stdio.h>
#include<stdlib.h>

void priority_non_premeemptive(process_t * processes, int max_process, int overhead_time){
    printf("hello from priority_non_premeemptive");
    // priority scheduling non premeemptive, i have already processes which are sorted by arriaval time first and then by priority

    int current_time=0;
    int total_waiting_time=0;
    int total_turn_around_time=0;

    // run the processes
    for(int i = 0; i < max_process; i++) {
        if(current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        current_time += overhead_time;
        processes[i].finish_time = current_time + processes[i].burst_time;
        processes[i].turn_around_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turn_around_time += processes[i].turn_around_time;

        current_time += processes[i].burst_time;
    }
        // calculate the average waiting time and average turn around time
        float avg_waiting_time = (float)total_waiting_time / max_process;
        float avg_turnaround_time = (float)total_turn_around_time / max_process;

        // printing the process
        printf("\nProcess ID\tArrival Time\tBurst Time\\priorty\tFinish Time\tWaiting Time\tTurn Around Time");
        for(int i = 0; i < max_process; i++) {
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].finish_time, processes[i].waiting_time, processes[i].turn_around_time);
        }

        printf("\nAverage Waiting Time: %f", avg_waiting_time);
        printf("\nAverage Turnaround Time: %f", avg_turnaround_time);


        
}