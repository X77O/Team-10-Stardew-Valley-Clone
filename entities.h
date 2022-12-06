#pragma once
#include "raylib.h"


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
    Color color = WHITE;
    int collected_apple_count = 0;
    int collected_crops = 90;
    int money = 0;
    bool shopping = false;
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

class Farmtile : Entity
{
public:
    Vector2 position = {};
    Vector2 size = { 76, 76 };
    Color tile_color = BROWN;
    int stage = 0; // (0) not planted (1) planted (2) small (3) almost there (4) ready corn;
    bool watered = false;
    Texture2D texture;
    Farmtile(int xpos, int ypos)
    {
        position.x = xpos;
        position.y = ypos;
    }
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

class Shop : Entity {

public:

    Vector2 size = {};
    Vector2 position = {};
    Color color = BROWN;

};

void InitialisePlayer();
void UpdatePlayer();
void DrawPlayer();
void DrawTools();
void InitialiseTools();
void UpdateShovel();
void ToolsGUI();
void UpdateWateringCan();
void InitFarming();
void HarvestApple();
void FarmtileRender();
void AppleGrowth();
void InShop();
int AskForUserInput();
void ShopUserInput();
void InitialiseShop();
void DrawShop();

