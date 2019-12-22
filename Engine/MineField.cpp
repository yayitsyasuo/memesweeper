#include "MineField.h"
#include <random>
#include <assert.h>

MineField::MineField(Graphics & gfx)
	:
	gfx(gfx)
{
}

Vei2 MineField::GivePos(int a)
{
	assert(a >= 0);
	if (a > width)
	{
		int y = a / width;
		int x = a - y * width;
		return Vei2(x * SpriteCodex::tileSize, y * SpriteCodex::tileSize);
	}
	else
		return Vei2(a * SpriteCodex::tileSize,0);
}

void MineField::Draw()
{
	DrawBackground();
	int x = 0;
	while (x != (height * width + 1))
	{
		switch (Tiles[x])
		{
		case Tiles::State::Hidden:
			SpriteCodex::DrawTileButton(GivePos(x), gfx);
			break;
		case Tiles::State::Revealed:
			SpriteCodex::DrawTile0(GivePos(x), gfx);
			break;
		}
		x++;

	}
}

void MineField::DrawBackground()
{
	gfx.DrawRect(0, 0,SpriteCodex::tileSize*height, SpriteCodex::tileSize*width, SpriteCodex::baseColor);
}

void MineField::SpawnBOOM()
{
	std::random_device koursi;
	std::mt19937 rng(koursi());
   std::uniform_int_distribution<int> yDist(0,height);
   std::uniform_int_distribution<int> xDist(0, width);
   
   Tiles[ yDist( rng ) * width * SpriteCodex::tileSize + xDist( rng ) ]= Tiles::State::BOOM;
}

void MineField::ChangeState(int x, int y, Tiles::State newState)
{
	Tiles[y * x] = newState;
}

MineField::Tiles::State MineField::Tiles::returnState()
{
	return State();
}
