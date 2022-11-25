/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <iostream>
#include <stack>
#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Game");

    Vector2 center = {(GetScreenWidth()), GetScreenHeight()};

    float outerRadius = 180.f;
    float startAngle = 180.f;
    float endAngle = 270.f;


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGREEN);
        SetWindowTitle("Farm it Up!");

        DrawCircleSector(center, outerRadius, startAngle, endAngle, 0, Fade(SKYBLUE, 0.3f));            // Pond
        DrawCircleSectorLines(center, outerRadius, startAngle, endAngle, 0, BLACK);                     // Pond Outline

        DrawRectangleGradientH(screenWidth * 0.f, screenHeight * 0.80f, 170, 180, DARKBROWN, BROWN);    // Shop
        DrawRectangleLines(screenWidth * 0.f, screenHeight * 0.80f, 169, 181, BLACK);                   // Shop Outline
        DrawText("S H O P !", screenWidth * 0.01f, screenHeight * 0.82f, 30, GOLD);                     // Shop Text

        DrawRectangleGradientH(screenWidth * 0.75f, screenHeight * 0.05f, 420, 720, ORANGE, BEIGE);     // Farmland

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}