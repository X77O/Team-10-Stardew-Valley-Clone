#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>
#include "../Headers/level.h"
#include "../Headers/entities.h"


//*************TIMER***********
// 
//timer values
int milisec = 0;
int sec = 0;
int min = 0;

void Timer()                                                  //Timer
{
    milisec++;
    if (milisec == 60)
    {
        sec++;
        milisec = 0;
    }
    if (sec == 60)
    {
        min++;
        sec = 0;
    }

    std::string seconds = std::to_string(sec);
    std::string mili_seconds = std::to_string(milisec);
    std::string minutes = std::to_string(min);


    DrawText(seconds.c_str(), 125, 700, 20, BLUE);
    DrawText(minutes.c_str(), 75, 700, 20, BLUE);
    DrawText("Time:     m     s", 10, 700, 20, BLACK);

}

//*******TREES********

struct Tree                                                   //Appletrees in the orchard
{
    int xposition;                                            // tree numbers  (1)  (2)  (3)  (4)
    int tree_number;                                          //   ----->      (5)  (6)  (7)  (8)
    int yposition;
    Color colorOfLeaves;


    Tree(int xpos, int ypos, int tree_nr, Color clrOfLeaves)
    {
        colorOfLeaves = clrOfLeaves;
        tree_number = tree_nr;
        xposition = xpos;
        yposition = ypos;
    }
};

std::vector<Tree> tree{};

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
    DrawRectangle(chunk, chunk * 0.1, chunk * 4, chunk * 3, DARKBROWN);

    for (Tree& tree : tree)
    {
        DrawRectangle(tree.xposition - 7, tree.yposition - 30, 15, 30, BROWN);
        DrawCircle(tree.xposition, tree.yposition - 50, 35, tree.colorOfLeaves);

    }

}

//********LEVEL*************

void RenderLevel() 
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    float outerRadius = 180.f;
    float startAngle = 180.f;
    float endAngle = 270.f;

    Vector2 center = { (GetScreenWidth()), GetScreenHeight() };

    ClearBackground(DARKGREEN);
    SetWindowTitle("Farm it Up!");

    DrawCircleSector(center, outerRadius, startAngle, endAngle, 0, Fade(BLUE, 0.3f));                       // Pond
    DrawCircleSectorLines(center, outerRadius, startAngle, endAngle, 0, BLACK);                             // Pond Outline

    DrawRectangleGradientH(0, screenHeight - 150, 170, 150, DARKBROWN, BROWN);                              // Shop
    DrawText("S H O P !", 15, screenHeight - 140, 30, GOLD);                                                // Shop Text

    DrawRectangleGradientH(screenWidth * 0.75f, screenHeight * 0.05f, 240, 400, ORANGE, BEIGE);             // Farmland

    DrawRectangle(screenWidth * 0.5, screenHeight * 0.15, 200, 230, BEIGE);                                 //Animal fence rectangles
    DrawRectangle(screenWidth * 0.48, screenHeight * 0.55, 330, 180, BEIGE);
    DrawRectangle(screenWidth * 0.2, screenHeight * 0.4, 180, 195, BEIGE);

    DrawRectangle(0, screenHeight * 0.91, screenWidth, 70, Color{ 255, 255, 255, 180 });                    //semi-transparent inventory bar
}

void RenderHowToPlay() 
{

    DrawRectangle((GetScreenWidth() / 2) - 300, (GetScreenHeight() / 2 - 300), 600, 600, Color{ 40,40,40,175 });
    DrawText("W - Move up", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 300) + 5, 30, RAYWHITE);
    DrawText("S - Move down", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 270) + 5, 30, RAYWHITE);
    DrawText("A - Move left", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 240) + 5, 30, RAYWHITE);
    DrawText("D - Move right", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 210) + 5, 30, RAYWHITE);
    DrawText("C - Change current crop", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 180) + 5, 30, RAYWHITE);
    DrawText("E - Refill or use  watering can", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 150) + 5, 30, RAYWHITE);
    DrawText("SPACE - Plant and harvest", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 120) + 5, 30, RAYWHITE);
    DrawText("SPACE - Interact with animals", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 90) + 5, 30, RAYWHITE);
    DrawText("SPACE - Collect apples", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 60) + 5, 30, RAYWHITE);
    DrawText("SPACE & Yellow places - Buy animals", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 30) + 5, 30, RAYWHITE);
    DrawText("SPACE - Open shop", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 - 0) + 5, 30, RAYWHITE);
    DrawText("Controls", (GetScreenWidth() / 2) - 270, (GetScreenHeight() / 2 + 30) + 5, 30, RAYWHITE);
}
