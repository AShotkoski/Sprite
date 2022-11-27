#include "Surface.h"
#include <assert.h>

Surface::Surface( int width, int height )
	:
	width(width),
	height(height),
	pixels(new Color[width * height])
{
}

Surface::~Surface()
{
	delete[] pixels;
	pixels = nullptr;
}

Surface::Surface( const Surface& src )
	:
	Surface(src.width, src.height)
{

	for ( int i = 0; i < width * height; i++ )
	{
		pixels[i] = src.pixels[i];
	}
}

Surface& Surface::operator=( const Surface& src )
{
	height = src.height;
	width = src.width;

	delete[] pixels;
	pixels = new Color[width * height];

	for ( int i = 0; i < width * height; i++ )
	{
		pixels[i] = src.pixels[i];
	}
	
	return *this;
}

void Surface::PutPixel( int x, int y, Color c )
{
	assert( x > 0 );
	assert( x < width );
	assert( y > 0 );
	assert( y < height );
	pixels[y * width + x] = c;
}

Color Surface::GetPixel( int x, int y ) const
{
	assert( ( y * width + x ) <= width * height );
	assert( ( y * width + x ) >= 0 );
	return pixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
