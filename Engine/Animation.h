#pragma once
#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation( int x, int y, int width, int height,float holdtime,
		int nFrames, Surface& SpriteSheet, Color Chroma = Colors::Magenta );
	//advances frames using realtime
	void Update( float dt );
	//draws current frame to pos
	void Draw( const Vei2& pos, Graphics& gfx ) const;
private:
	//advances the frame
	void Advance();
private:
	//chroma key color
	Color chroma;
	//reference to spritesheet, reference because cheaper memory
	Surface& SpriteSheet;
	//holds a rect of every frame
	std::vector<RectI> frames;
	//track current frame
	int iCurrFrame = 0;
	//holdtime is how long each frame is displayed
	float holdTime;
	float currTime = 0.f;
};

