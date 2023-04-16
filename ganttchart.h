#include<stdio.h>
#include <raylib.h>

int ganttchart(void){

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Q-Timekepper");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Gantt Chart", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}