#include <map>
#include "../Headers/entities.h"
#include <iostream>

void DrawShopMenu()
{
	DrawRectangle((GetScreenWidth() / 2) - 400, (GetScreenHeight() / 2), 700, 200, DARKGRAY);
	DrawText("1. Buy", 350, 400, 25, GREEN);
	DrawText("2. Sell", 700, 400, 25, RED);
	DrawText("3. Upgrade", 350, 500, 25, YELLOW);
	DrawText("4. Exit", 700, 500, 25, WHITE);

}

void DrawBuyMenu()
{
	DrawRectangle((GetScreenWidth() / 2) - 400, (GetScreenHeight() / 2), 700, 200, DARKGRAY);
	DrawText("A. Corn [50]", 350, 400, 25, GREEN);
	DrawText("B. Wheat [20]", 700, 400, 25, RED);
}

void DrawSellMenu()
{
	DrawRectangle((GetScreenWidth() / 2) - 400, (GetScreenHeight() / 2), 700, 200, DARKGRAY);
	DrawText("A. Corn [5]", 350, 400, 25, GREEN);
	DrawText("B. Wheat [2]", 520, 400, 25, RED);
	DrawText("C. Apple [30]", 350, 500, 25, YELLOW);
	DrawText("D. Wool [25]", 520, 500, 25, WHITE);
	DrawText("E. Milk [15]", 700, 400, 25, GOLD);
	DrawText("F. Egg [10]", 700, 500, 25, SKYBLUE);

}

void DrawUpgradeMenu()
{
	DrawRectangle((GetScreenWidth() / 2) - 400, (GetScreenHeight() / 2), 700, 200, DARKGRAY);
	DrawText("A. Watering Can [150]", 300, 400, 25, GREEN);
	DrawText("B. Fertilizer [125]", 650, 400, 25, RED);
	DrawText("C. House Tier 1 [300]", 300, 500, 25, YELLOW);
	DrawText("D. House Tier 2 [400]", 650, 500, 25, WHITE);
}
