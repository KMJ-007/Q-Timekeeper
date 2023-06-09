#include<stdio.h>
#include <raylib.h>



#define screenWidth 800
#define screenHeight 450
#define gantt_chart_box_width 700
#define gantt_chart_box_height 150
#define gantt_chart_x 50
#define gantt_chart_y 200


void draw_chart_bars_with_time_label(int x, int y, int width, int height, int thickness, int time, int process_id, Color color) {
    DrawRectangle(x, y, width, height, BLACK);
    // drawing the borders of the bar
    DrawRectangleLines(x, y, width, height, WHITE);
    // drawing the time label
    DrawText(TextFormat("%d", time), x - 40, y + (height / 2) - 10, 20, WHITE);
    DrawText(TextFormat("P%d", process_id), x + 5, y + 30, 20, WHITE);
}



// karan finale one
void draw_gantt_chart(process_t processes[], int num_processes, int total_time, int avg_waiting_time, int avg_turnaround_time) {

    int bar_height = gantt_chart_box_height;
    int bar_thickness = 2;
    int bar_x = 60;
    int bar_y = 200;
    int chart_width = 800;
    int chart_height = 400;
    float unit_time_width = (float)chart_width / total_time;

    // Initialize window and set target frames per second
    InitWindow(chart_width, chart_height, "Gantt Chart");
    SetTargetFPS(60);

    // Main window loop
    while (!WindowShouldClose()) {

        if(IsKeyPressed(KEY_ENTER)){
            CloseWindow();
        }

        // Begin drawing frame
        BeginDrawing();

        // Clear background
        ClearBackground(WHITE);
        DrawText("gantt chart", 10, 10, 20, BLACK);

        // Draw Gantt chart box dynamically according to the number of processes and total time
        DrawRectangleLines(bar_x, bar_y, gantt_chart_box_width, gantt_chart_box_height, BLACK);
        
        // Draw Gantt chart bars
        for (int i = 0; i < num_processes; i++) {
            float start_time = processes[i].arrival_time;
            float end_time = processes[i].finish_time;
            float duration = end_time - start_time;
            float bar_width = duration * unit_time_width;
            // draw vertical line between finish time and start time of next process
            DrawLineV((Vector2){bar_x + end_time * unit_time_width, bar_y}, (Vector2){bar_x + end_time * unit_time_width, bar_y + bar_height}, BLACK);

            // process label  with respect to the finish time of the process and the start time of the next process
            DrawText(TextFormat("P%d", processes[i].process_id), bar_x + end_time * unit_time_width + 5, bar_y + bar_height - 100, 20, BLACK);
        }

        // Draw time labels
        // Draw time labels
        for (int i = 0; i <= total_time; i++) {
            // draw vertical line at each unit of time
            // DrawLineV((Vector2){bar_x + i * unit_time_width, bar_y}, (Vector2){bar_x + i * unit_time_width, bar_y + bar_height}, BLACK);
            // draw time label at each unit of time
            DrawText(TextFormat("%d", i), bar_x + i * unit_time_width - 5, bar_y + bar_height + 5, 10, BLACK);
        }

        // Draw average waiting time
        DrawText(TextFormat("Average waiting time: %d ms", avg_waiting_time), 10, 40, 20, BLACK);

        // Draw average turnaround time
        DrawText(TextFormat("Average turnaround time: %d ms", avg_turnaround_time), 10, 60, 20, BLACK);

        // End drawing frame
        EndDrawing();
    }

    // Close window and exit
    CloseWindow();
}







//  one with black screen
// void draw_gantt_chart(process_t processes[], int num_processes, int total_time, int avg_waiting_time, int avg_turnaround_time) {

//     int bar_height = gantt_chart_box_height;
//     int bar_thickness = 2;
//     int bar_x = 60;
//     int bar_y = 200;
//     InitAudioDevice();
//     InitWindow(screenWidth, screenHeight, "Q-Timekepper");
//     Sound sound = LoadSound("resources/target.ogg");
//     SetTargetFPS(60);

