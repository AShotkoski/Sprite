#pragma once
#include "Colors.h"
#include <fstream>
#include "RectI.h"

class Surface
{
public:
	Surface( int width, int height );
	Surface( std::string fileName );
	~Surface();
	Surface& operator=( const Surface& src );
	Surface( const Surface& src );
	void PutPixel( int x, int y, Color c );
	Color GetPixel( int x, int y ) const;
	int GetWidth() const;
	int GetHeight() const;
	void FlipX();
	RectI GetRect() const;

private:
	Color* pixels = nullptr;
	int width;
	int height;
};

