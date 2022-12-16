#include "../Headers/entities.h"
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <iostream>
#include <vector>
#include "../Headers/shop.h"
#include "../Headers/level.h"
#include <map>


constexpr int PLAYER_SPEED = 5;

int x_select = 320;  //coordinates of the selection rectangle

Player player = {};
Shovel shovel = {};
WateringCan watering_can = {};
std::map <std::string, int> buy_pricelist;
std::map <std::string, int> sell_pricelist;
std::map <std::string, int> upgrade_pricelist;
bool upgraded_watercan = false;


//***************NOTIFICATIONS****************

std::string notification_text = "Welcome to Farm it up! Press Tab to see controls";
int time_to_show = 360;

void Notification(std::string notification, int time_to_show_sec)
{
    time_to_show = time_to_show_sec * 60;
    notification_text = notification;
}

void OurNotificationWindow()                    //this is a way of communicating things to the player, 
                                                //you only need message and time, and you can call it anywhere in the code
{
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

    Sound walking_sound = LoadSound("./Assets/walking.mp3");
    SetSoundVolume(walking_sound, 0.2f);
    player.walking_sound = walking_sound;

    Sound claiming_elements = LoadSound("./Assets/ping.mp3");
    SetSoundVolume(claiming_elements, 0.2f);
    player.claim = claiming_elements;

}

Vector2 normalize(Vector2 vector)
{
    float vector_length = sqrtf(vector.x * vector.x + vector.y * vector.y);

    if (vector_length > 0.f) {
        vector.x /= vector_length;
        vector.y /= vector_length;
    }

    return vector;
}

void UpdatePlayer() //TODO: MAKE IT NORMAL SPEED IN DIAGONALL
{

    int width = GetScreenWidth();
    int height = GetScreenHeight();

    player.current_texture = player.idle_texture; //sets texture for idle moments

    Vector2 direction = { 0.f, 0.f };

    if (IsKeyDown(KEY_UP))
    {
        player.current_texture = player.back_texture;
        direction.y -= 1;
        
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

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) //moving strats the sound
    {
        PlaySound(player.walking_sound);
    }

    if (IsSoundPlaying(player.walking_sound))  
    {
        if (IsKeyUp(KEY_UP) && IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT)) //when nobody is moving th sound stops
        {
            StopSound(player.walking_sound);
        }
        
    }

    if (player.position.x <= 10)                    //player bounds
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

    if (player.position.y >= height - 85)
    {
        if (IsKeyDown(KEY_DOWN))
        {
            player.current_texture = player.idle_texture;
            direction.y = 0;
        }
    }
    
    direction = normalize(direction);

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

void DeinitialisePlayer()
{
    UnloadTexture(player.back_texture);
    UnloadTexture(player.idle_texture);
    UnloadTexture(player.walk_left_texture);
    UnloadTexture(player.walk_right_texture);
    UnloadSound(player.walking_sound);
    UnloadTexture(shovel.texture);
    UnloadTexture(watering_can.texture);
}


//****************TOOLS*******************

