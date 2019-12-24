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
		void nNeighboursIncrease();
	private:
		int nNeighbours = 0;
		State state = { State::Hidden };
	};
public:
	MineField();
	Vei2 GivePos(const int x) const;
	void Draw(Graphics& gfx);
	void DrawBackground(Graphics& gfx);
	void SpawnBOOM();
	void ChangeState(const Vei2& pos, const Tiles::State newState);
	void ChangeStateToFlagged(const Vei2& pos); // // flagged needs tile to be hidden
	bool InsideTheField(const Vei2& pos) const; // that universal Update won't work here
	void countNeighbours();
	//Tiles::State ReturnState();
private:
	static constexpr int height = 18;
	static constexpr int width = 18;
	// Tiles::State Tiles[height*width] = { Tiles::State::Hidden }; would be cool but this way
	// I cannot use any function inside Tiles
	// Would be still fine but switch doesn't allow twice the same case 
	Tiles Tiles[height*width];
//	Graphics &gfx; FUCK YOU
};

