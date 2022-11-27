#include "Surface.h"
#include <assert.h>
#include "ChiliWin.h"

Surface::Surface( int width, int height )
	:
	width(width),
	height(height),
	pixels(new Color[width * height])
{
}

Surface::Surface( std::string fileName )
{
	std::ifstream file( fileName, std::ios::binary );
	assert( file );

	BITMAPFILEHEADER bmHeader;
	file.read( reinterpret_cast<char*>( &bmHeader ), sizeof( bmHeader ) );

	BITMAPINFOHEADER bmInfoHeader;
	file.read( reinterpret_cast<char*>( &bmInfoHeader ), sizeof( bmInfoHeader ) );

	assert( bmInfoHeader.biCompression == BI_RGB );
	assert( bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32 );

	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;
	bool flipped = false;
	if ( height < 0 )
	{
		height = -height;
		flipped = true;
	}

	pixels = new Color[width * height];

	file.seekg( bmHeader.bfOffBits );

	const int offset = ( 4 - ( width * 3 ) % 4 ) % 4;

	if(bmInfoHeader.biBitCount == 24 )
	{
		for ( int y = height - 1; y >= 0; y-- )
		{
			for ( int x = 0; x < width; x++ )
			{
				const char b = file.get();
				const char g = file.get();
				const char r = file.get();
				PutPixel( x, y, Color( r, g, b ) );
			}
			file.seekg( offset, std::ios::cur );
		}
	}
	else if ( bmInfoHeader.biBitCount == 32 )
	{
		for ( int y = height - 1; y >= 0; y-- )
		{
			for ( int x = 0; x < width; x++ )
			{
				const char b = file.get();
				const char g = file.get();
				const char r = file.get();
				const char a = file.get();
				PutPixel( x, y, Color( r, g, b ) );
			}
			file.seekg( offset, std::ios::cur );
		}
	}
	if ( flipped )
	{
		FlipX();
	}
}

Surface::Surface( const Surface& src )
	:
	Surface( src.width, src.height )
{

	for ( int i = 0; i < width * height; i++ )
	{
		pixels[i] = src.pixels[i];
	}
}

Surface::~Surface()
{
	delete[] pixels;
	pixels = nullptr;
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
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
	pixels[y * width + x] = c;
}

Color Surface::GetPixel( int x, int y ) const
{
	assert( x >= 0 );
	assert( x < width );
	assert( y >= 0 );
	assert( y < height );
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

void Surface::FlipX()
{
	const Surface old = *this;
	const int nPixels = width * height;
	for ( int x = 0; x < width; x++ )
	{
		for ( int y = 0; y < height; y++ ) 
		{
			int ny = height - y;
			pixels[y * width + x] = old.pixels[ny * width + x];
		}
	}
}

RectI Surface::GetRect() const
{
	return RectI(0,width,0,height);
}
