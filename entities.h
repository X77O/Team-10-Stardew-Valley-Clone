#pragma once
#include "raylib.h"
#include <string>

class Entity //parent class
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
    Sound claim;
    bool shopping = false;
    bool buying = false;
    bool selling = false;
    bool upgrading = false;
    int apple_growth_rate = 1800;

    //inventory (can edit starting values here)
    int apples = 0;
    int wool = 0;
    int milk = 0;
    int eggs = 0;
    int corn = 9;
    int wheat = 80;
    int money = 0;

};

//**********HOUSE**************

class House  //player's house element
{
public:
    Texture2D current_house;
    Texture2D next_house;
    Texture2D next_next_house;
    bool house1 = true;
    bool house2 = false;
    bool house3 = false;
};

//******ANIMALS*******

class Animal : Entity
{
public:
    Texture texture;
    std::string name;
    Vector2 position;
    Sound sound;
    int activity;
    bool walking;
    bool ready = false;
    int x_speed = 0;
    int y_speed = 0;
    int x_direction = 0;
    int y_direction = 0;

    Animal(std::string type)
    {
        activity = GetRandomValue(100, 300);
        name = type;
        if (type == "sheep")
        {
            position.x = GetRandomValue(GetScreenWidth() * 0.5 + 10, GetScreenWidth() * 0.5 + 130);
            position.y = GetRandomValue(GetScreenHeight() * 0.15 + 10, GetScreenHeight() * 0.15 + 160);
        }

        if (type == "cow")
        {
            position.x = GetRandomValue(GetScreenWidth() * 0.6 + 10, GetScreenWidth() * 0.6 + 140);
            position.y = GetRandomValue(GetScreenHeight() * 0.55 + 10, GetScreenHeight() * 0.55 + 140);
        }

        if (type == "chicken")
        {
            position.x = GetRandomValue(GetScreenWidth() * 0.2 + 10, GetScreenWidth() * 0.2 + 150);
            position.y = GetRandomValue(GetScreenHeight() * 0.4 + 10, GetScreenHeight() * 0.4 + 160);
        }

    }
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

class Arrow
{
public:
    Texture2D texture;
};

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


void OurNotificationWindow();

void InitialiseAnimals();
void RenderAnimals();
void UpdateAnimals();

void Applegrowth();
void HarvestApples();
void InitialiseFarming();
void RenderFarmTiles();
void DeinitialiseAnimalsAndFarm();

void InShop();
void BuyingMenu();
void ShopUserInput();
int AskForUserInput();
void InitialisePrices();

