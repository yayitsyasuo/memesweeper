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
		State returnState() const;
		void UpdateState(const State state);
		bool HasBomb = false;
	private:
		State state = { State::Hidden };
	};
public:
	MineField(Graphics& gfx);
	Vei2 GivePos(const int x) const;
	void Draw();
	void DrawBackground();
	void SpawnBOOM();
	void ChangeState(const Vei2(pos), const Tiles::State newState);
	//Tiles::State ReturnState();
private:
	static constexpr int height = 15;
	static constexpr int width = 15;
	// Tiles::State Tiles[height*width] = { Tiles::State::Hidden }; would be cool but this way
	// I cannot use any function inside Tiles
	// Would be still fine but switch doesn't allow twice the same case 
	Tiles Tiles[height*width];
	Graphics &gfx;
};

