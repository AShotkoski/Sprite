#include "TextDrawer.h"
#include <assert.h>
#include "SpriteEffect.h"

TextDrawer::TextDrawer( const std::string filename )
	:
	spriteSheet( filename )
{
}

void TextDrawer::DrawText( const std::string str, const Vei2& pos, Graphics& gfx, Color chroma, Color color ) const
{

	SpriteEffect::Substitute effect( chroma, color );
	auto currPos = pos;
	for ( char c : str )
	{
		if ( c == '\n' )
		{
			currPos.x = pos.x;
			currPos.y += tileHeight;
			continue;
		}
		if ( c > firstChar && c <= lastChar )
		{
			RectI rect = mapCharI( c );
			gfx.DrawSprite( currPos.x, currPos.y, mapCharI( c ), spriteSheet, effect);
		}
		currPos.x += tileWidth;
	}
}

RectI TextDrawer::mapCharI( char c ) const
{
	assert( c <= lastChar );
	assert( c >= firstChar );

	int charIndex = c - firstChar;
	int row = charIndex / nColumns;
	int column = charIndex % nColumns;
	return RectI( Vei2( column * tileWidth, row * tileHeight ), tileWidth, tileHeight );
}
