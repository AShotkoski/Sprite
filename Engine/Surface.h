#pragma once
#include "Colors.h"
#include <fstream>
#include "Rect.h"
#include "ChiliException.h"

class Surface
{
public:

	//Ctors, Dtors, operators
	Surface( int width, int height, Color FillColor );
	Surface( int width, int height );
	Surface( std::string fileName );
	~Surface();
	Surface() = default;
	Surface& operator=( const Surface& src );
	Surface& operator=( Surface&& donor ) noexcept;
	Surface( const Surface& src );
	Surface( Surface&& src ) noexcept;

	//Interface functions
	void PutPixel( int x, int y, Color c );
	Color GetPixel( int x, int y ) const;
	int GetWidth() const;
	int GetHeight() const;
	void FlipX();
	RectI GetRect() const;
	

private:
	//data
	Color* pixels = nullptr;
	int width = 0;
	int height = 0;
};

