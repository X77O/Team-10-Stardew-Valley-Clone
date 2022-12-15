#include "../Headers/entities.h"
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <iostream>
#include <vector>
#include "../Headers/shop.h"
#include <map>


constexpr int PLAYER_SPEED = 5;

int y_select = 70;  //coordinates of the selection rectangle

Player player = {};
Shovel shovel = {};
WateringCan watering_can = {};
std::map <std::string, int> buy_pricelist;
std::map <std::string, int> sell_pricelist;
std::map <std::string, int> upgrade_pricelist;
bool upgraded_watercan = false;
int house_tier = 1;


//***************NOTIFICATIONS****************

std::string notification_text = "Welcome to Farm it up!";
int time_to_show = 360;

void Notification(std::string notification, int time_to_show_sec)
{
    time_to_show = time_to_show_sec * 60;
    notification_text = notification;
}

void OurNotificationWindow() {
    if (time_to_show > 0) DrawText(notification_text.c_str(), 350, 270, 15, WHITE);
    if (time_to_show > 0) time_to_show--;
}

//******PLAYER**********
void InitialisePlayer()
{
    player.position = { 0.5f * GetScreenWidth(), 0.5f * GetScreenHeight() };
    player.size = { 0.03f * GetScreenWidth(), 0.055f * GetScreenHeight() };

    Texture2D player_texture_idle = LoadTexture("./Assets/character_femaleAdventurer_idle.png");
    Texture2D player_texture_walk_left = LoadTexture("./Assets/character_femaleAdventurer_walk0.png");
    Texture2D player_texture_back = LoadTexture("./Assets/character_femaleAdventurer_back.png");
    Texture2D player_texture_walk_right = LoadTexture("./Assets/character_femaleAdventurer_walk1.png");

    player.idle_texture = player_texture_idle;
    player.walk_left_texture = player_texture_walk_left;
    player.walk_right_texture = player_texture_walk_right;
    player.back_texture = player_texture_back;

    player.current_texture = player.idle_texture;

    Sound walking_sound = LoadSound("./Assets/walking.wav");
    SetSoundVolume(walking_sound, 0.2f);
    player.walking_sound = walking_sound;

}

