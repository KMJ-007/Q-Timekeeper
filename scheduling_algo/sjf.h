#include<stdio.h>
#include<stdlib.h>

// sort the process by arrival time and burst time
void sort_processes_by_arrival_time_burst_time(process_t *processes, int n, int overhead_time) {
     process_t temp_process;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            // Check which process arrived first
            if(processes[i].arrival_time > processes[j].arrival_time) {
                temp_process = processes[i];
                processes[i] = processes[j];
                processes[j] = temp_process;
            }
            // If processes arrived at the same time, choose the one with shorter burst time
            else if(processes[i].arrival_time == processes[j].arrival_time) {
                if(processes[i].burst_time > processes[j].burst_time) {
                    temp_process = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp_process;
                }
            }
        }
    }
    
    int time = 0;
    for(int i = 0; i < n; i++) {
        // Add overhead time if not the first process
        if(i != 0) {
            time += processes[i-1].burst_time + overhead_time;
        }
        int shortest_burst_time_index = i;
        for(int j = i+1; j < n; j++) {
            if(processes[j].arrival_time <= time && processes[j].burst_time < processes[shortest_burst_time_index].burst_time) {
                shortest_burst_time_index = j;
            }
        }
        temp_process = processes[i];
        processes[i] = processes[shortest_burst_time_index];
        processes[shortest_burst_time_index] = temp_process;
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


void sort_processes_by_arrival_time(process_t *processes, int n) {
    process_t temp_process;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(processes[i].arrival_time > processes[j].arrival_time) {
                temp_process = processes[i];
                processes[i] = processes[j];
                processes[j] = temp_process;
            }
        }
    }
}

// int get_shortest_job_index(process_t *processes, int n, int current_time) {
//     int shortest_job_index = -1;
//     int shortest_job_time = 10000; // a very large value
//     for(int i = 0; i < n; i++) {
//         if(processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
//             if(processes[i].remaining_time < shortest_job_time) {
//                 shortest_job_time = processes[i].remaining_time;
//                 shortest_job_index = i;
//             }
//         }
//     }
//     return shortest_job_index;
// }


void sjf_premeemptive(process_t * processes, int max_process, int overhead_time){
        print_name("\nPremeemptive SJF");
    // int current_time = 0;
    // int completed_jobs = 0;
    // int shortest_job_index = -1;

    // while(completed_jobs < max_process) {
    //     shortest_job_index = get_shortest_job_index(processes, max_process, current_time);

    //     if(shortest_job_index == -1) {
    //         printf("No available jobs at time %d\n", current_time);
    //         current_time++;
    //         continue;
    //     }

    //     processes[shortest_job_index].remaining_time--;

    //     if(processes[shortest_job_index].remaining_time == 0) {
    //         completed_jobs++;
    //         processes[shortest_job_index].finish_time = current_time + 1;
    //         processes[shortest_job_index].turn_around_time = processes[shortest_job_index].finish_time - processes[shortest_job_index].arrival_time;
    //         processes[shortest_job_index].waiting_time = processes[shortest_job_index].turn_around_time - processes[shortest_job_index].burst_time;
    //     }

    //     current_time++;

    //     // apply overhead time if any job in queue
    //     int is_job_available = 0;
    //     for(int i = 0; i < max_process; i++) {
    //         if(processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
    //             is_job_available = 1;
    //             break;
    //         }
    //     }
    //     if(is_job_available) {
    //         current_time += overhead_time;
    //     }
    // }

    // print results
    printf("\nSJF Preemptive Scheduling:\n");
    printf("Process ID\tArrival Time\tBurst Time\finsih Time\tTurnaround Time\tWaiting Time\n");
    for(int i = 0; i < max_process; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].finish_time, processes[i].turn_around_time, processes[i].waiting_time);
    }
}



// inputs fcfs(process,max_process);
int sjf(process_t *processes,int max_process,int overhead_time){
    int current_time=0;
    int premeemptive=0; // 0 for non premeemptive and 1 for premeemptive

    printf(" Non Premeemptive or Premeemptive(0/1): ");
    scanf("%d",&premeemptive);

    
     sort_processes_by_arrival_time_burst_time(processes,max_process,overhead_time);

    if(premeemptive==0){
        sjf_non_premeemptive(processes,max_process,overhead_time);
    }
    else{
        sjf_premeemptive(processes,max_process,overhead_time);
    }
    

    // checking for arrival time and updating the current time

}

