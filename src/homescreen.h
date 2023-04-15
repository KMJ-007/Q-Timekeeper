#include<raylib.h>
#include<stdio.h>


int homescreen(void){

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("This is home screen!", 190, 200, 20, BLACK);
        EndDrawing();

    }

    return 0;
}