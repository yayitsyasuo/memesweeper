#include "MineField.h"
#include <random>
#include <assert.h>
#include <algorithm>
#include "Graphics.h"

MineField::MineField()
{
	for (int i = 0; i < 20; i++)
		SpawnBOOM();
	countNeighbours();
}

Vei2 MineField::GivePos(const int a) const
{
	assert(a >= 0);
	assert(a <= width*height);
	if (a >= width)
	{
		int y =  a / width ;
		int x = a - y * width;
		return Vei2(x * SpriteCodex::tileSize, y * SpriteCodex::tileSize);
	}
	else
		return Vei2(a * SpriteCodex::tileSize,0);
}

void MineField::Draw(Graphics& gfx)
{
	DrawBackground(gfx);
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
			else if (Tiles[x].nNeighboursGimme() == 0)
			{
				SpriteCodex::DrawTile0(GivePos(x), gfx);
			}
			else
				SpriteCodex::DrawNeighbourNumber(Tiles[x].nNeighboursGimme(), GivePos(x), gfx);
			break;
		}
		x++;

	}
}

void MineField::Tiles::UpdateState(const State Newstate)
{
	state = Newstate;
}

void MineField::Tiles::nNeighboursIncrease()
{
	nNeighbours++;
}

int MineField::Tiles::nNeighboursGimme()
{
	return nNeighbours;
}

void MineField::DrawBackground(Graphics& gfx)
{
	const int whyudodistome = SpriteCodex::tileSize*height;
	gfx.DrawRect(0, 0, whyudodistome, whyudodistome, SpriteCodex::baseColor);
}

void MineField::SpawnBOOM()
{
	
	std::random_device koursi;
	std::mt19937 rng(koursi());
   std::uniform_int_distribution<int> yDist(0,height);
   std::uniform_int_distribution<int> xDist(0, width);
   
   Tiles[ yDist( rng ) * width +  xDist( rng ) ].HasBomb = true;
}

bool MineField::InsideTheField(const Vei2 & pos) const
{
	return pos.x <= width*SpriteCodex::tileSize && pos.y < height*SpriteCodex::tileSize;
}

void MineField::countNeighbours()
{ 
	for (int x = width + 1; x <= height * width - width - 1; x++)
	{
		if (!Tiles[x].HasBomb)
		{
			int top = (x - width);
			int bottom = (x + width);

			if (Tiles[top].HasBomb)
				Tiles[x].nNeighboursIncrease();
			if (Tiles[top - 1].HasBomb)
				Tiles[x].nNeighboursIncrease();
			if (Tiles[top + 1].HasBomb)
				Tiles[x].nNeighboursIncrease();
			if (Tiles[x + 1].HasBomb)
				Tiles[x].nNeighboursIncrease();
			if (Tiles[x - 1].HasBomb)
				Tiles[x].nNeighboursIncrease();
			if (Tiles[bottom].HasBomb)
				Tiles[x].nNeighboursIncrease();
			if (Tiles[bottom + 1].HasBomb)
				Tiles[x].nNeighboursIncrease();
			if (Tiles[bottom - 1].HasBomb)
				Tiles[x].nNeighboursIncrease();
		}
	}
}

void MineField::ChangeState(const Vei2& pos, const Tiles::State newState)
{
	assert(pos.x <= width * SpriteCodex::tileSize);
	assert(pos.y <= height * SpriteCodex::tileSize);

	Vei2 ConvertedPos = pos / SpriteCodex::tileSize;
	Tiles[ConvertedPos.y*width + ConvertedPos.x].UpdateState(newState);
}

MineField::Tiles::State MineField::Tiles::returnState() const
{
	return state;
}

void MineField::ChangeStateToFlagged(const Vei2& pos)
{
	assert(pos.x <= width * SpriteCodex::tileSize);
	assert(pos.y <= height * SpriteCodex::tileSize);

	Vei2 ConvertedPos = pos / SpriteCodex::tileSize;
	if (Tiles[ConvertedPos.y*width + ConvertedPos.x].returnState() == Tiles::State::Hidden) // flagged needs tile to be hidden
	{
		Tiles[ConvertedPos.y*width + ConvertedPos.x].UpdateState(Tiles::State::Flagged);
	}
}