void InitialiseTools()
{
    Texture2D Shovel = LoadTexture("./Assets/tool_shovel.png");
    Texture2D Watering_can = LoadTexture("./Assets/Watering_can.png");

    shovel.texture = Shovel;
    watering_can.texture = Watering_can;

    shovel.position = { GetScreenWidth() * 0.6f, GetScreenHeight() * 0.83f };
    watering_can.position = { GetScreenWidth() * 0.02f, GetScreenHeight() * 0.1f };
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

void UpdateShovel()
{
    int range = shovel.interact_radius;

    if ((shovel.position.x - range < player.position.x) && (player.position.x < shovel.position.x + range) &&
        (shovel.position.y - range < player.position.y) && (player.position.y < shovel.position.y + range))
    {
        PlaySound(player.claim);
        shovel.is_in_player_inventory = true;
    }
    bool draw_shovel = shovel.is_in_player_inventory;
}

void UpdateWateringCan()
{
        int range = watering_can.interact_radius;

        if ((watering_can.position.x - range < player.position.x) && (player.position.x < watering_can.position.x + range) &&
            (watering_can.position.y - range < player.position.y) && (player.position.y < watering_can.position.y + range)) 
        {
            PlaySound(player.claim);
            watering_can.is_in_player_inventory = true;
        }

        if (IsKeyDown(KEY_W) && watering_can.is_in_player_inventory) {

            watering_can.water_level--;
        }

        if (IsKeyDown(KEY_W) && watering_can.is_in_player_inventory) {

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
    int money = player.money;

    std::string apples_counter = "Apples: ";
    std::string corn_counter = "Corn: ";
    std::string milk_counter = "Milk: ";
    std::string wool_counter = "Wool: ";
    std::string eggs_counter = "Eggs: ";
    std::string wheat_counter = "Wheat: ";
    std::string money_counter = "Money: ";


    std::string apple_count_s = std::to_string(apple_count);
    std::string corn_count_s = std::to_string(corn_count);
    std::string wool_count_s = std::to_string(wool_count);
    std::string milk_count_s = std::to_string(milk_count);
    std::string egg_count_s = std::to_string(egg_count);
    std::string wheat_count_s = std::to_string(wheat_count);
    std::string money_count_s = std::to_string(money);

    DrawText(apples_counter.c_str(), 200, 700, 20, BLACK);
    DrawText(apple_count_s.c_str(), 275, 700, 20, BLUE);

    DrawText(corn_counter.c_str(), 300, 700, 20, BLACK);
    DrawText(corn_count_s.c_str(), 358, 700, 20, BLUE);

    DrawText(wheat_counter.c_str(), 385, 700, 20, BLACK);
    DrawText(wheat_count_s.c_str(), 452, 700, 20, BLUE);

    DrawText(wool_counter.c_str(), 480, 700, 20, BLACK);
    DrawText(wool_count_s.c_str(), 535, 700, 20, BLUE);

    DrawText(milk_counter.c_str(), 560, 700, 20, BLACK);
    DrawText(milk_count_s.c_str(), 605, 700, 20, BLUE);

    DrawText(eggs_counter.c_str(), 635, 700, 20, BLACK);
    DrawText(egg_count_s.c_str(), 695, 700, 20, BLUE);

    DrawText(money_counter.c_str(), 10, 670, 20, BLACK);
    DrawText(money_count_s.c_str(), 85, 670, 20, BLUE);


    DrawText("Tools:", 810, 700, 20, BLACK);

    if (shovel.is_in_player_inventory) {

        DrawText("Shovel, ", 890, 700, 20, BLACK);
    }

    if (watering_can.is_in_player_inventory) 
    {

        DrawText("Watering Can:", 980, 700, 20, BLACK);

        std::string level = std::to_string(watering_can.water_level);

        if(watering_can.water_level < 0) //if the level is below zero, it will always show zero not to confuse player, because you can dump all your water on the ground 
        {
            DrawText("0", 1120, 700, 20, RED);
        }
        else
        {
            DrawText(level.c_str(), 1120, 700, 20, BLUE);
        }
        
    }
}
//*********HOUSE************

House house = {};

void InitialiseHouse()
{
    Texture2D house_1 = LoadTexture("./Assets/house1.png");
    Texture2D house_2 = LoadTexture("./Assets/house2.png");
    Texture2D house_3 = LoadTexture("./Assets/house3.png");

    Texture2D current_house = house_1;
    house.next_house = house_2;
    house.next_next_house = house_3;
    house.current_house = current_house;
};

void UpdateHouse()
{
    if (house.house2)
    {
        house.current_house = house.next_house;
    }

    if (house.house3)
    {
        house.current_house = house.next_next_house;
    }
 
    DrawTextureRec(house.current_house, Rectangle(0, 0, 120, 120), Vector2(450, 400), RAYWHITE);            //Drawing the house, the idea is that you can't go back and the last house is final
}

void DeinitialiseHouse()
{
    UnloadTexture(house.current_house);
    UnloadTexture(house.next_house);
    UnloadTexture(house.next_next_house);
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
        if (player.money >= 60)
        {

            if (player.apple_growth_rate > 225)
            {
                player.apple_growth_rate = player.apple_growth_rate * 0.5;
                player.money -= 60;
            }
            else
            {
                Notification("Apples are already growing at max speed", 3);
            }

        }
        else
        {
            Notification("Not enough money", 3);
        }
    }

    if (IsKeyPressed(KEY_C)) {
        if (player.money >= 300) {
            player.money -= 300;
            house.current_house = house.next_house;
            house.house2 = true;
        }
        else {
            Notification("You do not have enough money or you already have a tier 2 house!", 3);
        }
    }

    if (IsKeyPressed(KEY_D)) {
        if (player.money >= 400 && house.house2) {
            player.money -= 400;
            house.current_house = house.next_next_house;
            house.house3 = true;
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


//**********APPLES**********

int timer = 1;

std::vector<Apple> apple{};

void Applegrowth()
{
    timer++;
    int rand = GetRandomValue(1, 8);
    
    if (timer % player.apple_growth_rate == 0 && apple.size() < 40)
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


        Apple new_apple(rand, xp, yp);          
        apple.push_back(new_apple);
    }

    for (Apple& apple : apple)
    {
        DrawCircle(apple.x_pos, apple.y_pos, apple.stage + 2, apple.apple_color);
        if (player.apple_growth_rate/3 == 0)
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

void HarvestApples()
{
    if (IsKeyDown(KEY_SPACE))
    {
        int tree_harvested = TreeLocator();
        for (int current = 0; current < apple.size(); current++)
        {
            if (apple[current].tree_nr == tree_harvested && apple[current].stage == 6)
            {
                PlaySound(player.claim);
                player.apples++;
                apple.erase(apple.begin() + current);
                break;
            }
        }
    }


}

//**********FARMING*******************

std::vector<Farmtile> tile{};
Arrow arrow = {};

void InitialiseFarming()
{
    Texture2D Spritesheet = LoadTexture("./Assets/Spritesheet.png");
    Texture2D arrow_texture = LoadTexture("./Assets/arrow.png");
    arrow.texture = arrow_texture;

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
    if (IsKeyPressed(KEY_C)) x_select = (x_select == 400) ? 320 : 400;  //changing the seeds to plant

    DrawTextureRec(arrow.texture, Rectangle(0,0,31,34), Vector2(x_select, 660), RAYWHITE);


    for (Farmtile& tile : tile)
    {
        if (IsKeyPressed(KEY_W) && player.position.x >= tile.position.x && player.position.x <= tile.position.x + 76 &&   //Watering tiles
            player.position.y >= tile.position.y && player.position.y <= tile.position.y + 76)
        {
            if (tile.watered == false && tile.stage >= 1 && tile.stage != 4 && tile.stage != 9 && watering_can.is_in_player_inventory && watering_can.water_level > 0)
            {
                tile.watered = true;
            }
        }

        if (IsKeyPressed(KEY_SPACE) && player.position.x >= tile.position.x && player.position.x <= tile.position.x + 76 &&
            player.position.y >= tile.position.y && player.position.y <= tile.position.y + 76)
        {

            //PLANTING

            if (x_select == 320)            //PLANTING  CORN
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
            else if (x_select == 400)      //PLANTING  WHEAT
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
                PlaySound(player.claim);
                tile.stage = 0;
                int grown_corn = GetRandomValue(14, 30);
                player.corn = player.corn + grown_corn;
                tile.watered = false;
            }
            else if (tile.stage == 9)    //HARVESTING  WHEAT
            {
                PlaySound(player.claim);
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

        //CORN IS GROWING
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

    for (int c = 1; c < 3; c++)
    {
        Animal sheep("sheep");
        sheep.texture = LoadTexture("./Assets/animals.png");
        sheep.sound = LoadSound("./Assets/sheep_baa.wav");  
        animals.push_back(sheep);
    }
    for (int c = 1; c < 3; c++)
    {
        Animal chicken("chicken");
        chicken.texture = LoadTexture("./Assets/chicken.png");
        chicken.sound = LoadSound("./Assets/chickens.wav"); 
        animals.push_back(chicken);
    }
    for (int c = 1; c < 4; c++)
    {
        Animal cow("cow");
        cow.texture = LoadTexture("./Assets/animals.png");
        cow.sound = LoadSound("./Assets/cow_moo.wav");
        animals.push_back(cow);
    }
}

void UpdateAnimals()
{

    // BUYING & SPAWNING ANIMALS

    if (player.position.x >= GetScreenWidth() * 0.5 - 40 && player.position.x <= GetScreenWidth() * 0.5 - 10 && player.position.y >= GetScreenHeight() * 0.15 - 10 && player.position.y < GetScreenHeight() * 0.15 + 30 && IsKeyPressed(KEY_SPACE))
    {
        if (player.money >= 35)     //Spawining animals without loading textures and sounds again was not working
        {
            Animal sheep("sheep");
            sheep.texture = LoadTexture("./Assets/animals.png");
            sheep.sound = LoadSound("./Assets/sheep_baa.wav");
            animals.push_back(sheep);
            player.money = player.money - 35;
        }
        else
        {
            Notification("You do not have enough money",6);
        }

    }
    if (player.position.x >= GetScreenWidth() * 0.2 - 40 && player.position.x <= GetScreenWidth() * 0.2 - 10 && player.position.y >= GetScreenHeight() * 0.4 - 10 && player.position.y < GetScreenHeight() * 0.4 + 30 && IsKeyPressed(KEY_SPACE))
    {
        if (player.money >= 25)
        {
            Animal chicken("chicken");
            chicken.texture = LoadTexture("./Assets/chicken.png");
            chicken.sound = LoadSound("./Assets/Chicken.wav");
            animals.push_back(chicken);
            player.money = player.money - 25;
        }
        else
        {
            Notification("You do not have enough money", 6);
        }
    }
    if (player.position.x >= GetScreenWidth() * 0.48 - 40 && GetScreenWidth() * 0.48 - 30 && player.position.y >= GetScreenHeight() * 0.55 - 10 && player.position.y < GetScreenHeight() * 0.55 + 30 && IsKeyPressed(KEY_SPACE))
    {
        if (player.money >= 50)
        {
            Animal cow("cow");
            cow.texture = LoadTexture("./Assets/animals.png");
            cow.sound = LoadSound("./Assets/cow_moo.wav");
            animals.push_back(cow);
            player.money = player.money - 50;
        }
        else
        {
            Notification("You do not have enough money", 6);
        }
    }

    //-------------------------------------------------------

    for (Animal& animal : animals)
    {
        // MILKING COWS

        if (animal.ready && animal.name == "cow")
        {

            if (IsKeyPressed(KEY_SPACE) && player.position.x >= animal.position.x - 30 && player.position.x <= animal.position.x + 30 &&
                player.position.y >= animal.position.y - 30 && player.position.y <= animal.position.y + 30)
            {
                animal.ready = false;
                player.milk++;
            }
        }

        //COLLECT CHICKEN EGGS

        if (animal.ready && animal.name == "chicken")
        {

            if (IsKeyPressed(KEY_SPACE) && player.position.x >= animal.position.x - 30 && player.position.x <= animal.position.x + 30 &&
                player.position.y >= animal.position.y - 30 && player.position.y <= animal.position.y + 30)
            {
                animal.ready = false;
                player.eggs++;
            }
        }

        //GET WOOL FROM SHEEP

        if (animal.ready && animal.name == "sheep")
        {

            if (IsKeyPressed(KEY_SPACE) && player.position.x >= animal.position.x - 30 && player.position.x <= animal.position.x + 30 &&
                player.position.y >= animal.position.y - 30 && player.position.y <= animal.position.y + 30)
            {
                animal.ready = false;
                player.wool++;
            }
        }

        // ANIMALS WALKING

        else if (animal.walking)
        {
            animal.position.x = animal.position.x + animal.x_speed * 0.003 * animal.x_direction;
            animal.position.y = animal.position.y + animal.y_speed * 0.003 * animal.y_direction;

        }

        if (timer % animal.activity == 0 && animal.ready == false)
        {
            int chance_to_be_ready = GetRandomValue(0, 20);
            animal.walking = (animal.walking == true || chance_to_be_ready == 0) ? false : true;
            if (chance_to_be_ready == 0)
            {
                animal.ready = true;
                PlaySound(animal.sound);          //      <-------------  AND I PLAY THE SOUND HERE
            }
            else if (animal.walking)
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


        //BORDERS-------------------------------

        if (animal.name == "sheep")
        {
            if (animal.position.x <= GetScreenWidth() * 0.5 || animal.position.x >= GetScreenWidth() * 0.5 + 150) animal.x_direction *= -1;
            if (animal.position.y <= GetScreenHeight() * 0.15 || animal.position.y >= GetScreenHeight() * 0.15 + 190) animal.y_direction *= -1;
        }

        if (animal.name == "cow")
        {
            if (animal.position.x <= GetScreenWidth() * 0.46 || animal.position.x >= GetScreenWidth() * 0.48 + 280) animal.x_direction *= -1;
            if (animal.position.y <= GetScreenHeight() * 0.55 || animal.position.y >= GetScreenHeight() * 0.55 + 130) animal.y_direction *= -1;
        }

        if (animal.name == "chicken")
        {
            if (animal.position.x <= GetScreenWidth() * 0.2 || animal.position.x >= GetScreenWidth() * 0.2 + 160) animal.x_direction *= -1;
            if (animal.position.y <= GetScreenHeight() * 0.4 || animal.position.y >= GetScreenHeight() * 0.4 + 160) animal.y_direction *= -1;
        }

        //-----------------------------------------

    }

}



void RenderAnimals()
{
    for (Animal& animal : animals)
    {
        if (animal.name == "sheep")
        {
            if (animal.x_direction == -1) DrawTextureRec(animal.texture, Rectangle{ 0, 0, 60, 30 }, Vector2{ animal.position.x, animal.position.y }, WHITE);
            else DrawTextureRec(animal.texture, Rectangle{ 0, 30, 60, 30 }, Vector2{ animal.position.x, animal.position.y }, WHITE);
        }
        if (animal.name == "chicken")
        {
            if (animal.x_direction == -1) DrawTextureRec(animal.texture, Rectangle{ 0, 30, 30, 30 }, Vector2{ animal.position.x, animal.position.y }, WHITE);
            else DrawTextureRec(animal.texture, Rectangle{ 0, 0, 30, 30 }, Vector2{ animal.position.x, animal.position.y }, WHITE);
        }
        if (animal.name == "cow")
        {
            if (animal.x_direction == -1) DrawTextureRec(animal.texture, Rectangle{ 0, 80, 60, 30 }, Vector2{ animal.position.x, animal.position.y }, WHITE);
            else DrawTextureRec(animal.texture, Rectangle{ 0, 110, 60, 40 }, Vector2{ animal.position.x, animal.position.y }, WHITE);
        }

        if (animal.ready)
        {
            DrawRectangle(animal.position.x + 6, animal.position.y - 14, 4, 10, GREEN);             // Rendering the green rectangle for signalizing that the animal is ready to be interacted with
            DrawRectangle(animal.position.x + 6, animal.position.y - 3, 4, 4, GREEN);
        }

        // ANIMAL PURCHASING BUTTONS

        DrawRectangle(GetScreenWidth() * 0.5 - 40, GetScreenHeight() * 0.15, 30, 30, YELLOW);
        DrawRectangle(GetScreenWidth() * 0.48 - 40, GetScreenHeight() * 0.55, 30, 30, YELLOW);
        DrawRectangle(GetScreenWidth() * 0.2 - 40, GetScreenHeight() * 0.4, 30, 30, YELLOW);

        DrawText("35", GetScreenWidth() * 0.5 - 35, GetScreenHeight() * 0.15 + 5, 15, BLACK);
        DrawText("50", GetScreenWidth() * 0.48 - 35, GetScreenHeight() * 0.55 + 5, 15, BLACK);
        DrawText("25", GetScreenWidth() * 0.2 - 35, GetScreenHeight() * 0.4 + 5, 15, BLACK);
    }
}

//DEINITIALISING TEXTURES FROM ANIMALS
void DeinitialiseAnimalsAndFarm()
{
    Animal sheep("sheep");
    Animal chicken("chicken");
    Animal cow("cow");
    

    UnloadTexture(chicken.texture);
    UnloadTexture(cow.texture);
    UnloadTexture(sheep.texture);
    UnloadTexture(arrow.texture);
    UnloadTexture(shovel.texture);
    UnloadTexture(watering_can.texture);

}
