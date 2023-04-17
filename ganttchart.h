#include<stdio.h>
#include <raylib.h>

#define screenWidth 800
#define screenHeight 450
#define gantt_chart_box_width 700
#define gantt_chart_box_height 150
#define gantt_chart_x 50
#define gantt_chart_y 200


void draw_chart_bars_with_time_label(int x, int y, int width, int height, int thickness, int time, int process_id, Color color) {
    DrawRectangle(x, y, width, thickness, color);
    // drawing the borders of the bar
    DrawRectangleLines(x, y, width, height, BLACK);
    // drawing the time label
    DrawText(TextFormat("%d", time), x, y + height, 20, BLACK);
    // DrawText(TextFormat("P%d", process_id), x + 5, y + 30, 20, BLACK);
}



// void draw_gantt_chart(process_t processes[], int num_processes, int total_time,int avg_waiting_time, int avg_turnaround_time) {

//     int bar_height = gantt_chart_box_height;
//     int bar_thickness = 2;
//     int bar_x = 60;
//     int bar_y = 200;

//     InitWindow(screenWidth, screenHeight, "Q-Timekepper");
//     SetTargetFPS(60);
    
//     while(!WindowShouldClose()){
//     // if enter key is pressed then close the window
//         if(IsKeyPressed(KEY_ENTER)){
//             CloseWindow();
//         }
//         BeginDrawing();
//         ClearBackground(WHITE);
//         DrawText("gantt chart", 10, 10, 20, BLACK);
//         char num_processes_str[10];
//         sprintf(num_processes_str, "%d", num_processes);
//         DrawText(TextFormat("number of processes: %s", num_processes_str), 10, 40, 17, BLACK);

//         // avarage waiting time
//         char avg_waiting_time_str[10];
//         sprintf(avg_waiting_time_str, "%d", avg_waiting_time);
//         DrawText(TextFormat("avarage waiting time: %s ms", avg_waiting_time_str), 10, 70, 17, BLACK);

//         // avarage turnaround time
//         char avg_turnaround_time_str[10];
//         sprintf(avg_turnaround_time_str, "%d", avg_turnaround_time);
//         DrawText(TextFormat("avarage turnaround time: %s ms", avg_turnaround_time_str), 10, 100, 17, BLACK);

//         // drawing the box for the gantt chart max width would be 600, and max height would be 300 with only borders no color inside the box
//         DrawRectangle(gantt_chart_x, gantt_chart_y, gantt_chart_box_width, gantt_chart_box_height, BLACK);
//         // drawing the interiror of the gantt chart box in white
//         DrawRectangle(gantt_chart_x + 1, gantt_chart_y + 1, gantt_chart_box_width - 2, gantt_chart_box_height - 2, WHITE);

//         draw_chart_bars_with_time_label(bar_x, bar_y, bar_thickness, bar_height, bar_thickness, 0, 1, BLACK);
//         // drawing the bars with time labels, bars spacing should be in proportion to the gantt chart's width
//         int bar_spacing = gantt_chart_box_width / total_time;
//         int bar_width = bar_spacing - bar_thickness;

//         for (int i = 0; i < num_processes; i++) {
//             // calculating start time and finish time using burst time and finish time of the process
//             int start_time = processes[i].finish_time - processes[i].burst_time;
//             int finish_time = processes[i].finish_time;
//             // drawing the bars with time labels
//             draw_chart_bars_with_time_label(bar_x, bar_y, bar_width, bar_height, bar_thickness, start_time, processes[i].process_id, BLACK);
//             draw_chart_bars_with_time_label(bar_x + bar_width, bar_y, bar_width, bar_height, bar_thickness, finish_time, processes[i].process_id, BLACK);
//             // incrementing the x position of the bar
//             bar_x += bar_spacing;
//         }
//         EndDrawing();
//     }

//     CloseWindow();
// }



void draw_gantt_chart(process_t processes[], int num_processes, int total_time, int avg_waiting_time, int avg_turnaround_time) {

    int bar_height = gantt_chart_box_height;
    int bar_thickness = 2;
    int bar_x = 60;
    int bar_y = 200;

    InitWindow(screenWidth, screenHeight, "Q-Timekepper");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        // if enter key is pressed then close the window
        if(IsKeyPressed(KEY_ENTER)){
            CloseWindow();
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("gantt chart", 10, 10, 20, BLACK);
        char num_processes_str[10];
        sprintf(num_processes_str, "%d", num_processes);
        DrawText(TextFormat("number of processes: %s", num_processes_str), 10, 40, 17, BLACK);

        // avarage waiting time
        char avg_waiting_time_str[10];
        sprintf(avg_waiting_time_str, "%d", avg_waiting_time);
        DrawText(TextFormat("average waiting time: %s ms", avg_waiting_time_str), 10, 70, 17, BLACK);

        // avarage turnaround time
        char avg_turnaround_time_str[10];
        sprintf(avg_turnaround_time_str, "%d", avg_turnaround_time);
        DrawText(TextFormat("average turnaround time: %s ms", avg_turnaround_time_str), 10, 100, 17, BLACK);

        // drawing the box for the gantt chart max width would be 600, and max height would be 300 with only borders no color inside the box
        DrawRectangle(gantt_chart_x, gantt_chart_y, gantt_chart_box_width, gantt_chart_box_height, BLACK);
        // drawing the interior of the gantt chart box in white
        DrawRectangle(gantt_chart_x + 1, gantt_chart_y + 1, gantt_chart_box_width - 2, gantt_chart_box_height - 2, WHITE);

        // drawing the bars with time labels, bars spacing should be in proportion to the gantt chart's width
        int bar_spacing = gantt_chart_box_width / total_time;
        int bar_width = bar_spacing - bar_thickness;

        for (int i = 0; i < num_processes; i++) {
            // calculating start time and finish time using burst time and finish time of the process
            int start_time = processes[i].finish_time - processes[i].burst_time;
            int finish_time = processes[i].finish_time;
            // resetting the x position of the bar
            bar_x = 60 + start_time * bar_spacing;
            // drawing the bars with time labels
            draw_chart_bars_with_time_label(bar_x, bar_y, bar_width, bar_height, bar_thickness, start_time, processes[i].process_id, BLACK);
            draw_chart_bars_with_time_label(bar_x + bar_width, bar_y, bar_width, bar_height, bar_thickness, finish_time, processes[i].process_id, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();
}
