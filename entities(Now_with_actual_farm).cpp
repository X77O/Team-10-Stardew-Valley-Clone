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
int timer = 0;                                   // DELETE TIMER FROM LEVEL.CPP

Player player = {};
std::vector<Apple> apple{};

void InitialisePlayer()
{
    // TODO: Update your variables here
    player.position = { 0.5f * GetScreenWidth(), 0.5f * GetScreenHeight() };
    player.size = { 0.03f * GetScreenWidth(), 0.05f * GetScreenHeight() };


    //----------------------------------------------------------------------------------
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

    std::string corn_count = std::to_string(player.collected_crops);
    DrawText(corn_count.c_str(), 700, 70, 20, YELLOW);
    DrawText("Collected corn: ", 450, 70, 20, BLACK);
    
    for (Farmtile& tile : tile)
    {
        if (IsKeyPressed(KEY_SPACE) && player.position.x >= tile.position.x && player.position.x <= tile.position.x + 76 &&
            player.position.y >= tile.position.y && player.position.y <= tile.position.y + 76)
        {
            //WATERING CORN

            if (tile.watered == false && tile.stage >= 1 && tile.stage < 4)
            {
                tile.watered = true;
            }
            //PLANTING CORN

            if (player.collected_crops >= 9 && tile.stage < 1)
            {
                tile.stage++;
                player.collected_crops = player.collected_crops - 9;
            }

            //HARVESTING CORN

            if (tile.stage == 4)
            {
                tile.stage = 0;
                int grown_corn = GetRandomValue(14, 30);
                player.collected_crops = player.collected_crops + grown_corn;
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
        default:
            break;       
        }    
        // ^ SCREAMER ALERT ^ //

        //CORN IS GROWING  (CHANGE "chance_to_grow" TO MAKE CORN GROW FASTER/SLOWER)

        int chance_to_grow = tile.watered ? GetRandomValue(0, 2000) : GetRandomValue(0, 4000);
        if(chance_to_grow == 0 && tile.stage != 0 && tile.stage != 4)
        {
            tile.stage++;
            tile.watered = false;
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