void UpdatePlayer() //TODO: MAKE IT NORMAL SPEED IN DIAGONALL
{

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    player.current_texture = player.idle_texture;

    Vector2 direction = { 0.f, 0.f };

    if (IsKeyDown(KEY_UP))
    {
        player.current_texture = player.back_texture;
        direction.y -= 1;
        //PlaySound(player.walking_sound);
    }

    if (IsKeyDown(KEY_DOWN))
    {
        player.current_texture = player.idle_texture;
        direction.y += 1;

    }

    if (IsKeyDown(KEY_RIGHT))
    {
        player.current_texture = player.walk_right_texture;
        direction.x += 1;

    }

    if (IsKeyDown(KEY_LEFT))
    {
        player.current_texture = player.walk_left_texture;
        direction.x -= 1;

    }

    if (player.position.x <= 10)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            player.current_texture = player.idle_texture;
            direction.x = 0;
        }
    }
    if (player.position.x >= width - 10)
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            player.current_texture = player.idle_texture;
            direction.x = 0;
        }
    }
    if (player.position.y <= 20)
    {
        if (IsKeyDown(KEY_UP))
        {
            player.current_texture = player.idle_texture;
            direction.y = 0;
        }
    }
    if (player.position.y >= height - 20)
    {
        if (IsKeyDown(KEY_DOWN))
        {
            player.current_texture = player.idle_texture;
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
    Texture2D current_texture = player.current_texture;
    Rectangle playerRectangle = { 0,0, width, height };
    Vector2 playerCenter = { width / 2, height / 2 };
    Rectangle player = { posX, posY, width, height };

    //DrawRectangle(posX, posY, width, height, color);
    DrawTexturePro(current_texture, playerRectangle, player, playerCenter, 0, RAYWHITE);
}

void DrawTools()
{
    if (!shovel.is_in_player_inventory)
    {
        Texture2D texture = shovel.texture;
        Rectangle shovelRectangle = { 0,0,shovel.size.x , shovel.size.y };
        Vector2 shovel_center = { shovel.size.x, shovel.size.y };
        Rectangle Shovel = { shovel.position.x, shovel.position.y, shovel.size.x * 4, shovel.position.y / 10 };

        //DrawRectangleGradientV(shovel.position.x, shovel.position.y, shovel.size.x, shovel.size.y, YELLOW, BROWN);
        DrawTexturePro(texture, shovelRectangle, Shovel, shovel_center, 0, RAYWHITE);
    }
    if (!watering_can.is_in_player_inventory)
    {
        Texture2D texture = watering_can.texture;
        Rectangle watering_canRectangle = { 0,0,watering_can.size.x, watering_can.size.y };
        Vector2 watering_can_center = { watering_can.size.x / 2, watering_can.size.y / 2 };
        Rectangle water_can = { watering_can.position.x, watering_can.position.y, watering_can.size.x, watering_can.size.y };


        //DrawRectangleGradientV(watering_can.position.x, watering_can.position.y, watering_can.size.x, watering_can.size.y, DARKBLUE, BLUE);
        DrawTexturePro(texture, watering_canRectangle, water_can, watering_can_center, 0, RAYWHITE);
    }
}

void DeinitialisePlayer()
{
    UnloadTexture(player.back_texture);
    UnloadTexture(player.idle_texture);
    UnloadTexture(player.walk_left_texture);
    UnloadTexture(player.walk_right_texture);
    UnloadSound(player.walking_sound);
    UnloadTexture(shovel.texture);
    UnloadTexture(watering_can.texture);
    UnloadTexture(player.current_house);
}


//****************TOOLS*******************

void InitialiseTools()
{
    Texture2D Shovel = LoadTexture("./Assets/tool_shovel.png");
    Texture2D Watering_can = LoadTexture("./Assets/Watering_can.png");

    shovel.texture = Shovel;
    watering_can.texture = Watering_can;

    shovel.position = { GetScreenWidth() * 0.6f, GetScreenHeight() * 0.85f };
    watering_can.position = { GetScreenWidth() * 0.02f, GetScreenHeight() * 0.1f };
}

void UpdateShovel()
{
    int range = shovel.interact_radius;

    if ((shovel.position.x - range < player.position.x) && (player.position.x < shovel.position.x + range) &&
        (shovel.position.y - range < player.position.y) && (player.position.y < shovel.position.y + range))
    {
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
    }

    if (IsKeyDown(KEY_SPACE) && watering_can.is_in_player_inventory) {

        watering_can.water_level--;
    }

    if (IsKeyDown(KEY_E) && watering_can.is_in_player_inventory) {

        if (player.position.x > GetScreenWidth() - 180 && player.position.y > GetScreenHeight() - 180 && !upgraded_watercan) {

            watering_can.water_level = 50;
        }

        else if (player.position.x > GetScreenWidth() - 180 && player.position.y > GetScreenHeight() - 180 && upgraded_watercan) {

            watering_can.water_level = 100;
        }

    }

    if (watering_can.water_level <= 0) {

        Notification("Watering Can is empty! Refill it at the pond!", 5);
    }
}

//****************INVENTORY*******************

void RenderInventory()
{
    int apple_count = player.apples;
    int corn_count = player.corn;
    int wheat_count = player.wheat;
    int wool_count = player.wool;
    int milk_count = player.milk;
    int egg_count = player.eggs;

    std::string apples_counter = "Apples: ";
    std::string corn_counter = "Crops: ";
    std::string milk_counter = "Milk: ";
    std::string wool_counter = "Wool: ";
    std::string eggs_counter = "Eggs: ";


    std::string apple_count_s = std::to_string(apple_count);
    std::string corn_count_s = std::to_string(corn_count);
    std::string wool_count_s = std::to_string(wool_count);
    std::string milk_count_s = std::to_string(milk_count);
    std::string egg_count_s = std::to_string(egg_count);

    DrawText(apples_counter.c_str(), 300, 700, 20, LIGHTGRAY);
    DrawText(apple_count_s.c_str(), 375, 700, 20, ORANGE);

    DrawText(corn_counter.c_str(), 400, 700, 20, LIGHTGRAY);
    DrawText(corn_count_s.c_str(), 470, 700, 20, ORANGE);

    DrawText(wool_counter.c_str(), 500, 700, 20, LIGHTGRAY);
    DrawText(wool_count_s.c_str(), 560, 700, 20, ORANGE);

    DrawText(milk_counter.c_str(), 600, 700, 20, LIGHTGRAY);
    DrawText(milk_count_s.c_str(), 650, 700, 20, ORANGE);

    DrawText(eggs_counter.c_str(), 700, 700, 20, LIGHTGRAY);
    DrawText(egg_count_s.c_str(), 760, 700, 20, ORANGE);


    DrawText("Tools:", 810, 700, 20, LIGHTGRAY);

    if (shovel.is_in_player_inventory) {

        DrawText("Shovel, ", 890, 700, 20, ORANGE);
    }

    if (watering_can.is_in_player_inventory)
    {

        DrawText("Watering Can:", 980, 700, 20, ORANGE);

        std::string level = std::to_string(watering_can.water_level);

        if (watering_can.water_level < 0)
        {
            DrawText("0", 1120, 700, 20, ORANGE);
        }
        else
        {
            DrawText(level.c_str(), 1120, 700, 20, ORANGE);
        }

    }
}

//***********LEVEL****************

void InitialiseLevel()
{
    Texture2D house_1 = LoadTexture(". / Assets / house1.png");
    Texture2D house_2 = LoadTexture(". / Assets / house2.png");
    Texture2D house_3 = LoadTexture(". / Assets / house3.png");

    Texture2D current_house = house_1;
};


//**********APPLES**********

int timer = 1;

std::vector<Apple> apple{};

void Applegrowth()
{
    timer++;
    int rand = GetRandomValue(1, 8);
    if (timer % 1800 == 0 && apple.size() < 40)
    {

        int xp = 0;
        int yp = 0;
        switch (rand) {
        case 1:
            xp = GetRandomValue(110, 180);
            yp = GetRandomValue(20, 80);
            break;
        case 2:
            xp = GetRandomValue(160, 230);
            yp = GetRandomValue(20, 80);
            break;
        case 3:
            xp = GetRandomValue(210, 280);
            yp = GetRandomValue(20, 80);
            break;
        case 4:
            xp = GetRandomValue(260, 330);
            yp = GetRandomValue(20, 80);
            break;
        case 5:
            xp = GetRandomValue(110, 180);
            yp = GetRandomValue(120, 180);
            break;
        case 6:
            xp = GetRandomValue(160, 230);
            yp = GetRandomValue(120, 180);
            break;
        case 7:
            xp = GetRandomValue(210, 280);
            yp = GetRandomValue(120, 180);
            break;
        case 8:
            xp = GetRandomValue(260, 330);
            yp = GetRandomValue(120, 180);
            break;
        }      // <--- x and y position generation


        Apple new_apple(rand, xp, yp);          // ----  Work in Progress  ----
        apple.push_back(new_apple);
    }

    for (Apple& apple : apple)
    {
        DrawCircle(apple.x_pos, apple.y_pos, apple.stage + 2, apple.apple_color);
        if (timer % 600 == 0)
        {
            if (apple.stage != 6) apple.stage++;
            if (apple.stage == 3) apple.apple_color = ORANGE;
            if (apple.stage == 6) apple.apple_color = RED;
        }

    }
}

int TreeLocator()
{
    if (player.position.y < 170 && player.position.y > 90)
    {
        if (player.position.x >= 145 && player.position.x < 175)
        {
            return 1;
        }
        if (player.position.x >= 175 && player.position.x < 205)
        {
            return 2;
        }
        if (player.position.x >= 205 && player.position.x < 235)
        {
            return 3;
        }
        if (player.position.x >= 235 && player.position.x < 265)
        {
            return 4;
        }
    }
    if (player.position.y < 250 && player.position.y >= 170)
    {
        if (player.position.x >= 145 && player.position.x < 175)
        {
            return 5;
        }
        if (player.position.x >= 175 && player.position.x < 205)
        {
            return 6;
        }
        if (player.position.x >= 205 && player.position.x < 235)
        {
            return 7;
        }
        if (player.position.x >= 235 && player.position.x < 265)
        {
            return 8;
        }
    }
}

//APPLE HARVEST RADIUS IS NOT PERFECT, BUT IT WORKS

void HarvestApples()
{
    if (IsKeyDown(KEY_SPACE))
    {
        int tree_harvested = TreeLocator();
        for (int current = 0; current < apple.size(); current++)
        {
            if (apple[current].tree_nr == tree_harvested && apple[current].stage == 6)
            {
                player.apples++;
                apple.erase(apple.begin() + current);
                break;
            }
        }
    }


}

//**********FARMING*******************

std::vector<Farmtile> tile{};

void InitialiseFarming()
{
    Texture2D Spritesheet = LoadTexture("./Assets/Spritesheet.png");

    for (int c = 0; c < 3; c++)
    {
        for (int a = 0; a < 5; a++)
        {
            Farmtile farmtile(GetScreenWidth() * 0.75 + 2 + c * 80, GetScreenHeight() * 0.05 + 2 + a * 80);
            farmtile.texture = Spritesheet;
            tile.push_back(farmtile);
        }
    }

}


void RenderFarmTiles()
{

    if (IsKeyPressed(KEY_C)) y_select = (y_select == 70) ? 90 : 70;

    DrawRectangle(670, y_select, 20, 20, ORANGE);
    std::string corn_count = std::to_string(player.corn);
    DrawText(corn_count.c_str(), 700, 70, 20, YELLOW);
    DrawText("Collected corn: ", 450, 70, 20, BLACK);

    std::string wheat_count = std::to_string(player.wheat);
    DrawText(wheat_count.c_str(), 700, 90, 20, YELLOW);
    DrawText("Collected wheat: ", 450, 90, 20, BLACK);

    for (Farmtile& tile : tile)
    {
        if (IsKeyPressed(KEY_SPACE) && player.position.x >= tile.position.x && player.position.x <= tile.position.x + 76 &&
            player.position.y >= tile.position.y && player.position.y <= tile.position.y + 76)
        {

            //WATERING CORN

            if (tile.watered == false && tile.stage >= 1 && tile.stage != 4 && tile.stage != 9 && watering_can.is_in_player_inventory && watering_can.water_level > 0)
            {
                tile.watered = true;
            }


            //PLANTING

            if (y_select == 70)            //PLANTING  CORN
            {
                if (player.corn >= 9 && tile.stage < 1 && shovel.is_in_player_inventory)
                {

                    tile.stage++;
                    player.corn = player.corn - 9;
                }

                if (player.corn <= 9 && tile.stage < 1 && shovel.is_in_player_inventory)
                {
                    Notification("You need at least 9 seeds of corn to plant corn", 5);
                }

                if (!shovel.is_in_player_inventory) {
                    Notification("You need to have shovel to plant", 5);
                }
            }
            else if (y_select == 90)      //PLANTING  WHEAT
            {
                if (player.wheat >= 16 && tile.stage < 1 && shovel.is_in_player_inventory)
                {

                    tile.stage = 5;
                    player.wheat = player.wheat - 16;
                }

                if (player.corn <= 9 && tile.stage < 1 && shovel.is_in_player_inventory)
                {
                    Notification("You need at least 16 seeds of wheat to plant wheat", 3);
                }

                if (!shovel.is_in_player_inventory) {
                    Notification("You need to have shovel to plant", 3);
                }
            }


            //HARVESTING

            if (tile.stage == 4)       //HARVESTING CORN
            {
                tile.stage = 0;
                int grown_corn = GetRandomValue(14, 30);
                player.corn = player.corn + grown_corn;
                tile.watered = false;
            }
            else if (tile.stage == 9)    //HARVESTING  WHEAT
            {
                tile.stage = 0;
                int wheat_grown = GetRandomValue(19, 40);
                player.wheat = player.wheat + wheat_grown;
                tile.watered = false;
            }


        }



        tile.tile_color = tile.watered ? DARKBROWN : BROWN;
        DrawRectangle(tile.position.x, tile.position.y, tile.size.x, tile.size.y, tile.tile_color);

        switch (tile.stage)
        {
        case 1:
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 2:

            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 95,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 3:
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 65,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 4:
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 35,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 5:
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 350,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 6:
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 320,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 7:
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 290,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 8:
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 250,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;
        case 9:
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 25 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 45 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 220,130,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 45 }, WHITE);
            break;

        default:
            break;
        }
        // ^ SCREAMER ALERT ^ //

        //CORN IS GROWING  (CHANGE "chance_to_grow" TO MAKE CORN GROW FASTER/SLOWER)
        if (tile.corn)
        {
            int chance_to_grow = tile.watered ? GetRandomValue(0, 2000) : GetRandomValue(0, 4000);
            if (chance_to_grow == 0 && tile.stage != 0 && tile.stage != 4)
            {
                tile.stage++;
                tile.watered = false;
            }
        }
        else if (tile.corn == false)
        {
            int chance_to_grow = tile.watered ? GetRandomValue(0, 1600) : GetRandomValue(0, 3500);
            if (chance_to_grow == 0 && tile.stage != 0 && tile.stage != 9)
            {
                tile.stage++;
                tile.watered = false;
            }
        }

    }
}


