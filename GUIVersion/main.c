#include <raylib.h>
#include "splashscreen.h"
#include "homescreen.h"


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Q-Timekepper");
    SetTargetFPS(60);

    // for first 5 second show splash screen then show main screen
    splashscreen();
    homescreen();

    CloseWindow();

    return 0;
}
