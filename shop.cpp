#include "entities.h"

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
	DrawText("1. Apple", 350, 400, 25, GREEN);
	DrawText("2. Corn", 700, 400, 25, RED);
	DrawText("3. Wheat", 350, 500, 25, YELLOW);
	DrawText("4. Wool", 700, 500, 25, WHITE);

}


