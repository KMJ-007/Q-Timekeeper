#include<raylib.h>
#include<stdio.h>


int homescreen(void){

     GuiLoadStyle("raygui_dark.rgs");

    // Define the dropdown box options
    const char* options[] = {"Option 1", "Option 2", "Option 3"};

    // Define the dropdown box properties
    Rectangle dropdownBox = {100, 100, 150, 30};
    int selectedOption = 0;


    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("This is home screen!", 190, 200, 20, BLACK);
        DrawText(options[selectedOption], 270, 100, 20, BLACK);
        EndDrawing();

    }

    return 0;
}