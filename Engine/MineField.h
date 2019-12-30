#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Sound.h"
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
		int nNeighboursGimme();
	private:
		int nNeighbours = 0;
		State state = { State::Hidden };
	};
public:
	MineField();
	Vei2 GivePos(const int x) const; // converts into coordinates
	void Draw(Graphics& gfx);
	void DrawBackground(Graphics& gfx);
	void SpawnBOOM();
	void ChangeState(const Vei2& pos, const Tiles::State newState);
	void ChangeStateToFlagged(const Vei2& pos); // // flagged needs tile to be hidden Or ChangeStateToDeFlagged
	bool InsideTheField(const Vei2& pos) const; // that universal Update won't work here
	void countNeighbours();
	bool amifucked();
	bool WinCondition();
	void RevealStuffButBomb(const int x);
	const Vei2 CenteredTopLeft = { 250, 150 };
private:
//	const Vei2 CenteredTopLeft = { 250, 150 };
	const Vei2 CenteredBottomRight = { 250 + height*SpriteCodex::tileSize, 150 + height * SpriteCodex::tileSize };
	static constexpr int height = 15;
	static constexpr int width = 15;
	static constexpr int nBombs = 10;
	bool ufucked = false;
	bool just_once = true; // awkward but fuk it
	int hiddenBois = 0;
	int flaggedBois = 0;
	Sound snd = Sound(L"spayed.wav");
	Tiles Tiles[height*width];
//	Graphics &gfx; FUCK YOU
};

