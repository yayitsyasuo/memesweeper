#include "MineField.h"
#include <random>
#include <assert.h>
#include <algorithm>
#include "Graphics.h"

MineField::MineField()
{
	for (int i = 0; i < nBombs; i++)
		SpawnBOOM();
	countNeighbours();
}

Vei2 MineField::GivePos(const int a) const // converts into coordinates
{
//	assert(a >= 0);
//	assert(a <= width*height);
	if (a >= width)
	{
		int y =  a / width ;
		int x = a - y * width;
		return Vei2(CenteredTopLeft.x + x * SpriteCodex::tileSize, CenteredTopLeft.y + y * SpriteCodex::tileSize);
	}
	else
		return Vei2(CenteredTopLeft.x + a * SpriteCodex::tileSize, CenteredTopLeft.y);
}

void MineField::Draw(Graphics& gfx)
{
	DrawBackground(gfx);
	int x = 0;
	if (WinCondition()) // win condition drawing?
	{
		SpriteCodex::DrawWin(Vei2 (350, 300), gfx);
	}
	hiddenBois = 0;    // things for win condition
	flaggedBois = 0;   // things for win condition
	while (x != (height * width))
	{
		switch (Tiles[x].returnState())
		{
		case Tiles::State::Hidden:
			hiddenBois++;
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
				flaggedBois++;
				SpriteCodex::DrawTileButton(GivePos(x), gfx);
				SpriteCodex::DrawTileFlag(GivePos(x), gfx);
			}
			break;
		case Tiles::State::Revealed:
			if (Tiles[x].HasBomb)
			{
				SpriteCodex::DrawTile0(GivePos(x), gfx);
				SpriteCodex::DrawTileBombRed(GivePos(x), gfx);
				if (just_once)
				{
					ufucked = true;
					snd.Play();
					just_once = false;
				}
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
	const int whyudodistome = SpriteCodex::tileSize*height ;
	gfx.DrawRect(CenteredTopLeft.x, CenteredTopLeft.y, CenteredBottomRight.x,
		CenteredBottomRight.y, SpriteCodex::baseColor);
}

void MineField::SpawnBOOM()
{
	
	std::random_device koursi;
	std::mt19937 rng(koursi());
   std::uniform_int_distribution<int> yDist(0,height*width - 1); // -1 cause grid start from 0
   
   Tiles[ yDist( rng ) ].HasBomb = true;
}

bool MineField::InsideTheField(const Vei2 & pos) const
{
	return pos.x <= CenteredTopLeft.x + width * SpriteCodex::tileSize &&
		pos.y <= CenteredTopLeft.y + height * SpriteCodex::tileSize
		&& pos.x >= CenteredTopLeft.x && pos.y >= CenteredTopLeft.y;
}

void MineField::countNeighbours()
{ 
	for (int x = 0; x <= height * width; x++)
	{
		if (Tiles[x].HasBomb)
		{
			const int top = x - width;
			const int bottom = x + width;
			const int right = x + 1;
			const int left = x - 1;

			if (InsideTheField(GivePos(top)))
				Tiles[top].nNeighboursIncrease();
			if (InsideTheField(GivePos(top - 1)) && GivePos(top - 1).y == GivePos(top).y)
				Tiles[top - 1].nNeighboursIncrease();
			if (InsideTheField(GivePos(top + 1)) && GivePos(top + 1).y == GivePos(top).y)
				Tiles[top + 1].nNeighboursIncrease();
				
			
			if (InsideTheField(GivePos(right)) && GivePos(right).y == GivePos(x).y  ) // You wouldn't get it
				Tiles[right].nNeighboursIncrease();
			if (InsideTheField(GivePos(left)) && GivePos(left).y == GivePos(x).y)
				Tiles[left].nNeighboursIncrease();

				
			if (InsideTheField(GivePos(bottom)))
				Tiles[bottom].nNeighboursIncrease();
			if (InsideTheField(GivePos(bottom + 1)) && GivePos(bottom + 1).y == GivePos(bottom).y)
				Tiles[bottom+1].nNeighboursIncrease();
			if (InsideTheField(GivePos(bottom - 1)) && GivePos(bottom - 1).y == GivePos(bottom).y)
					Tiles[bottom-1].nNeighboursIncrease();
			
		}
	}
}

bool MineField::amifucked()
{
	return ufucked;
}

bool MineField::WinCondition()
{

	return hiddenBois == 0 && flaggedBois == nBombs;
}

void MineField::RevealStuffButBomb(const Vei2& pos)
{
	if (Tiles[pos.y * width + pos.x].nNeighboursGimme() == 0) // no number = no bombs nearby
	{
		Vei2 newPos = pos - Vei2 (1,1);
		for (newPos.y; newPos.y <= 1 + pos.y; newPos.y++) //repeat 3 times
		{
			for (newPos.x = pos.x - 1; newPos.x <= 1 + pos.x; newPos.x++)
			{
				//here's the shit it does
				ChangeState(newPos, Tiles::State::Revealed);
				// RevealStuffButBomb( newPos );
			}
		}
	}
	else
		return;

}

void MineField::ChangeState(const Vei2& pos, const Tiles::State newState)
{
	assert(pos.x <= width);
	assert(pos.y <= height);
	assert(pos.x >= 0);
	assert(pos.y >= 0);

	// plane was at first in the left top corner
	Tiles[pos.y*width + pos.x].UpdateState(newState);
}

MineField::Tiles::State MineField::Tiles::returnState() const
{
	return state;
}

void MineField::ChangeStateToFlagged(const Vei2& pos)
{
	assert(pos.x <= CenteredTopLeft.x + width * SpriteCodex::tileSize);
	assert(pos.y <= CenteredTopLeft.y + height * SpriteCodex::tileSize);

	//pos was originally at top left corner, now it's shifted
	Vei2 ConvertedPos = (pos- CenteredTopLeft) / SpriteCodex::tileSize;
	if (Tiles[ConvertedPos.y*width + ConvertedPos.x].returnState() == Tiles::State::Hidden) // flagged needs tile to be hidden
	{
		Tiles[ConvertedPos.y*width + ConvertedPos.x].UpdateState(Tiles::State::Flagged);
	}else
		Tiles[ConvertedPos.y*width + ConvertedPos.x].UpdateState(Tiles::State::Hidden);
	
}