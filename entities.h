#pragma once
#include "raylib.h"
#include "string"

class Entity
{
public:
    Vector2 size;
    Vector2 position;
    Color color;
};

class Player : Entity
{
public:
    Vector2 size = {};
    Vector2 position = {};
    Color color = BLUE;
    int collected_apple_count = 0;
    int collected_crops = 90;
    int collected_wheat = 90;
};

class Shovel : Entity
{
public:
    Vector2 size = { 10, 20 };
    Vector2 position;
    Color color = YELLOW;
    bool is_in_player_inventory = false;
    int interact_radius = 8;
};

class WateringCan : Entity
{
public:

    Vector2 size = { 40, 25 };
    Vector2 position;
    Color color = DARKBLUE;
    bool is_in_player_inventory = false;
    int water_level = 50;
    int interact_radius = 8;
};

class Apple : Entity
{
public:
    int stage = 0;
    int tree_nr = 0;
    int x_pos = 0;
    int y_pos = 0;
    Color apple_color = YELLOW;
    //bool harvested = false;

    Apple(int tree_number, int x_position, int y_position)
    {
        tree_nr = tree_number;
        x_pos = x_position;
        y_pos = y_position;
    }
};


class Farmtile : Entity
{
public:
    Vector2 position = {};
    Vector2 size = {76, 76};
    Color tile_color = BROWN;
    int stage = 0; // (0) not planted (1) planted (2) small (3) almost there (4) ready corn;
    bool watered = false;
    Texture2D texture;
    bool corn = true;
    
    Farmtile(int xpos, int ypos)
    {
        position.x = xpos;
        position.y = ypos;
    }

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

//DrawRectangle(screenWidth * 0.5, screenHeight * 0.15, 140, 170, BEIGE);                                 //
//DrawRectangle(screenWidth * 0.6, screenHeight * 0.55, 150, 150, BEIGE);                                 // Places for animals
//DrawRectangle(screenWidth * 0.2, screenHeight * 0.4, 160, 170, BEIGE);

class Animal : Entity
{
public:
    Texture texture;
    std::string name;
    Vector2 position;
    int activity;
    bool walking;
    bool ready = false;
    int x_speed = 0;
    int y_speed = 0;
    int x_direction = 0;
    int y_direction = 0;
    int x_left_border;
    int y_top_border;
    int x_right_border;
    int y_bottom_border;

    Animal(std::string type)
    {
        activity = GetRandomValue(100, 300);
        name = type;
        if (type == "sheep")
        {
            position.x = GetRandomValue(GetScreenWidth() * 0.5 + 10, GetScreenWidth() * 0.5 + 130);
            position.y = GetRandomValue(GetScreenHeight() * 0.15 + 10, GetScreenHeight() * 0.15 + 160);
            int x_left_border = GetScreenWidth() * 0.5;
            int y_top_border = GetScreenHeight() * 0.15;
            int x_right_border = GetScreenWidth() * 0.5 + 140;
            int y_bottom_border = GetScreenHeight() * 0.15 + 170;
        }
        if (type == "cow")
        {
            position.x = GetRandomValue(GetScreenWidth() * 0.6 + 10, GetScreenWidth() * 0.6 + 140);
            position.y = GetRandomValue(GetScreenHeight() * 0.55 + 10, GetScreenHeight() * 0.55 + 140);
            int x_left_border = GetScreenWidth() * 0.6;
            int y_top_border = GetScreenHeight() * 0.55;
            int x_right_border = GetScreenWidth() * 0.6 + 150;
            int y_bottom_border = GetScreenHeight() * 0.55 + 150;
        }
        if (type == "chicken")
        {
            position.x = GetRandomValue(GetScreenWidth() * 0.2 + 10, GetScreenWidth() * 0.2 + 150);
            position.y = GetRandomValue(GetScreenHeight() * 0.4 + 10, GetScreenHeight() * 0.4 + 160);
            int x_left_border = GetScreenWidth() * 0.2;
            int y_top_border = GetScreenHeight() * 0.4;
            int x_right_border = GetScreenWidth() * 0.2 + 160;
            int y_bottom_border = GetScreenHeight() * 0.4 + 170;
        }
        
    }
};





void InitialisePlayer();
void UpdatePlayer();
void DrawPlayer();
void HarvestApples();
void InitFarming();
void Farmtilerender();
void DrawTools();
void InitialiseTools();
void ToolsGUI();
void UpdateShovel();
void UpdateWateringCan();
void Notificationwindow();
void InitAnimals();
void RenderAnimals();
void UpdateAnimals();