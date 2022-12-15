#include <iostream>
#include <stack>
#include "raylib.h"
#include "../Headers/level.h"
#include "../Headers/entities.h"
#include "../Headers/shop.h"

void RenderLevel();

int main(void)
{
    // Initialization


    InitWindow(1280, 720, "Game");  // Setting the window
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();              //Open audio
    InitialiseLevel();              //Imports textures for houses
    InitialisePlayer();             //Draws player, imports the texture for them
    InitialiseTools();              //Darws tools, imports textures for them
    InitialiseFarming();            //
    InitialiseAnimals();                //
        
    
    // Main game loop

    while (!WindowShouldClose())
    {
        // Update
        UpdatePlayer();            //Updates player's position and texture
        UpdateShovel();            //Updates shovel's state, picked up (?)
        UpdateWateringCan();       //Updates can's state, water level, picked up(?)
        HarvestApples();         //
        UpdateAnimals();         //
        InShop();                  //Rendering menues in shop, managing the shop

        // Draw

        BeginDrawing();            //Open for drawing

        
        RenderLevel();             //Draw the background - Pond, Shop, Field
        RenderTrees();             //Draws the trees
        RenderInventory();         //Draws the inventory on the bottom
        RenderAnimals();        //
        RenderFarmTiles();         //

        OurNotificationWindow();    //Handles every notification
        
        
        Timer();                   //Timer
        Applegrowth();             //
        DrawPlayer();              //Draws Player and their texture
        DrawTools();               //Draw tools and their textures

        EndDrawing();              //Close for drawing

    }
    
    DeinitialisePlayer();          //Unload textures
    CloseAudioDevice();            //Close audio

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
