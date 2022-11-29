#pragma once
#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation( int x, int y, int width, int height,float holdtime,
		int nFrames, Surface& SpriteSheet, Color Chroma = Colors::Magenta );
	void Update( float dt );
	void Draw( const Vei2& pos, Graphics& gfx ) const;
private:
	void Advance();
private:
	Color chroma;
	Surface& SpriteSheet;
	std::vector<RectI> frames;
	int iCurrFrame = 0;
	float holdTime;
	float currTime = 0.f;
};

