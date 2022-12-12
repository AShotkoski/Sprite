#include "Surface.h"
#include <assert.h>
#include "ChiliWin.h"

Surface::Surface( int width, int height )
	:
	width( width ),
	height( height ),
	pixels( new Color[width * height] )
{
}

Surface::Surface( std::string fileName )
{
	std::ifstream file;
	BITMAPFILEHEADER bmHeader;
	BITMAPINFOHEADER bmInfoHeader;

	bool flipped = false;

	try
	{
		//Open file
		file.open( fileName, std::ios::binary );
		if ( !file )
		{
			throw std::runtime_error( "Error Loading Surface File: " + fileName );
		}

		//Read file header into bitmapfileheader data struct	
		file.read( reinterpret_cast<char*>( &bmHeader ), sizeof( bmHeader ) );

		//read file infoheader into bitmapinfoheader data struct	
		file.read( reinterpret_cast<char*>( &bmInfoHeader ), sizeof( bmInfoHeader ) );

		//Make sure the file is compatible
		if ( bmInfoHeader.biCompression != BI_RGB )
		{
			throw std::runtime_error( "Surface bitmap compression type not supported. in: " + fileName );
		}
		if ( bmInfoHeader.biBitCount != 24 && bmInfoHeader.biBitCount != 32 )
		{
			throw std::runtime_error( "Surface bitmap is not a supported bitcount. in: " + fileName );
		}

		width = bmInfoHeader.biWidth;
		height = bmInfoHeader.biHeight;

		//Some bitmap files do a negative height and then they have to be be inverted and flipped to work right
		//This code handles that case
		if ( height < 0 )
		{
			height = -height;
			flipped = true;
		}

		//Assign memory to store information
		pixels = new Color[width * height];

		//Seek to the pixel data in the bitmap file
		file.seekg( bmHeader.bfOffBits );


		if ( bmInfoHeader.biBitCount == 24 )
		{
			//24 bit files use padding
			const int offset = ( 4 - ( width * 3 ) % 4 ) % 4;

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
			}
		}
		if ( flipped )
		{
			FlipX();
		}
	}
	catch ( const std::runtime_error& e )
	{
		//here is where a better programmer than me would fill the surface with filler info if the surface
		//file fails to load
#ifdef _DEBUG
		throw e;
#endif
		width = 15;
		height = 15;
		pixels = new Color[width * height];
		for ( int i = 0; i < width * height; ++i )
		{
			pixels[i] = Colors::White;
		}
	}




}

Surface::Surface( const Surface& src )
	:
	Surface( src.width, src.height )
{
	if ( &src != this )
	{
		for ( int i = 0; i < width * height; i++ )
		{
			pixels[i] = src.pixels[i];
		}
	}
}

Surface::Surface( Surface&& src ) noexcept
	:
	width( src.width ),
	height( src.height ),
	pixels( src.pixels )
{
	src.pixels = nullptr;
	src.width = 0;
	src.height = 0;
}

Surface::~Surface()
{
	delete[] pixels;
	pixels = nullptr;
}

Surface& Surface::operator=( const Surface& src )
{
	if ( &src != this ) //No self assignment, thats bad
	{
		//delete old memory
		delete[] pixels;

		//Copy size from source
		height = src.height;
		width = src.width;

		//assign new memory
		pixels = new Color[width * height];

		//copy data into new memory
		for ( int i = 0; i < width * height; i++ )
		{
			pixels[i] = src.pixels[i];
		}
	}

	return *this;

}

Surface& Surface::operator=( Surface&& donor ) noexcept
{
	if ( &donor != this )
	{
		delete[] pixels;
		height = donor.height;
		width = donor.width;
		pixels = donor.pixels;
		donor.pixels = nullptr;
		donor.width = 0;
		donor.height = 0;
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
	return RectI( 0, width, 0, height );
}
