#include "Animation.h"
#include <assert.h>
#include "SpriteEffect.h"

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
		frames.emplace_back(  x + width * i, x + width + width * i, y,  y + height );
	}
}

void Animation::Update( float dt )
{
	currTime += dt;
	//advances frames based off real time passed
	while ( currTime >= holdTime )
	{ //this will be called currTime / holdTime times
		Advance();
		currTime -= holdTime;
	}
}

void Animation::Draw( const Vei2& pos, Graphics& gfx ) const
{
	gfx.DrawSprite( pos.x, pos.y, frames[iCurrFrame], SpriteSheet, SpriteEffect::Chroma(chroma ));
}

void Animation::Advance()
{
	iCurrFrame++;
	if ( iCurrFrame >= frames.size() )
	{
		iCurrFrame = 0;
	}
}
