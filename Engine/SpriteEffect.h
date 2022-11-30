#pragma once

#include "Colors.h"
#include "Graphics.h"
#include <cassert>

namespace SpriteEffect
{
	class Copy
	{
	public:
		void operator()( Color cSrc, int xDest, int yDest, Graphics& gfx ) const
		{		
			gfx.PutPixel( xDest, yDest, cSrc );
		}
	};

	class Chroma
	{
	public:
		Chroma( Color c )
			:
			chroma( c )
		{}
		void operator()( Color cSrc, int xDest, int yDest, Graphics& gfx ) const
		{		
			if ( cSrc != chroma )
			{
				gfx.PutPixel( xDest, yDest, cSrc );
			}
		}
	private:
		Color chroma;
	};

	class Substitute
	{
	public:
		Substitute( Color chroma, Color newCol )
			:
			chroma( chroma ),
			newCol(newCol)
		{}
		void operator()( Color cSrc, int xDest, int yDest, Graphics& gfx ) const
		{		
			if ( cSrc != chroma )
			{
				gfx.PutPixel( xDest, yDest, newCol );
			}
		}
	private:
		Color chroma;
		Color newCol;
	};

	class Transparency
	{
	public:
		//visibility percent between 0.0f and 1.0f
		Transparency( Color chroma, float VisibilityPercent )
			:
			chroma( chroma ),
			visPerc( VisibilityPercent )
		{
			assert( visPerc >= 0 );
			assert( visPerc <= 1.0f );
		}
		void operator()( Color cSrc, int xDest, int yDest, Graphics& gfx ) const
		{
			if ( cSrc != chroma )
			{
				//init + percent * (final + init) = val
				Color bgPixel = gfx.GetPixel( xDest, yDest );
				Color newCol
				( 
					perc( bgPixel.GetR(), cSrc.GetR() ) ,
					perc( bgPixel.GetG(), cSrc.GetG() ),
					perc( bgPixel.GetB(), cSrc.GetB() )
				);
				gfx.PutPixel( xDest, yDest, newCol );
			}
		}
	private:
		inline unsigned char perc( unsigned int v0, unsigned int v1 ) const
		{
			return unsigned char( v0 + visPerc * ( v1 - v0 ) );
		}
		Color chroma;
		float visPerc;
	};
}