#include<stdio.h>
#include<stdlib.h>
#include"scheduling_algo/fcfs.h"
#include"scheduling_algo/sjf.h"
#include"scheduling_algo/priority_scheduling.h"
#include"scheduling_algo/round_robin.h"


void qtimekeeper()
{
    int max_process,algo_choice,overhead_time=0; 
    // pointer to the process
    process_t *processes; 
    
    // asking user for max number of process
    printf("\nEnter the number of processes: ");
    scanf("%d",&max_process);

    // allocating the memory according to the max process
    processes = (process_t *)malloc(max_process * sizeof(process_t));
    if(processes == NULL){
        printf("Memory allocation failed");
        exit(1);
    }

    // asking user for the process details
    

    // asking user for the algorithm choice
    printf("\nWhich algorithm do you want to use for scheduling?\n");
    printf("\n1. First Come First Serve (FCFS)");
    printf("\n2. Shortest Job First (SJF)");
    printf("\n3. Priority Scheduling");
    printf("\n4. Round Robin");
    printf("\n5. Exit");
    printf("\n\nEnter your choice: ");
    scanf("%d",&algo_choice);

    // if exit is choosen then give user a message and exit
    if(algo_choice == 5){
        printf("bye bye see you soon!!!!!\n");
        exit(0);
    }

    if(algo_choice>5 || algo_choice<1){
        printf("Invalid choice");
        exit(1);
    }

    // asking user for the overhead time
    printf("Enter the overhead time: ");
    scanf("%d",&overhead_time);

    printf("overhead time %d\n",overhead_time);

    print_name("Enter the process details");

    
    for(int i=0;i<max_process;i++){
        printf("Enter the arrival time of process %d: ",i+1);
        scanf("%d",&processes[i].arrival_time);
        printf("Enter the burst time of process %d: ",i+1);
        scanf("%d",&processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].process_id = i+1;
        processes[i].completed = 0;
        processes[i].arrived = 0;

        // if priority algo is choosen then also ask for priority
        if(algo_choice == 3){
            printf("Enter the priority of process %d: ",i+1);
            scanf("%d",&processes[i].priority);
        }
        printf("\n");
    }

    // calling the function according to the choice
    switch(algo_choice){
        case 1:
            fcfs(processes,max_process,overhead_time);
            break;
        case 2:
            sjf(processes,max_process,overhead_time);
            break;
        case 3:
            priority_scheduling(processes,max_process,overhead_time);
            break;
        case 4:
            round_robin(processes,max_process,overhead_time);
            break;
        case 5:
            printf("bye bye see you soon!!!!!\n");
            exit(0);
            break;
        default:
            printf("Invalid choice");
            break;
    }

}