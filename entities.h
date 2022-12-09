#pragma once
#include "raylib.h"
#include <string>

class Entity
{
public:
    Vector2 size;
    Vector2 position;
    Color color;
};

//*****PLAYER*******

class Player : Entity
{
public:
    Vector2 size = {};
    Vector2 position = {};
    Color color = WHITE;

    Texture2D current_texture;
    Texture2D idle_texture;
    Texture2D walk_left_texture;
    Texture2D walk_right_texture;
    Texture2D back_texture;
    Sound walking_sound;
    Texture2D current_house;
    bool shopping = false;

    //inventory
    int apples = 0;
    int wool = 0;
    int milk = 0;
    int eggs = 0;
    int corn = 9;
    int wheat = 16;

};

//******ANIMALS*******

class Animal : Entity     //TODO: MOVE TO SEPRETE FUNCTION
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

class Cow : Entity
{
    bool milked = false;
};

class Sheep : Entity
{
    bool sheared = false;
};

class Chicken : Entity
{
    bool laid_egg = false;
};

//********CROPS***********

class CornCrop : Entity
{
    enum class Growth_Stage
    {
        EMPTY,
        STAGE_1,
        STAGE_2,
        STAGE_3,
        READY
    };

    bool is_harvestable = false;
};

class WheatCrop : Entity
{
    enum class Growth_Stage
    {
        EMPTY,
        STAGE_1,
        STAGE_2,
        STAGE_3,
        READY
    };

    bool is_harvestable = false;
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

//*********FARMTILE************

class Farmtile : Entity
{
public:
    Vector2 position = {};
    Vector2 size = { 76, 76 };
    Color tile_color = BROWN;
    int stage = 0;                              // (0) not planted 
                                                // (1) planted
                                                // (2) small 
                                                // (3) almost there 
                                                // (4) ready corn;

    bool watered = false;
    Texture2D texture;
    bool corn = true;

    Farmtile(int xpos, int ypos)
    {
        position.x = xpos;
        position.y = ypos;
    }

};

//***********TOOLS************

class Shovel : Entity
{
public:
    Vector2 size = { 20, 15 };
    Vector2 position;
    Color color = YELLOW;
    Texture2D texture;
    bool is_in_player_inventory = false;
    int interact_radius = 20;
};

class WateringCan : Entity
{
public:

    Vector2 size = { 64, 55 };
    Vector2 position;
    Color color = DARKBLUE;
    Texture2D texture;
    bool is_in_player_inventory = false;
    int water_level = 7;
    int interact_radius = 20;
};

//**********SHOP************

class Shop : Entity {

public:

    Vector2 size = {};
    Vector2 position = {};
    Color color = BROWN;

};

//*********FUNCTIONS***********

void InitialisePlayer();
void DeinitialisePlayer();
void UpdatePlayer();
void DrawPlayer();

void RenderInventory();
void DrawTools();
void InitialiseTools();
void UpdateShovel();
void UpdateWateringCan();

void InitialiseLevel();

void OurNotificationWindow();

void InitialiseAnimals();
void RenderAnimals();
void UpdateAnimals();

void Applegrowth();
void HarvestApples();
void InitialiseFarming();
void RenderFarmTiles();

