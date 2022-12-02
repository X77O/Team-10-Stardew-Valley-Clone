
#include <iostream>
#include <stack>
#include "raylib.h"
#include "level.h"
#include "../entities.h"

void RenderLevel();

int main(void)
{
    // Initialization


    InitWindow(1280, 720, "Game");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitialisePlayer();
    InitialiseTools();
    // Main game loop

    while (!WindowShouldClose()) 
    {
        // Update
        UpdatePlayer();
        UpdateShovel();
        UpdateWateringCan();

        // Draw
       
        BeginDrawing();

        RenderLevel();
        RenderTrees();
        Counters();
        Timer();

        DrawPlayer();
        DrawTools();

        EndDrawing();

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}