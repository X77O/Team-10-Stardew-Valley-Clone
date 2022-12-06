#include "raylib.h"
#include <vector>
#include <iostream>
#include <string>

//int timer = 0;
int milisec = 0;
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

void Counters()
{
    std::string tree_counter = "Tree count: ";
    std::string apple_counter = "Apple count: ";
    //std::string apple_count = std::to_string(apple.size());
    std::string count = std::to_string(tree.size());

    DrawText(tree_counter.c_str(), 190, 200, 20, LIGHTGRAY);
    DrawText(count.c_str(), 320, 200, 20, ORANGE);

    DrawText(apple_counter.c_str(), 190, 230, 20, LIGHTGRAY);
    //DrawText(apple_count.c_str(), 320, 230, 20, ORANGE);

}


void Timer() {

    //timer++;
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

    std::string sekonds = std::to_string(sec);
    std::string mili_sekonds = std::to_string(milisec);
    std::string minutes = std::to_string(min);


    DrawText(sekonds.c_str(), 125, 700, 20, WHITE);
    DrawText(minutes.c_str(), 75, 700, 20, WHITE);
    DrawText("Time:     m     s", 10, 700, 20, YELLOW);

}


void RenderLevel() {

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

    DrawRectangle(screenWidth * 0.5, screenHeight * 0.15, 140, 170, BEIGE);                                 //
    DrawRectangle(screenWidth * 0.6, screenHeight * 0.55, 150, 150, BEIGE);                                 // Places for animals
   DrawRectangle(screenWidth * 0.2, screenHeight * 0.4, 160, 170, BEIGE);                                   // 
}