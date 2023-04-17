#include<stdio.h>
#include<stdlib.h>
#include "../process_t.h"
#include "../print_name.h"
#include "../ganttchart.h"

int fcfs(process_t *processes,int max_process, int overhead_time){
    print_name("First Come First Serve (FCFS)");

    int current_time = 0;

    // calculating the waiting time and turn around time for each process
    for(int i=0; i<max_process; i++){
        // first sorting the processes according to the arrival time using bubble sort
        for(int j=0; j<max_process-1; j++){
            if(processes[j].arrival_time > processes[j+1].arrival_time){
                process_t temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
        // if the current time is greater than the arrival time of the process then add the overhead time
        if (current_time - processes[i-1].arrival_time > 0) {
            current_time += overhead_time;
        }

        // if the current time is less than the arrival time of the process then update the current time to the arrival time of the process
        if(current_time < processes[i].arrival_time){
            current_time = processes[i].arrival_time;
        }
        
        // calculating the waiting time and turn around time
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turn_around_time = processes[i].waiting_time + processes[i].burst_time;

        // updating the finish time 
        processes[i].finish_time = current_time + processes[i].burst_time;
        
        
        // updating the current time and moving to the next process
        current_time += processes[i].burst_time;
    }

    // calculating the average waiting time and turn around time of all processes
    int total_waiting_time = 0;
    int total_turn_around_time = 0;
    for(int i=0; i<max_process; i++){
        total_waiting_time += processes[i].waiting_time;
        total_turn_around_time += processes[i].turn_around_time;
    }
    
    printf("total_waiting_time: %d",total_waiting_time);
    printf("total_turn_around_time: %d",total_turn_around_time);
    
    int avg_waiting_time = (total_waiting_time / max_process);
    int avg_turn_around_time = total_turn_around_time / max_process;

    // printing the table
    printf("\nProcess ID\tArrival Time\tBurst Time\tFinish Time\tWaiting Time\tTurn Around Time");
    for(int i=0; i<max_process; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",processes[i].process_id,processes[i].arrival_time,processes[i].burst_time,processes[i].finish_time,processes[i].waiting_time,processes[i].turn_around_time);
    }
    printf("\nAverage Waiting Time: %d ms",avg_waiting_time);
    printf("\nAverage Turn Around Time: %d ms\n",avg_turn_around_time);

    // ask use if he want to see the gantt chart
    char choice;
    printf("Do you want to see the gantt chart? (y/n): ");
    scanf(" %c",&choice);
    if(choice == 'y'){
        draw_gantt_chart(processes,max_process,overhead_time,avg_waiting_time,avg_turn_around_time); //overhead time will automatically increase so it become total time
    }
    
}