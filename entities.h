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

void InitialisePlayer();
void UpdatePlayer();
void DrawPlayer();