//***********ANIMALS**************

std::vector<Animal> animals{};


void InitialiseAnimals()
{
    Texture2D Cow_t = LoadTexture("");
    Texture2D Sheep_t = LoadTexture("");
    Texture2D Chicken_t = LoadTexture("");

    for (int c = 1; c < 3; c++)
    {
        Animal sheep("sheep");
        sheep.texture = Sheep_t;
        animals.push_back(sheep);
    }
    for (int c = 1; c < 3; c++)
    {
        Animal chicken("chicken");
        chicken.texture = Chicken_t;
        animals.push_back(chicken);
    }
    for (int c = 1; c < 4; c++)
    {
        Animal cow("cow");
        cow.texture = Cow_t;
        animals.push_back(cow);
    }
}


void UpdateAnimals()
{
    if (IsKeyPressed(KEY_ONE))
    {
        Animal sheep("sheep");

        animals.push_back(sheep);

    }
    if (IsKeyPressed(KEY_TWO))
    {
        Animal chicken("chicken");

        animals.push_back(chicken);
    }
    if (IsKeyPressed(KEY_THREE))
    {
        Animal cow("cow");

        animals.push_back(cow);
    }

    for (Animal& animal : animals)
    {
        if (timer % animal.activity == 0 && animal.ready == false)
        {
            animal.walking = (animal.walking == true) ? false : true;
            if (animal.walking)
            {
                do
                {
                    animal.x_speed = GetRandomValue(0, 100);
                    animal.y_speed = GetRandomValue(0, 100);
                } while (animal.x_speed + animal.y_speed != 100);
                animal.x_direction = GetRandomValue(0, 1);
                if (animal.x_direction == 0) animal.x_direction = -1;
                animal.y_direction = GetRandomValue(0, 1);
                if (animal.y_direction == 0) animal.y_direction = -1;
            }
        }
        if (animal.walking)
        {
            animal.position.x = animal.position.x + animal.x_speed * 0.003 * animal.x_direction;
            animal.position.y = animal.position.y + animal.y_speed * 0.003 * animal.y_direction;

            if (animal.position.x == animal.x_left_border || animal.position.x == animal.x_right_border) animal.x_direction * -1;
            if (animal.position.y == animal.y_top_border || animal.position.y == animal.y_bottom_border) animal.y_direction * -1;

        }

    }
}

