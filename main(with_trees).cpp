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
#include <vector>
#include <string>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
/*struct Rectangle_Structure                                   // <------------------------FROM HERE
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
};                                    */                      // <-------------------------------TO HERE, THIS THING TURNED OUT TO BE PRETTY USELESS



void RenderLevel()
{
    //Trees                            
 
    int screenWidth = 1280;
    int screenHeight = 720;
    int chunk = GetScreenHeight() * 0.1;
    //Rectangle_Structure Trees(chunk, chunk * 0.1, chunk * 4, chunk * 3, DARKBROWN);
    DrawRectangle(chunk, chunk * 0.1, chunk * 4, chunk * 3, DARKBROWN);

   

    //Tree tree(chunk + 60);

    //DrawRectangle(chunk, screenWidth - chunk, chunk * 4, chunk * 2, BLUE);
   ClearBackground(GREEN);
}

//Variables

int apple_count = 0;
int milisek = 0;
int sec = 0;
int min = 0;

struct Tree
{
    int xposition;        //            (1)  (2)  (3)  (4)
    int tree_number;  // ----->      (5)  (6)  (7)  (8)
    int yposition;
    Color colorOfLeaves;
    

    Tree(int xpos, int ypos, int tree_nr, Color clrOfLeaves)
    {

        //DrawRectangle(xpos - 7, ypos - 30, 15, 30, BROWN);
        //DrawCircle(xpos, ypos - 50, 35, colorOfLeaves);

        colorOfLeaves = clrOfLeaves;
        tree_number = tree_nr;
        xposition = xpos;
        yposition = ypos;
    }

    //void RenderTrees();

};

struct Apple
{
    int stage = 0;
    int tree_nr = 0;

    Apple(int tree_number)
    {
        tree_nr = tree_number;
    }
};

std::vector<Apple> apple{

};



void Applegrowth()
{
    if (sec == 30 || sec == 59)
    {
        //Apple new_apple();           ----  Work in Progress  ----
    }
}

std::vector<Tree> tree{      

};

void RenderTrees()
{
    int chunk = GetScreenHeight() * 0.1;
    if (tree.size() < 6)
    {
        Tree tree1(chunk + 60, chunk + 30, 1, LIME);
        tree.push_back(tree1);
        Tree tree2(chunk + 110, chunk + 30, 2, DARKGREEN);
        tree.push_back(tree2);
        Tree tree3(chunk + 160, chunk + 30, 3, LIME);
        tree.push_back(tree3);
        Tree tree4(chunk + 210, chunk + 30, 4, DARKGREEN);
        tree.push_back(tree4);
        Tree tree5(chunk + 70, chunk + 130, 5, LIME);
        tree.push_back(tree5);
        Tree tree6(chunk + 120, chunk + 130, 6, DARKGREEN);
        tree.push_back(tree6);
        Tree tree7(chunk + 170, chunk + 130, 7, LIME);
        tree.push_back(tree7);
        Tree tree8(chunk + 220, chunk + 130, 8, DARKGREEN);
        tree.push_back(tree8);
    }
    //if (is_present) DrawCircle(xpos, ypos - 50, 35, colorOfLeaves);            //Add std::vector, trees should be stored in vector
    for (Tree& tree : tree)
    {
        DrawRectangle(tree.xposition - 7, tree.yposition - 30, 15, 30, BROWN);
        DrawCircle(tree.xposition, tree.yposition - 50, 35, tree.colorOfLeaves);
        
    }
    
}

int a = GetRandomValue(0, 9);

void Counters()
{
    std::string tree_counter = "tree count: ";
    std::string apple_counter = "Apple count: ";
    std::string count = std::to_string(tree.size());
    std::string random_check = std::to_string(a);
    
    //tree_counter.push_back(tree.size());
    const char * tree_cnt = tree_counter.c_str();
    const char* coun = count.c_str();

    //SetRandomSeed(GetTime());

    DrawText(tree_cnt, 190, 200, 20, LIGHTGRAY);
    DrawText(coun, 320, 200, 20, ORANGE);
    DrawText(random_check.c_str(), 190, 280, 20, BLACK);
}



void Timer() {
    

    milisek++;
    if (milisek == 60)
    {
        sec++;
        milisek = 0;
    }
    if (sec == 60)
    {
        min++;
        sec = 0;
    }

    std::string sekonds = std::to_string(sec);
    std::string mili_sekonds = std::to_string(milisek);
    std::string minutes = std::to_string(min);


    DrawText(sekonds.c_str(), 125, 700, 20, BLACK);
    DrawText(minutes.c_str(), 75, 700, 20, BLACK);
    DrawText("Time:     m     s", 10, 700, 20, GRAY);

}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    /// <summary>
    
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //Load

    Vector2 center = { (GetScreenWidth()), GetScreenHeight() };
    float outerRadius = 180.f;
    float startAngle = 180.f;
    float endAngle = 270.f;


   // Image player = LoadImage("Programming/Yee-haw! Farm it!/betty_1.png");
    //Texture2D texture = LoadTextureFromImage(player);

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

        SetWindowTitle("Farm it Up!");

        DrawCircleSector(center, outerRadius, startAngle, endAngle, 0, Fade(BLUE, 0.3f));                       // Pond
        DrawCircleSectorLines(center, outerRadius, startAngle, endAngle, 0, BLACK);                             // Pond Outline

        DrawRectangleGradientH(screenWidth - screenWidth, screenHeight - 150, 170, 150, DARKBROWN, BROWN);      // Shop
        DrawText("S H O P !", 15, screenHeight - 140, 30, GOLD);                                                // Shop Text

        DrawRectangleGradientH(screenWidth * 0.75f, screenHeight * 0.05f, 240, 400, ORANGE, BEIGE);             // Farmland
        RenderLevel();
        
        
        
        RenderTrees();
        Counters();
        Timer();
        //DrawTexture(texture, GetScreenWidth()/2, GetScreenHeight() / 2, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    // 
    //UnloadTexture(player);
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}



