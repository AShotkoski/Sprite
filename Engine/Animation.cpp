#include "Animation.h"
#include <assert.h>

Animation::Animation(int x, int y, int width, int height, float holdtime, int nFrames, Surface& SpriteSheet, Color Chroma )
	:
	SpriteSheet(SpriteSheet),
	holdTime(holdtime),
	chroma(Chroma)
{
	assert( x + width * nFrames <= SpriteSheet.GetWidth() );
	//init frames
	for ( int i = 0; i < nFrames; ++i )
	{
		//each frame add a rect of that frame to the frames vector
		frames.emplace_back(  x + width * i, width + width * i, y,  y + height );
	}
}

void Animation::Update( float dt )
{
	currTime += dt;
	if ( currTime >= holdTime )
	{
		Advance();
		currTime = 0.0f;
	}
}

void Animation::Draw( const Vei2& pos, Graphics& gfx ) const
{
	gfx.DrawSprite( pos.x, pos.y, frames[iCurrFrame], SpriteSheet, chroma );
}

void Animation::Advance()
{
	iCurrFrame++;
	if ( iCurrFrame >= frames.size() )
	{
		iCurrFrame = 0;
	}
}
