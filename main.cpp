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
    InitialiseHouse();              //Imports textures for houses
    InitialisePlayer();             //Draws player, imports the texture for them
    InitialiseTools();              //Darws tools, imports textures for them
    InitialiseFarming();            //Draws farm
    InitialiseAnimals();            //Draws animals
        
    
    // Main game loop

    while (!WindowShouldClose())
    {
        // Update
        UpdatePlayer();            //Updates player's position and texture
        UpdateHouse();             //Updates the house texture in case player has bought an upgrade
        UpdateShovel();            //Updates shovel's state, picked up (?)
        UpdateWateringCan();       //Updates can's state, water level, picked up(?)
        HarvestApples();           //Updates player inventory and manages apples
        UpdateAnimals();           //Moves animals and handles interaction between them and the player

        // Draw

        BeginDrawing();            //Open for drawing

        
        RenderLevel();             //Draw the background - Pond, Shop, Field
        RenderTrees();             //Draws the trees
        RenderFarmTiles();         //Draws individual elements on the farmland, grows stuff on farm
        RenderAnimals();           //Draws animals
        InShop();                  //Rendering menues in shop, managing the shop
        
        OurNotificationWindow();    //Handles every notification
        
        
        Timer();                   //Timer
        Applegrowth();             //Grows apples
        DrawPlayer();              //Draws Player and their texture
        DrawTools();               //Draw tools and their textures
        RenderInventory();         //Draws the inventory on the bottom

        if (IsKeyDown(KEY_TAB))
        {
            RenderHowToPlay();     //Render semi-translucents How_to_play
        }

        EndDrawing();              //Close for drawing

    }
    
    DeinitialisePlayer();          //Unloading textures and sounds
    DeinitialiseHouse();           //Unloading textures and sounds
    DeinitialiseAnimalsAndFarm();         //Unloading textures
    CloseAudioDevice();            //Close audio

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
