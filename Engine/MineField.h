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
			Flagged,
			Revealed,
			Hidden
		};
	private:
		// Vei2 loc; maybe not
	};
public:
	MineField(Graphics& gfx);
	Vei2 GivePos(int x, int y);
	void Draw();
	void DrawBackground();
private:
	static constexpr int height = 15;
	static constexpr int width = 15;
	int Tiles[height*width];
	Graphics &gfx;
};

