#include "../entities.h"
#include "raylib.h"

constexpr int PLAYER_SPEED = 5;

Player player = {};


void InitialisePlayer()
{
    // TODO: Update your variables here
    player.position = { 0.5f * GetScreenWidth(), 0.5f * GetScreenHeight() };
    player.size = { 0.03f * GetScreenWidth(), 0.05f * GetScreenHeight() };


    //----------------------------------------------------------------------------------
}

void UpdatePlayer()
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();

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


    if (player.position.x <= 0)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            direction.x = 0;
        }
    }
    if (player.position.x >= width -  player.size.x)
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            direction.x = 0;
        }
    }
    if (player.position.y <= 0)
    {
        if (IsKeyDown(KEY_UP))
        {
            direction.y = 0;
        }
    }
    if (player.position.y >= height - player.size.y)
    {
        if (IsKeyDown(KEY_DOWN))
        {
            direction.y = 0;
        }
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
