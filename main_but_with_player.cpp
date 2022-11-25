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

#include "raylib.h"

constexpr int PLAYER_SPEED = 20;

class Entity
{public:
    Vector2 size;
    Vector2 position;
    Color color;
};

class Player : Entity
{public:
    Vector2 size = {};
    Vector2 position = {};
    Color color = BLUE;
};

class Cow : Entity
{

};

class Sheep : Entity
{

};

class Chicken : Entity
{

};

Player player = {};


void DrawPlayer(int posX, int posY, int width, int height, Color color)
{
    DrawRectangle(posX, posY, width, height, color);
}

void DrawBackground()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenWidth();

    Vector2 center = { (GetScreenWidth()), GetScreenHeight() };

    float outerRadius = 180.f;
    float startAngle = 180.f;
    float endAngle = 270.f;

    ClearBackground(DARKGREEN);
    SetWindowTitle("Farm it Up!");


    DrawCircleSector(center, outerRadius, startAngle, endAngle, 0, Fade(SKYBLUE, 0.3f));            // Pond
    DrawCircleSectorLines(center, outerRadius, startAngle, endAngle, 0, BLACK);                     // Pond Outline

    DrawRectangleGradientH(screenWidth * 0.f, screenHeight * 0.80f, 170, 180, DARKBROWN, BROWN);    // Shop
    DrawRectangleLines(screenWidth * 0.f, screenHeight * 0.80f, 169, 181, BLACK);                   // Shop Outline
    DrawText("S H O P !", screenWidth * 0.01f, screenHeight * 0.82f, 30, GOLD);                     // Shop Text

    DrawRectangleGradientH(screenWidth * 0.75f, screenHeight * 0.05f, 420, 720, ORANGE, BEIGE);     // Farmland               // Farmland Outline
}

void InitialiseGame()
{
    // TODO: Update your variables here
    player.position = { 0.5f * GetScreenWidth(), 0.5f * GetScreenHeight() };
    player.size = { 0.03f * GetScreenWidth(), 0.05f * GetScreenHeight() };


//----------------------------------------------------------------------------------
}

void Update()
{
    Vector2 direction = {0.f, 0.f};

    if (IsKeyPressed(KEY_UP))
    {
        direction.y -= 1;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        direction.y += 1;
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        direction.x += 1;
    }
    if (IsKeyPressed(KEY_LEFT))
    {
        direction.x -= 1;
    }

    player.position.x += direction.x * PLAYER_SPEED;
    player.position.y += direction.y * PLAYER_SPEED;

}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Game");
    InitialiseGame();

    SetTargetFPS(60);



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        SetWindowTitle("Farm it up!");

        Update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        DrawBackground();

        DrawPlayer(player.position.x, player.position.y, player.size.x, player.size.y, player.color);

       

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}