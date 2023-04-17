#include<stdio.h>
#include<stdlib.h>



void swap(process_t *a, process_t *b) {
    process_t temp = *a;
    *a = *b;
    *b = temp;
}


void priority_premeemptive(process_t * processes, int max_process, int overhead_time){
    int current_time = 0;
    int completed = 0;
    
    printf("hello from priority_premeemptive");
    // Sorting processes in ascending order of arrival time
    for(int i = 0; i < max_process - 1; i++) {
        for(int j = i + 1; j < max_process; j++) {
            if(processes[i].arrival_time > processes[j].arrival_time) {
                swap(&processes[i], &processes[j]);
            }
        }
    }


 // Printing Gantt chart headers
    printf("\nGantt Chart:\n");
    printf("------------------------------------------------------------------------\n");
    printf("| Process ID | Arrival Time | Burst Time | Finish Time | remaining time |\n");
    printf("-------------------------------------------------------------------------\n");

    // Running the priority preemptive algorithm
    while(completed != max_process){
        
        // Find the process with minimum priority
        int min_priority = 1000, index = -1;
        for(int i = 0; i < max_process; i++) {
            // Check if the process has remaining time and has already arrived
            if(processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                if(processes[i].priority < min_priority) {
                    min_priority = processes[i].priority;
                    index = i;
                }
            }
        }

        // If no process is available, print IDLE and increment current time
        if(index == -1) {
            printf("|     IDLE   |      %d      |     %d     |     %d      |  \n", current_time, overhead_time, current_time + overhead_time);
            current_time += overhead_time;
        }
        else {

            // Updating waiting time if the process has just started
            if(processes[index].remaining_time == processes[index].burst_time) {
                processes[index].waiting_time = current_time - processes[index].arrival_time;
            }

            // Decrementing remaining time and incrementing current time
            processes[index].remaining_time--;
            current_time++;

            // If the process has finished, update its details
            if(processes[index].remaining_time == 0) {
                completed++;
                processes[index].finish_time = current_time;
                processes[index].turn_around_time = processes[index].finish_time - processes[index].arrival_time;
                processes[index].waiting_time = processes[index].turn_around_time - processes[index].burst_time;
                printf("--------------------------------------------------------\n");
            }
        }
        // Printing the details of the selected process
            printf("|     P%d     |      %2d     |     %2d     |    %2d     |   %2d   |\n", processes[index].process_id, processes[index].arrival_time, processes[index].burst_time, processes[index].finish_time,processes[index].remaining_time);
    }


    // calculating average waiting time and average turn around time
    float avg_waiting_time = 0, avg_turn_around_time = 0;
    for(int i = 0; i < max_process; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turn_around_time += processes[i].turn_around_time;
    }
    avg_waiting_time /= max_process;
    avg_turn_around_time /= max_process;

    // Printing the table of processes

    printf("\n\nProcess Table:\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("| Process ID | Arrival Time | Burst Time | Finish Time | Waiting Time | Turn Around Time | Priority | Remaining Time |\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < max_process; i++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].finish_time, processes[i].waiting_time, processes[i].turn_around_time, processes[i].priority, processes[i].remaining_time);
    }

    printf("\nAverage Waiting Time: %f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %f", avg_turn_around_time);


}