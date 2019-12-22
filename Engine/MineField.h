#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
class MineField
{
public:
	class Tiles {
	public:
		enum class State {
			Hidden,
			Flagged,
			Revealed
		};
	public:
		State returnState();
		bool HasBomb = false;
	private:
		Vei2 loc;
	};
public:
	MineField(Graphics& gfx);
	Vei2 GivePos(int x);
	void Draw();
	void DrawBackground();
	void SpawnBOOM();
	void ChangeState(int x, int y, Tiles::State);
	//Tiles::State ReturnState();
private:
	static constexpr int height = 15;
	static constexpr int width = 15;
	Tiles::State Tiles[height*width] = { Tiles::State::Hidden };
	Graphics &gfx;
};

