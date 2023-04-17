#include<stdio.h>
#include <raylib.h>

void draw_gantt_chart(process_t processes[], int num_processes, int total_time) {
    int bar_height = 30;
    int bar_width;
    int bar_x = 100;
    int bar_y = 100;
    int time_scale = 10;
    int spacing = 10;

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Q-Timekepper");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("gantt chart", 10, 10, 20, BLACK);

        // Calculate the width of each bar based on the total time and the screen width
        bar_width = (GetScreenWidth() - 2 * bar_x) / total_time;

        // Draw the axis labels
        DrawText("Gantt Chart", 10, 10, 20, BLACK);
        DrawText("Time", 50, 50, 20, BLACK);
        DrawText("Process", 10, bar_y - 20, 20, BLACK);

        // Draw the bars for each process
        for (int i = 0; i < num_processes; i++) {
            // Calculate the start and end times of the process
            int start_time = processes[i].arrival_time;
            int end_time = start_time + processes[i].burst_time;

            // Draw the process label
            char label[10];
            sprintf(label, "P%d", processes[i].process_id);
            DrawText(label, bar_x - 50, bar_y, 20, BLACK);

            // Draw the bars for the process
            for (int t = start_time; t < end_time; t++) {
                // Calculate the position of the bar based on the start time and the time scale
                int x = bar_x + (t - start_time) * bar_width;
                int y = bar_y;
                int width = bar_width;
                int height = bar_height;

                // Draw the bar
                DrawRectangle(x, y, width, height, BLUE);
            }

            // Update the y position for the next process
            bar_y += bar_height + spacing;
        }

        // Draw the time scale
        // for (int t = 0; t <= total_time; t++) {
        //     int x = bar_x + t * bar_width;
        //     int y = 50;
        //     DrawLine(x, y, x, y + 10, BLACK);
        //     if (t % time_scale == 0) {
        //         char label[10];
        //         sprintf(label, "%d", t);
        //         DrawText(label, x - 10, y + 20, 10, BLACK);
        //     }
        // }

        EndDrawing();
    }

    CloseWindow();
}
