#include "entities.h"
#include "raylib.h"
#include <iostream>
#include <string>

constexpr int PLAYER_SPEED = 5;

Player player = {};
Shovel shovel = {};
WateringCan watering_can = {};

void InitialisePlayer()
{
    // TODO: Update your variables here
    player.position = { 0.5f * GetScreenWidth(), 0.5f * GetScreenHeight() };
    player.size = { 0.015f * GetScreenWidth(), 0.05f * GetScreenHeight() };


    //----------------------------------------------------------------------------------
}

void InitialiseTools()
{
    shovel.position = { GetScreenWidth() * 0.6f, GetScreenHeight() * 0.85f };
    watering_can.position = { GetScreenWidth() * 0.02f, GetScreenHeight() * 0.1f };
}

void UpdatePlayer()
{
    Vector2 direction = { 0.f, 0.f };

    if (IsKeyDown(KEY_UP))
    {
        direction.y -= 1;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        direction.y += 1;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        direction.x += 1;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        direction.x -= 1;
    }

    player.position.x += direction.x * PLAYER_SPEED;
    player.position.y += direction.y * PLAYER_SPEED;
}

void DrawPlayer()
{
    int posX = player.position.x;
    int posY = player.position.y;
    int width = player.size.x;
    int height = player.size.y;
    Color color = player.color;

    DrawRectangle(posX, posY, width, height, color);
}

void DrawTools() 
{
    if (!shovel.is_in_player_inventory) {

        DrawRectangleGradientV(shovel.position.x, shovel.position.y, shovel.size.x, shovel.size.y, YELLOW, BROWN);
    }
    if (!watering_can.is_in_player_inventory) {

        DrawRectangleGradientV(watering_can.position.x, watering_can.position.y, watering_can.size.x, watering_can.size.y, DARKBLUE, BLUE);
    }
}

void ToolsGUI() {

    DrawText("Tools:", 0, 5, 20, GOLD);

    if (shovel.is_in_player_inventory) {

        DrawText("Shovel", 0, 25, 10, WHITE);
    }

    if (watering_can.is_in_player_inventory) {

        DrawText("Watering Can", 0, 35, 10, WHITE);
    }    
    
}

void UpdateShovel()
{
    int range = shovel.interact_radius;

    if ((shovel.position.x - range < player.position.x) && (player.position.x < shovel.position.x + range) &&
        (shovel.position.y - range < player.position.y) && (player.position.y < shovel.position.y + range)) {
        shovel.is_in_player_inventory = true;
    }
    bool draw_shovel = shovel.is_in_player_inventory;
}

void UpdateWateringCan()
{
    int range = watering_can.interact_radius;

    if ((watering_can.position.x - range < player.position.x) && (player.position.x < watering_can.position.x + range) &&
        (watering_can.position.y - range < player.position.y) && (player.position.y < watering_can.position.y + range)) {
        watering_can.is_in_player_inventory = true;
        std::cout << "Watering Can Collected" << std::endl;
    }
    bool draw_watering_can = watering_can.is_in_player_inventory;
}