void RenderAnimals()
{
    for (Animal& animal : animals)
    {
        if (animal.name == "sheep")
        {
            DrawRectangle(animal.position.x, animal.position.y, 13, 10, WHITE);
        }
        if (animal.name == "chicken")
        {
            DrawRectangle(animal.position.x, animal.position.y, 9, 9, BROWN);
        }
        if (animal.name == "cow")
        {
            DrawRectangle(animal.position.x, animal.position.y, 15, 12, BLACK);
        }
    }
}

//*************SHOP**************

void InitialisePrices() {

    buy_pricelist.insert({ "Corn", 50 });			// Buy menu prices
    buy_pricelist.insert({ "Wheat", 20 });

    sell_pricelist.insert({ "Corn", 5 });			// Sell menu prices
    sell_pricelist.insert({ "Wheat", 2 });
    sell_pricelist.insert({ "Apple", 30 });
    sell_pricelist.insert({ "Wool", 25 });
    sell_pricelist.insert({ "Milk", 15 });
    sell_pricelist.insert({ "Egg", 10 });

    upgrade_pricelist.insert({ "Upgraded Watering Can", 750 });
    upgrade_pricelist.insert({ "Fertilizer for Apple Trees", 500 });
    upgrade_pricelist.insert({ "Tier 1", 1000 });	// Upgrade menu prices
    upgrade_pricelist.insert({ "Tier 2", 2000 });
    upgrade_pricelist.insert({ "Tier 3", 3000 });
}

