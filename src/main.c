#include <raylib.h>
#include "splashscreen.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Hello, Karan!");
    SetTargetFPS(60);

    // for first 5 second show splash screen then show main screen
    splashscreen();
    
    while (!WindowShouldClose())
    {

        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText("Hello Hello", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
