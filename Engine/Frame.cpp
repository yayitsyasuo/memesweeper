#include "Frame.h"

Frame::Frame(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Frame::DrawAlles()
{
	Color cc = Colors::Red;
	//left top left tri
	TriLTL(GetLoc(Gap, Gap), GetColor(leftFactor));
	// left bottom left tri
	TriLDL(GetLoc(Gap, gfx.ScreenHeight + 1 - Gap - TriWidth), GetColor(leftFactor));
	//left left RECT
	Rect(Gap, Gap + TriWidth, Gap + TriWidth, gfx.ScreenHeight + 1 - Gap - TriWidth, GetColor(leftFactor));
	//left top right tri
	TriLTL(GetLoc(Gap + TriWidth, Gap + TriWidth), GetColor(rightFactor));
	//left bottom right
	TriLDL(GetLoc(Gap + TriWidth, gfx.ScreenHeight + 1 - Gap - TriWidth - TriWidth), GetColor(rightFactor));
	Rect(Gap + TriWidth, Gap + 2 * TriWidth, Gap + 2 * TriWidth, gfx.ScreenHeight + 1 - Gap - 2 * TriWidth, GetColor(rightFactor));


	//left top left top tri
	TriLTL2(GetLoc(Gap, Gap), GetColor(topFactor));
	//left top left bottom tri
	TriLTL2(GetLoc(Gap + TriWidth, Gap + TriWidth), GetColor(bottomFactor));
	//top top rect
	Rect(Gap + TriWidth, Gap, gfx.ScreenWidth + 1 - TriWidth - Gap, Gap + TriWidth, GetColor(topFactor));
	//top bottom rect
	Rect(Gap + 2 * TriWidth, Gap + TriWidth, gfx.ScreenWidth + 1 - 2 * TriWidth - Gap, Gap + 2 * TriWidth, GetColor(bottomFactor));
	//right top left tri
	TriLDL(GetLoc(gfx.ScreenWidth + 1 - Gap - TriWidth, Gap), GetColor(topFactor));
	//right top left left tri
	TriLDL(GetLoc(gfx.ScreenWidth + 1 - Gap - 2 * TriWidth, Gap + TriWidth), GetColor(bottomFactor));
	//right top right right
	//right top right right bottom
	TriLDL2(GetLoc(gfx.ScreenWidth + 1 - Gap, Gap), GetColor(rightFactor));
	TriLDL2(GetLoc(gfx.ScreenWidth + 1 - Gap - TriWidth, Gap + TriWidth), GetColor(leftFactor));
	//right right rect
	Rect(gfx.ScreenWidth + 1 - Gap - 2 * TriWidth, Gap + 2 * TriWidth, gfx.ScreenWidth + 1 - Gap - TriWidth, gfx.ScreenHeight + 1 - Gap - 2 * TriWidth, GetColor(leftFactor));
	//right left reect
	Rect(gfx.ScreenWidth + 1 - Gap - TriWidth, Gap + TriWidth, gfx.ScreenWidth + 1 - Gap, gfx.ScreenHeight + 1 - Gap - TriWidth, GetColor(rightFactor));

	//left bottom left left
	TriLDL2(GetLoc(Gap + TriWidth, gfx.ScreenHeight + 1 - Gap - TriWidth), GetColor(bottomFactor));
	TriLDL2(GetLoc(Gap + 2 * TriWidth, gfx.ScreenHeight + 1 - Gap - 2 * TriWidth), GetColor(topFactor));

	//right bottom right right
	TriLTL2(GetLoc(gfx.ScreenWidth + 1 - Gap - TriWidth, gfx.ScreenHeight + 1 - Gap - TriWidth), GetColor(rightFactor));
	TriLTL2(GetLoc(gfx.ScreenWidth + 1 - Gap - 2 * TriWidth, gfx.ScreenHeight + 1 - Gap - 2 * TriWidth), GetColor(leftFactor));
	//right bottom left
	TriLTL(GetLoc(gfx.ScreenWidth + 1 - Gap - TriWidth, gfx.ScreenHeight + 1 - Gap - TriWidth), GetColor(bottomFactor));
	TriLTL(GetLoc(gfx.ScreenWidth + 1 - Gap - 2 * TriWidth, gfx.ScreenHeight + 1 - Gap - 2 * TriWidth), GetColor(topFactor));

	//bottom top rect
	Rect(Gap + 2 * TriWidth, gfx.ScreenHeight + 1 - Gap - 2 * TriWidth, gfx.ScreenWidth + 1 - Gap - 2 * TriWidth, gfx.ScreenHeight + 1 - TriWidth - Gap, GetColor(topFactor));
	//bottom bottom rect
	Rect(Gap + TriWidth, gfx.ScreenHeight + 1 - Gap - TriWidth, gfx.ScreenWidth + 1 - Gap - TriWidth, gfx.ScreenHeight + 1 - Gap, GetColor(bottomFactor));
}

void Frame::TriLTL(Vei2& loc, Color& c)
{
	int SelfControl = 0;
	for (int y = loc.y; y < loc.y + TriWidth; y++)
	{
		SelfControl++;
		for (int x = loc.x; x < loc.x + SelfControl; x++)
		{
			gfx.PutPixel(x, y, c);
			// gfx.PutPixel(int(Y), int(X), Colors::Blue); MAKES THE OTHER HALF OF THE TRIANGLE c:
		}

	}
}

void Frame::TriLTL2(Vei2& loc, Color& c)
{
	int SelfControl = -1;
	for (int y = loc.y; y < loc.y + TriWidth; y++)
	{
		SelfControl++;
		for (int x = loc.x + SelfControl; x < loc.x + TriWidth; x++)
		{
			gfx.PutPixel(x, y, c);
		}
	}
}

void Frame::TriLDL(Vei2& loc, Color& c)
{
	int SelfControl = TriWidth + 1;
	for (int y = loc.y; y <= loc.y + TriWidth; y++)
	{
		SelfControl--;
		for (int x = loc.x; x < loc.x + SelfControl; x++)
		{
			gfx.PutPixel(x, y, c);
			// gfx.PutPixel(int(Y), int(X), Colors::Blue); MAKES THE OTHER HALF OF THE TRIANGLE c:
		}

	}
}

void Frame::TriLDL2(Vei2& loc, Color& c)
{
	int SelfControl = 0;
	for (int y = loc.y; y < loc.y + TriWidth; y++)
	{
		SelfControl++;
		for (int x = loc.x - 1; x > loc.x - SelfControl; x--)
		{
			gfx.PutPixel(x, y, c);
			// gfx.PutPixel(int(Y), int(X), Colors::Blue); MAKES THE OTHER HALF OF THE TRIANGLE c:
		}

	}
}

void Frame::Rect(int x, int y, int x1, int y1, Color & c)
{
	gfx.DrawRect(x, y, x1, y1, c);
}

Vei2 Frame::GetLoc(int x, int y)
{
	Vei2 loc(x, y);
	return loc;
}

Color Frame::GetColor(float factor)
{
	float R = float(BaseC.GetR()) * factor;
	float G = float(BaseC.GetB()) * factor;
	float B = float(BaseC.GetG()) * factor;
	Color c2 = Color((int)R, (int)G, (int)B);
	return c2;
}