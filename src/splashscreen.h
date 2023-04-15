#include<raylib.h>
#include<stdio.h>


int splashscreen(void){

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        
        DrawText("Welcome to Q-timekeeper!", 190, 200, 20, BLACK);
        DrawText("A job schduling simulator", 200, 230, 17, DARKGRAY);
        EndDrawing();
        
        if(IsKeyPressed(KEY_ENTER)){
            break;
        }

        // close after 5 seond
        if(GetTime() > 5){
            break;
        }
    }

    return 0;
}