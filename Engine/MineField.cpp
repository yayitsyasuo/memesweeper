#include "MineField.h"


MineField::MineField(Graphics & gfx)
	:
	gfx(gfx)
{
}

Vei2 MineField::GivePos(int x, int y)
{
	return Vei2(x*SpriteCodex::tileSize, y*SpriteCodex::tileSize);
}

void MineField::Draw()
{
	DrawBackground();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SpriteCodex::DrawTileButton(GivePos(x, y), gfx);
		}
	}
}

void MineField::DrawBackground()
{
	gfx.DrawRect(0,0,SpriteCodex::tileSize*height, SpriteCodex::tileSize*width, SpriteCodex::baseColor);
}
