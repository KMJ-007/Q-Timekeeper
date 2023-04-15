#include <raylib.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitAudioDevice();  
    InitWindow(screenWidth, screenHeight, "Hello, Karan!");
    Sound fxOgg = LoadSound("resources/target.ogg");  
    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER)) PlaySound(fxOgg);  

        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText("Hello, Karan, how are you doing?", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    UnloadSound(fxOgg);     // Unload sound data

    CloseAudioDevice();  
    CloseWindow();

    return 0;
}