//     while(!WindowShouldClose()){
//         // if enter key is pressed then close the window
//         // play a sound when space is pressed
//         if(IsKeyPressed(KEY_SPACE)){
//             PlaySound(sound);
//         }
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
//         DrawText(TextFormat("average waiting time: %s ms", avg_waiting_time_str), 10, 70, 17, BLACK);

//         // avarage turnaround time
//         char avg_turnaround_time_str[10];
//         sprintf(avg_turnaround_time_str, "%d", avg_turnaround_time);
//         DrawText(TextFormat("average turnaround time: %s ms", avg_turnaround_time_str), 10, 100, 17, BLACK);

//         // drawing the box for the gantt chart max width would be 600, and max height would be 300 with only borders no color inside the box
//         DrawRectangle(gantt_chart_x, gantt_chart_y, gantt_chart_box_width, gantt_chart_box_height, BLACK);
//         // drawing the interior of the gantt chart box in white
//         DrawRectangle(gantt_chart_x + 1, gantt_chart_y + 1, gantt_chart_box_width - 2, gantt_chart_box_height - 2, WHITE);

//         // drawing the bars with time labels, bars spacing should be in proportion to the gantt chart's width
//         int bar_spacing = gantt_chart_box_width / total_time;
//         int bar_width = bar_spacing - bar_thickness;

//         for (int i = 0; i < num_processes; i++) {
//             // calculating start time and finish time using burst time and finish time of the process
//             int start_time = processes[i].finish_time - processes[i].burst_time;
//             int finish_time = processes[i].finish_time;
//             // resetting the x position of the bar
//             bar_x = 60 + (total_time - finish_time) * bar_spacing - gantt_chart_box_width;
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


// void draw_gantt_chart(process_t processes[], int num_processes, int total_time, int avg_waiting_time, int avg_turnaround_time) {

//     int bar_height = gantt_chart_box_height;
//     int bar_thickness = 2;
//     int bar_x = 60;
//     int bar_y = 200;
//     SetTraceLogLevel(LOG_NONE); // Set the log level to not show any logs

//     InitWindow(screenWidth, screenHeight, "Q-Timekepper");
//     SetTargetFPS(60);
//     TraceLog(LOG_INFO, "procss 1 burst_time = %d", processes[0].burst_time);

//     while(!WindowShouldClose()){
//         // if enter key is pressed then close the window
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
//         DrawText(TextFormat("average waiting time: %s ms", avg_waiting_time_str), 10, 70, 17, BLACK);

//         // avarage turnaround time
//         char avg_turnaround_time_str[10];
//         sprintf(avg_turnaround_time_str, "%d", avg_turnaround_time);
//         DrawText(TextFormat("average turnaround time: %s ms", avg_turnaround_time_str), 10, 100, 17, BLACK);

//         // drawing the box for the gantt chart max width would be 600, and max height would be 300 with only borders no color inside the box
//         // DrawRectangle(gantt_chart_x, gantt_chart_y, gantt_chart_box_width, gantt_chart_box_height, BLACK);
//         // drawing the interior of the gantt chart box in white
//         // DrawRectangle(gantt_chart_x + 1, gantt_chart_y + 1, gantt_chart_box_width - 2, gantt_chart_box_height - 2, WHITE);

//         // drawing the bars with time labels, bars spacing should be in proportion to the gantt chart's width
//         int bar_spacing = gantt_chart_box_width / total_time;
//         int bar_width = bar_spacing - bar_thickness;

//         for (int i = 0; i < num_processes; i++) {
//             // calculating start time and finish time using burst time and finish time of the process
//             int start_time = (processes[i].finish_time - processes[i].burst_time);
//             int finish_time = processes[i].finish_time;
//             // resetting the x position of the bar
//             bar_x = 60 + (total_time - finish_time) * bar_spacing - gantt_chart_box_width;
            

            
//         }
//         EndDrawing();
//     }

//     CloseWindow();
// }