void BuyingMenu()
{
    if (IsKeyPressed(KEY_A)) {

        if (player.money >= 50) {
            player.money -= 50;
            player.corn++;
        }
        else {
            Notification("You do not have enough money!", 3);
        }
    }

    if (IsKeyPressed(KEY_B)) {
        if (player.money >= 20) {
            player.money -= 20;
            player.wheat++;
        }
        else {
            Notification("You do not have enough money!", 3);
        }
    }
}

void SellingMenu()
{
    if (IsKeyPressed(KEY_A)) {

        if (player.corn >= 1) {
            player.money += 5;
            player.corn--;
            Notification("You sold an item!", 2);
        }
        else {
            Notification("You do not have any corn to sell!", 3);
        }
    }

    if (IsKeyPressed(KEY_B)) {

        if (player.wheat >= 1) {
            player.money += 2;
            player.wheat--;
            Notification("You sold an item!", 2);
        }
        else {
            Notification("You do not have any wheat to sell!", 3);
        }
    }

    if (IsKeyPressed(KEY_C)) {

        if (player.apples >= 1) {
            player.money += 30;
            player.apples--;
            Notification("You sold an item!", 2);
        }
        else {
            Notification("You do not have any apples to sell!", 3);
        }
    }

    if (IsKeyPressed(KEY_D)) {

        if (player.wool >= 1) {
            player.money += 25;
            player.wool--;
            Notification("You sold an item!", 2);
        }
        else {
            Notification("You do not have any wool to sell!", 3);
        }
    }

    if (IsKeyPressed(KEY_E)) {

        if (player.milk >= 1) {
            player.money += 15;
            player.milk--;
            Notification("You sold an item!", 2);
        }
        else {
            Notification("You do not have any milk to sell!", 3);
        }
    }

    if (IsKeyPressed(KEY_F)) {

        if (player.eggs >= 1) {
            player.money += 10;
            player.eggs--;
            Notification("You sold an item!", 2);
        }
        else {
            Notification("You do not have any eggs to sell!", 3);
        }
    }
}

