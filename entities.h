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
    int water_level = 0;
    int interact_radius = 8;
};

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


void InitialisePlayer();
void UpdatePlayer();
void DrawPlayer();
void DrawTools();
void InitialiseTools();
void UpdateShovel();
void ToolsGUI();
void UpdateWateringCan();