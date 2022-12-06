#include "entities.h"
#include "raylib.h"
#include "string"
#include <vector>

/*

                *DON'T FORGET TO DOWNLOAD SPRITESHEET FOR CORN FROM GITHUB*


PUT THIS CLASS BELOW INTO ENTITIES.H

-----------------------------------------------------------

class Farmtile : Entity
{
public:
    Vector2 position = {};
    Vector2 size = {76, 76};
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

----------------------------------------------------------

ADD FOLLOWING VARIABLES TO PLAYER CLASS:       int collected_apple_count = 0;       int collected_crops = 90;    (FRANEK HAD HIS OWN VARIABLES FOR THAT, BUT I'M TOO TIRED TO FIX THAT TODAY)
    
*/

constexpr int PLAYER_SPEED = 5;
int timer = 1;   

int y_select = 70;
// DELETE TIMER FROM LEVEL.CPP

Player player = {};
std::vector<Apple> apple{};

Shovel shovel = {};
WateringCan watering_can = {};

std::string notification_text = "Welcome to Farm it up!";
int time_to_show = 360;

void Notification(std::string notification, int time_to_show_sec)
{
    time_to_show = time_to_show_sec * 60;
    notification_text = notification;
}

void Notificationwindow() {
    if (time_to_show > 0) DrawText(notification_text.c_str(), 350, 270, 15, WHITE);
    if (time_to_show > 0) time_to_show--;
}

void InitialisePlayer()
{
    // TODO: Update your variables here
    player.position = { 0.5f * GetScreenWidth(), 0.5f * GetScreenHeight() };
    player.size = { 0.03f * GetScreenWidth(), 0.05f * GetScreenHeight() };


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

void Applegrowth()
{
    timer++;
    int rand = GetRandomValue(1, 8);
    if (timer % 1800 == 0 && apple.size() < 40)                //CHANGE "1800" IF YOU WANT APPLES TO APPEAR MORE/LESS
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
        }      


        Apple new_apple(rand, xp, yp);          
        apple.push_back(new_apple);
    }

    for (Apple& apple : apple)
    {
        DrawCircle(apple.x_pos, apple.y_pos, apple.stage + 2, apple.apple_color);
        if (timer % 600 == 0)                                                             //CHANGE "600" IF YOU WANT APPLES TO APPEAR MORE/LESS
        {
            if (apple.stage != 6) apple.stage++;
            if (apple.stage == 3) apple.apple_color = ORANGE;
            if (apple.stage == 6) apple.apple_color = RED;
        }

    }
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
        
    }
    bool draw_watering_can = watering_can.is_in_player_inventory;

    if (IsKeyDown(KEY_SPACE) && watering_can.is_in_player_inventory) {

        watering_can.water_level--;
    }

    if (IsKeyDown(KEY_E) && watering_can.is_in_player_inventory) {

        if (player.position.x > GetScreenWidth() - 180 && player.position.y > GetScreenHeight() - 180) {

            watering_can.water_level = 50;
        }

    }

    if (watering_can.water_level <= 0) {

        Notification("Watering Can is empty! Refill it at the pond!", 4);
        
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
                player.collected_apple_count++;
                apple.erase(apple.begin() + current);
                break;
            }
        }
    }

    
    std::string ap_count = std::to_string(player.collected_apple_count);
    DrawText(ap_count.c_str(), 700, 40, 20, YELLOW);
    DrawText("Collected apple count: ", 450, 40, 20, BLACK);

}

std::vector<Farmtile> tile{};

void InitFarming()
{    
    Texture2D Spritesheet = LoadTexture("C:/Users/julij/Desktop/Visby/Programming/Farmitup/Spritesheet.png");
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




void Farmtilerender()
{
    
    if (IsKeyPressed(KEY_C)) y_select = (y_select == 70) ? 90 : 70;

    DrawRectangle(670, y_select, 20, 20, ORANGE);
    std::string corn_count = std::to_string(player.collected_crops);
    DrawText(corn_count.c_str(), 700, 70, 20, YELLOW);
    DrawText("Collected corn: ", 450, 70, 20, BLACK);

    std::string wheat_count = std::to_string(player.collected_wheat);
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
                if (player.collected_crops >= 9 && tile.stage < 1 && shovel.is_in_player_inventory)
                {
                    
                    tile.stage++;
                    player.collected_crops = player.collected_crops - 9;
                }

                if (player.collected_crops <= 9 && tile.stage < 1 && shovel.is_in_player_inventory)
                {
                    Notification("You need at least 9 seeds of corn to plant corn", 5);
                }

                if (!shovel.is_in_player_inventory) {
                    Notification("You need to have shovel to plant", 5);
                }
            }
            else if (y_select == 90)      //PLANTING  WHEAT
            {
                if (player.collected_wheat >= 16 && tile.stage < 1 && shovel.is_in_player_inventory)
                {

                    tile.stage = 5;
                    player.collected_wheat = player.collected_wheat - 16;
                }

                if (player.collected_crops <= 9 && tile.stage < 1 && shovel.is_in_player_inventory)
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
                player.collected_crops = player.collected_crops + grown_corn;
                tile.watered = false;
            }
            else if (tile.stage == 9)    //HARVESTING  WHEAT
            {
                tile.stage = 0;
                int wheat_grown = GetRandomValue(19, 40);
                player.collected_wheat = player.collected_wheat + wheat_grown;
                tile.watered = false;
            }

            
        }
        


        tile.tile_color = tile.watered ? DARKBROWN : BROWN;
        DrawRectangle(tile.position.x, tile.position.y, tile.size.x, tile.size.y, tile.tile_color);
        
        switch (tile.stage)
        {
        case 1:
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x, tile.position.y + 5 }, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 20, tile.position.y + 5}, WHITE);
            DrawTextureRec(tile.texture, Rectangle{ 125,290,30, 30 }, Vector2{ tile.position.x + 40, tile.position.y + 5}, WHITE);
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
            if (chance_to_grow == 0 && tile.stage != 0 && tile.stage != 10)
            {
                tile.stage++;
                tile.watered = false;
            }
        }
        
    }
}

//      ----------------------------       Animals      -----------------------------------------          //

//DrawRectangle(screenWidth * 0.5, screenHeight * 0.15, 140, 170, BEIGE);                                 //
//DrawRectangle(screenWidth * 0.6, screenHeight * 0.55, 150, 150, BEIGE);                                 // Places for animals
//DrawRectangle(screenWidth * 0.2, screenHeight * 0.4, 160, 170, BEIGE);

std::vector<Animal> animals{};


void InitAnimals()
{
    Texture2D Cow_t = LoadTexture("C:/Users/julij/Desktop/Visby/Programming/Farmitup");
    Texture2D Sheep_t = LoadTexture("C:/Users/julij/Desktop/Visby/Programming/Farmitup");
    Texture2D Chicken_t = LoadTexture("C:/Users/julij/Destop/Visby/Programming/Farmitup");

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

void DrawPlayer()
{
    int posX = player.position.x;
    int posY = player.position.y;
    int width = player.size.x;
    int height = player.size.y;
    Color color = player.color;

    DrawRectangle(posX, posY, width, height, color);
}