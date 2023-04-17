#include<stdio.h>
#include<stdlib.h>
#include"priority_non_premeemptive.h"


void sort_process_by_arrival_priority(process_t *processes,int max_process){
    for(int i=0;i<max_process;i++){
        for(int j=0;j<max_process-i-1;j++){
            if(processes[j].arrival_time > processes[j+1].arrival_time){
                process_t temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
            else if(processes[j].arrival_time == processes[j+1].arrival_time){
                if(processes[j].priority > processes[j+1].priority){
                    process_t temp = processes[j];
                    processes[j] = processes[j+1];
                    processes[j+1] = temp;
                }
            }
        }
    }
}

int priority_scheduling(process_t *processes,int max_process,int overhead_time){
    print_name("Priority Scheduling\n");

    int premeemptive=0; // 0 for non premeemptive and 1 for premeemptive
    
    printf(" Non Premeemptive or Premeemptive(0/1): ");
    scanf("%d",&premeemptive);

    

    if(premeemptive==0){
        sort_process_by_arrival_priority(processes,max_process);
        priority_non_premeemptive(processes,max_process,overhead_time);
    }
    else{
        // premeemptive(processes,max_process);
        printf("Premeemptive not implemented yet\n");
    }
    
}