void UpgradeMenu()
{
    
    if (IsKeyPressed(KEY_A)) {

        if (player.money >= 150) {
            player.money -= 150;
            watering_can.water_level = 100;
            upgraded_watercan = true;
        }
        else {
            Notification("You do not have enough money!", 3);
        }
    }

    if (IsKeyPressed(KEY_B)) {
         
        // CODE TO UPGRADE THE RATE FOR APPLES
    }

    if (IsKeyPressed(KEY_C)) {
        if (player.money >= 300 && house_tier == 1) {
            player.money -= 300;
            house_tier = 2;
            // CHANGE THE SPRITE OF THE HOUSE
        }
        else {
            Notification("You do not have enough money or you already have a tier 2 house!", 3);
        }
    }

    if (IsKeyPressed(KEY_D)) {
        if (player.money >= 400 && house_tier == 2) {
            player.money -= 400;
            house_tier = 3;
            // CHANGE THE SPRITE OF THE HOUSE
        }
        else {
            Notification("You do not have enough money or you need to buy the 2nd tier first!", 3);
        }
    }
}

int AskForUserInput() {

	bool input = false;
	if (IsKeyPressed(KEY_ONE)) {
		return 1;
	}

	if (IsKeyPressed(KEY_TWO)) {
		return 2;
	}
	if (IsKeyPressed(KEY_THREE)) {
		return 3;
	}

	if (IsKeyPressed(KEY_FOUR)) {
		return 4;
	}
	else {
		return 0;
	}

}

void ShopUserInput() {

	bool shop_open = true;

	while (shop_open) {
		
	int user_input = AskForUserInput();

		switch (user_input)
		{
		case 1:
			player.buying = !player.buying;
		case 2:
			player.selling = !player.selling;
		case 3:
            player.upgrading = !player.upgrading;
		default:
			shop_open = false;
			break;
		}
	}
}

// The program would keep rendering the next frame so it was difficult to keep the menu and sub menus open in the game.
// As a solution the shopping process is divided over multiple methods with while loops and help of booleans to make sure the correct shop menu is being rendered.

void InShop()
{
    bool inside_shop = (player.position.x > 0 && player.position.x < 170 && player.position.y > GetScreenHeight() - 150 && player.position.y < GetScreenHeight());

    if (IsKeyPressed(KEY_SPACE) && inside_shop) {
        player.shopping = !player.shopping;

        DrawShopMenu();
        ShopUserInput();
    }

    else if (IsKeyPressed(KEY_FOUR) && inside_shop) {
        player.shopping = false;
        return;
    }

    else if (player.shopping && inside_shop && !player.buying && !player.selling && !player.upgrading) {
        DrawShopMenu();
        ShopUserInput();
    }

    else if (player.buying && inside_shop) {
        DrawBuyMenu();
        ShopUserInput();
        BuyingMenu();
    }

    else if (player.selling && inside_shop) {
        DrawSellMenu();
        ShopUserInput();
        SellingMenu();
    }

    else if (player.upgrading && inside_shop) {
        DrawUpgradeMenu();
        ShopUserInput();
        UpgradeMenu();
    }

    else if (!inside_shop) {
        player.shopping = false;
        player.selling = false;
        player.upgrading = false;
    }

    else {
        return;
    }
}



