#include "MineField.h"
#include <random>
#include <assert.h>

MineField::MineField(Graphics & gfx)
	:
	gfx(gfx)
{
	for (int i = 0; i < 15; i++)
		SpawnBOOM();
}

Vei2 MineField::GivePos(const int a) const
{
	assert(a >= 0);
	if (a >= width)
	{
		int y =  a / width ;
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
		switch (Tiles[x].returnState())
		{
		case Tiles::State::Hidden:
			SpriteCodex::DrawTileButton(GivePos(x), gfx);
			break;
		case Tiles::State::Flagged:
			SpriteCodex::DrawTileButton(GivePos(x), gfx);
			SpriteCodex::DrawTileFlag(GivePos(x), gfx);
			break;
		case Tiles::State::Revealed:
			if (Tiles[x].HasBomb)
			{
				SpriteCodex::DrawTile0(GivePos(x), gfx);
				SpriteCodex::DrawTileBomb(GivePos(x), gfx);
			}
			else
				SpriteCodex::DrawTile0(GivePos(x), gfx);
			break;
		}
		x++;

	}
}

void MineField::Tiles::UpdateState(const State Newstate)
{
	state = Newstate;
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
   
   Tiles[ yDist( rng ) * xDist( rng ) ].HasBomb = true;
}

void MineField::ChangeState(const Vei2(pos), const Tiles::State newState)
{
	assert(pos.x < width*SpriteCodex::tileSize);
	assert(pos.y < height*SpriteCodex::tileSize);
	Vei2 ConvertedPos = pos / SpriteCodex::tileSize;
	Tiles[ConvertedPos.y*width + ConvertedPos.x].UpdateState(newState);
}

MineField::Tiles::State MineField::Tiles::returnState() const
{
	return state;
}
