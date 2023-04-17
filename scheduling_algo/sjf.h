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
    printf("\max_processrocess ID\tArrival Time\tBurst Time\tFinish Time\tWaiting Time\tTurn Around Time");
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




struct Node
{
    process_t data;
    struct Node *next;
};


struct Node *remaining_timepriorityInsert(struct Node *queue,  process_t process)
{

    if (!queue)
    {
        queue = (struct Node *)malloc(sizeof(struct Node));
        queue->data = process;
        queue->next = NULL;
        return queue;
    }

    struct Node *t = queue;

    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->data = process;
    new->next = NULL;

    if (t->next == NULL)
    {
        if (t->data.remaining_time < new->data.remaining_time)
        {
            t->next = new;
        }
        else
        {
            new->next = t;
            queue = new;
        }
        return queue;
    }
    if (t->data.remaining_time > new->data.remaining_time)
    {
        new->next = t;
        queue = new;
        return queue;
    }

    while (t->next != NULL && t->next->data.remaining_time < new->data.remaining_time)
    {
        t = t->next;
    }

    new->next = t->next;
    t->next = new;
    return queue;
}

process_t getLowestremaining_timeProcess(struct Node **queue)
{
    process_t *p = (process_t *)malloc(sizeof( process_t));
    *p = (*queue)->data;
    struct Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return *p;
}

void SortByAT(process_t *process, int length)
{
    int swapped = 0;
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if (process[j].arrival_time > process[j + 1].arrival_time)
            {
                // printf("\n\t %d and %d",process[j].arrival_time,process[j + 1].arrival_time);
                swapped = 1;
                process_t temp;
                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
        if (!swapped)
        {
            return;
        }
    }
}


void sjf_premeemptive(process_t * processes, int max_process, int overhead_time){
    int current_time=0,current_process_index = -1, current_process_reamining_time = 0,processCount = 1;
    
    print_name("\max_processremeemptive SJF");
    // sort by arrival time
    sort_processes_by_arrival_time(processes, max_process);

    // create a queue
    struct Node *processQueue = NULL;
    
    // run the processes
    printf("\n--------------------------");
    while (processCount != max_process )
    {
        // Insert Arriving processes in queue;
        for (int i = 0; i < max_process; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].arrived == 0)
            {
                // New Process arrives
                processes[i].arrived = 1;

                if (current_process_index == -1)
                { // NO process initialized
                    current_process_index= i;
                    current_process_reamining_time = processes[i].remaining_time;
                }
                else if (processes[i].remaining_time < processes[current_process_index].remaining_time)
                {
                    // Push running process to Queue
                    processQueue = remaining_timepriorityInsert(processQueue, processes[current_process_index]);

                    if (processes[i].arrival_time != processes[current_process_index].arrival_time) // Process Switching due to PREMPTION
                    {
                        current_time += overhead_time; // Add overhead
                        printf("\n--------------------------");
                    }
                    current_process_index = i;
                    current_process_reamining_time = processes[current_process_index].remaining_time;
                }
                else
                {
                    processQueue = remaining_timepriorityInsert(processQueue, processes[i]);
                }
                // printQueue(processQueue);
            }
        }

        if (current_process_reamining_time == 0 && current_process_index != -1)
        {
            // process completed, CPU free for new process

            if (processes[current_process_index].completed == 0){
                // Fill data for completed process
                processes[current_process_index].finish_time = current_time;
                processes[current_process_index].turn_around_time = processes[current_process_index].finish_time - processes[current_process_index].arrival_time;
                processes[current_process_index].waiting_time = processes[current_process_index].turn_around_time - processes[current_process_index].burst_time;
                processes[current_process_index].completed = 1;

                processCount++;
            }

            if (processQueue == NULL)
            {
                // NO PROCESS ZONE
                current_time++;
                printf("\nXXXXXXXXXXXXXXXXX");
                continue;
            }

            // if (current_process_index == -1)
            // {
            //     // NO initial process
            //     current_process_index = getLowestremaining_timeProcess(&processQueue).process_id;
            //     printf("\n%d", current_process_index);
            //     cprocessremaining_time = process[current_process_index].remaining_time;
            // }
            else
            {
                // Add overhead for switching
                current_time += overhead_time;

                // Give CPU a new Process
                current_process_index = getLowestremaining_timeProcess(&processQueue).process_id;
                // printf("\n%d  and processCount=%d", current_process_index, processCount);
                current_process_reamining_time = processes[current_process_index].remaining_time;
                printf("\n--------------------------");
            }
        }

        current_time++;
        current_process_reamining_time--;
        processes[current_process_index].remaining_time--;

        printf("\n %2d |  P%d  |   %2d  ", current_time, processes[current_process_index].process_id, processes[current_process_index].remaining_time);
    }

    processes[current_process_index].finish_time = current_time - 1 + overhead_time + processes[current_process_index].remaining_time;
    processes[current_process_index].turn_around_time = processes[current_process_index].finish_time - processes[current_process_index].arrival_time;
    processes[current_process_index].waiting_time = processes[current_process_index].turn_around_time - processes[current_process_index].burst_time;

    // PRINT FINAL TABLE and AVERAGES
    float totalTAT = 0, totalWT = 0;

    printf("\n\max_processrocess | ArrivalTime | BurstTime | FinishTime | TurnAroundTime | WaitingTime");
    for (int i = 0; i < max_process; i++)
    {
        processes[i].turn_around_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;

        totalTAT += processes[i].turn_around_time;
        totalWT += processes[i].waiting_time;
        printf("\n   P%d\t    %5d\t%5d\t      %5d\t     %5d\t    %5d", processes[i].process_id + 1, processes[i].arrival_time, processes[i].burst_time, processes[i].finish_time, processes[i].turn_around_time, processes[i].waiting_time);
    }
    printf("\nAverage Turn Around Time: %4.3f ms", totalTAT / (float)max_process);
    printf("\nAverage Waiting Time: %4.3f ms", totalWT / (float)max_process);
    
}



// imax_processuts fcfs(process,max_process);
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

