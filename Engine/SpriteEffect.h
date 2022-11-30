#pragma once

#include "Colors.h"
#include "Graphics.h"

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
}