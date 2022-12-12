/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	elapsedTime = ft.Mark();
	Vec2 dir( 0, 0 );
	if(wnd.kbd.KeyIsPressed(VK_RIGHT) )
	{
		dir = { 1.f, 0 };
	}
	if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
	{
		dir = { -1.f, 0 };
	}
	if ( wnd.kbd.KeyIsPressed( VK_UP ) )
	{
		dir = { 0, -1.f };
	}
	if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
	{
		dir = { 0, 1.f };
	}

	fred.SetDirection( dir );
	fred.Update( elapsedTime );
}

void Game::ComposeFrame()
{
	gfx.DrawSprite( 50, 50, whitebg, SpriteEffect::Copy() );
	
	text.DrawText( "Gay Bro", Vei2(fred.getPos()), gfx, Colors::White, Colors::Red);
	fred.Draw( gfx );
	gfx.DrawSprite( 350, 350, funny, []( Color cSrc, int xDest, int yDest, Graphics& gfx )
		{
			Color newColor = cSrc.dword ^ 0xFF00FF0F;
		gfx.PutPixel( xDest, yDest, newColor );
		}
	);
}
