#pragma once
#include "Surface.h"
#include "Graphics.h"

class TextDrawer
{
public:
	TextDrawer( const std::string filename );
	void DrawText( const std::string str, const Vei2& pos, Graphics& gfx, Color chroma, Color color ) const;

private:
	RectI mapCharI( char c ) const;
private:
	Surface spriteSheet;
	//tile sizes
	const int tileWidth = 16;
	const int tileHeight = 28;

	//font sheet
	const int nColumns = 32;
	const int nRows = 3;

	const char firstChar = ' ';
	const char lastChar = '~';
};

