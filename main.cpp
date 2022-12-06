
#include <iostream>
#include <stack>
#include "raylib.h"
#include "../level.h"
#include "../entities.h"

void RenderLevel();

int main(void)
{
    // Initialization


    InitWindow(1280, 720, "Game");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitialisePlayer();
    InitialiseTools();
    InitFarming();
    InitAnimals();
    
    // Main game loop

    while (!WindowShouldClose()) 
    {
        // Update
        UpdatePlayer();
        HarvestApples();
        UpdateAnimals();

        // Draw
       
        BeginDrawing();

        

        ToolsGUI();
        UpdateShovel();
        UpdateWateringCan();

        Notificationwindow();

        RenderLevel();
        RenderTrees();

        DrawTools();
        
        RenderAnimals();

        Farmtilerender();

        Counters();
        Timer();
        Applegrowth();
        DrawPlayer();

        EndDrawing();

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}