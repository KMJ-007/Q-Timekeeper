#include<stdio.h>
#include<stdlib.h>

// sort the process by arrival time and burst time
void sort_processes_by_burst_time(process_t *processes, int n) {
    process_t temp_process;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(processes[i].arrival_time <= processes[j].arrival_time) {
                if(processes[i].burst_time > processes[j].burst_time) {
                    temp_process = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp_process;
                }
            }
            else {
                if(processes[i].burst_time > processes[j].burst_time && processes[i].arrival_time > processes[j].arrival_time) {
                    temp_process = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp_process;
                }
            }
        }
    }
}


void sjf_non_premeemptive(process_t * processes, int max_process, int overhead_time){
    print_name("\nNon-premeemptive SJF");

    int current_time=0;
    int total_waiting_time=0;
    int total_turn_around_time=0;
    
    // run the processes
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

    // calculate the average waiting time and average turnaround time
    float avg_waiting_time = (float)total_waiting_time / max_process;
    float avg_turnaround_time = (float)total_turn_around_time / max_process;

    // printing the process
    printf("\nProcess ID\tArrival Time\tBurst Time\tFinish Time\tWaiting Time\tTurn Around Time");
    for(int i = 0; i < max_process; i++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].finish_time, processes[i].waiting_time, processes[i].turn_around_time);
    }

    printf("\nAverage Waiting Time: %f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %f", avg_turnaround_time);


}

void sjf_premeemptive(process_t * processes, int max_process, int overhead_time){
        print_name("\nPremeemptive SJF");
}



// inputs fcfs(process,max_process);
int sjf(process_t *processes,int max_process,int overhead_time){
    int current_time=0;
    int premeemptive=0; // 0 for non premeemptive and 1 for premeemptive

    printf(" Non Premeemptive or Premeemptive(0/1): ");
    scanf("%d",&premeemptive);

    
    sort_processes_by_burst_time(processes,max_process);

    if(premeemptive==0){
        sjf_non_premeemptive(processes,max_process,overhead_time);
    }
    else{
        sjf_premeemptive(processes,max_process,overhead_time);
    }
    

    // checking for arrival time and updating the current time

}

