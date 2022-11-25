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
#include <random>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
struct Rectangle_Structure                                        // <------------------------FROM HERE
{
    //str = structure
    int str_xpos;
    int str_ypos;
    int str_width;
    int str_height;
    Color color;

    Rectangle_Structure(int xpos, int ypos, int width, int height, Color color)
    {
        str_xpos = xpos;
        str_ypos = ypos;
        str_width = width;
        str_height = height;
        color = color;

        DrawRectangle(xpos, ypos, width, height, color);
    }
};                                                          // <-------------------------------TO HERE, THIS THING TURNED OUT TO BE PRETTY USELESS



void RenderLevel()
{
    //Trees                            
 
    int screenWidth = 1280;
    int screenHeight = 720;
    int chunk = GetScreenHeight() * 0.1;
    //Rectangle_Structure Trees(chunk, chunk * 0.1, chunk * 4, chunk * 3, DARKBROWN);
    Rectangle_Structure Trees(chunk, chunk * 0.1, chunk * 4, chunk * 3, DARKBROWN);

   

    //Tree tree(chunk + 60);

    //DrawRectangle(chunk, screenWidth - chunk, chunk * 4, chunk * 2, BLUE);
   ClearBackground(GREEN);
}

struct Tree
{
    int xpos;        //            (1)  (2)  (3)  (4)
    int tree_number;  // ----->      (5)  (6)  (7)  (8)
    int ypos;
    Color colorOfLeaves;
    bool is_present;

    Tree(int xpos, int ypos, int tree_nr, Color colorOfLeaves)
    {

        DrawRectangle(xpos - 7, ypos - 30, 15, 30, BROWN);
        DrawCircle(xpos, ypos - 50, 35, colorOfLeaves);

        colorOfLeaves = colorOfLeaves;
        tree_number = tree_nr;
    }

    void RenderTrees();

};

void Tree::RenderTrees()
{
    if (is_present) DrawCircle(xpos, ypos - 50, 35, colorOfLeaves);            //Add std::vector, trees should be stored in vector
}

void CreateTrees()
{
    int chunk = GetScreenHeight() * 0.1;
    
    Tree tree1(chunk + 60, chunk + 30, 1, LIME);
    Tree tree2(chunk + 110, chunk + 30, 2, DARKGREEN);
    Tree tree3(chunk + 160, chunk + 30, 3, LIME);
    Tree tree4(chunk + 210, chunk + 30, 4, DARKGREEN);
    Tree tree5(chunk + 70, chunk + 130, 5, LIME);
    Tree tree6(chunk + 120, chunk + 130, 6, DARKGREEN);
    Tree tree7(chunk + 170, chunk + 130, 7, LIME);
    Tree tree8(chunk + 220, chunk + 130, 8, DARKGREEN);

}



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

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
        RenderLevel();
        
        CreateTrees();
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}



