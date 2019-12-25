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

Vei2 MineField::GivePos(const int a) const // converts into coordinates
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
	while (x != (height * width))
	{
		switch (Tiles[x].returnState())
		{
		case Tiles::State::Hidden:
			SpriteCodex::DrawTileButton(GivePos(x), gfx);
			if (ufucked)
			{
				if (Tiles[x].HasBomb)
					SpriteCodex::DrawTileBomb(GivePos(x), gfx);
			}
			break;
		case Tiles::State::Flagged:
			if (ufucked)
			{
				SpriteCodex::DrawTileBomb(GivePos(x), gfx);
				if(!Tiles[x].HasBomb)
				SpriteCodex::DrawTileCross(GivePos(x), gfx);
				else 
					SpriteCodex::DrawTileFlag(GivePos(x), gfx);
			}
			else {
				SpriteCodex::DrawTileButton(GivePos(x), gfx);
				SpriteCodex::DrawTileFlag(GivePos(x), gfx);
			}
			break;
		case Tiles::State::Revealed:
			if (Tiles[x].HasBomb)
			{
				SpriteCodex::DrawTile0(GivePos(x), gfx);
				SpriteCodex::DrawTileBombRed(GivePos(x), gfx);
				ufucked = true;
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
   std::uniform_int_distribution<int> yDist(0,height*width);
   
   Tiles[ yDist( rng ) ].HasBomb = true;
}

bool MineField::InsideTheField(const Vei2 & pos) const
{
	return pos.x <= width * SpriteCodex::tileSize && pos.y < height*SpriteCodex::tileSize
		&& pos.x >= 0 && pos.y >= 0;
}

void MineField::countNeighbours()
{ 
	for (int x = 0; x <= height * width; x++)
	{
		if (!Tiles[x].HasBomb)
		{
			const int top = (x - width);
			const int bottom = (x + width);


			if (Tiles[top].HasBomb && InsideTheField(GivePos(top)))
				Tiles[x].nNeighboursIncrease();
			if (Tiles[top - 1].HasBomb && InsideTheField(GivePos(top-1)))
				Tiles[x].nNeighboursIncrease();
			if (Tiles[top + 1].HasBomb && InsideTheField(GivePos(top+1)))
				Tiles[x].nNeighboursIncrease();
			
			
			if (Tiles[x + 1].HasBomb && InsideTheField(GivePos(x+1)) && GivePos(x + 1).y == GivePos(x).y  ) // You wouldn't get it
				Tiles[x].nNeighboursIncrease();
			if (Tiles[x - 1].HasBomb && InsideTheField(GivePos(x-1)) && GivePos(x - 1).y == GivePos(x).y )
				Tiles[x].nNeighboursIncrease();

		
			if (Tiles[bottom].HasBomb && InsideTheField(GivePos(bottom)))
				Tiles[x].nNeighboursIncrease();
			if (Tiles[bottom + 1].HasBomb && InsideTheField(GivePos(bottom+1)))
				Tiles[x].nNeighboursIncrease();
			if (Tiles[bottom - 1].HasBomb && InsideTheField(GivePos(bottom-1)))
				Tiles[x].nNeighboursIncrease();
			
		}
	}
}

bool MineField::amifucked()
{
	return ufucked;
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