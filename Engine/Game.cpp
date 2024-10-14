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
}

void Game::ComposeFrame()
{
	// 화살표 키 눌렀는지 확인
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		xCrosshair -= 3;
	}
	else if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		yCrosshair -= 3;
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		xCrosshair += 3;
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		yCrosshair += 3;
	}

	const bool isRed = wnd.kbd.KeyIsPressed(VK_CONTROL);
	const int red = 255;
	const int green = isRed ? 0 : 255;
	const int blue = isRed ? 0 : 255;

	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		// 십자선
		gfx.PutPixel(xCrosshair - 5, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair - 4, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair - 3, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 3, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 4, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 5, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 5, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 4, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 3, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 3, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 4, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 5, red, green, blue);
	}
	else
	{
		// 십자선
		gfx.PutPixel(xCrosshair, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair - 4, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair - 3, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair - 2, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair - 1, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 4, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 3, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 2, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 1, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 4, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 3, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 2, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 1, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 4, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 3, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 2, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 1, red, green, blue);

		// 원
		gfx.PutPixel(xCrosshair - 5, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair - 5, yCrosshair - 1, red, green, blue);
		gfx.PutPixel(xCrosshair - 4, yCrosshair - 2, red, green, blue);
		gfx.PutPixel(xCrosshair - 4, yCrosshair - 3, red, green, blue);
		gfx.PutPixel(xCrosshair - 3, yCrosshair - 4, red, green, blue);
		gfx.PutPixel(xCrosshair - 2, yCrosshair - 4, red, green, blue);
		gfx.PutPixel(xCrosshair - 1, yCrosshair - 5, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair - 5, red, green, blue);
		gfx.PutPixel(xCrosshair + 5, yCrosshair - 1, red, green, blue);
		gfx.PutPixel(xCrosshair + 4, yCrosshair - 2, red, green, blue);
		gfx.PutPixel(xCrosshair + 4, yCrosshair - 3, red, green, blue);
		gfx.PutPixel(xCrosshair + 3, yCrosshair - 4, red, green, blue);
		gfx.PutPixel(xCrosshair + 2, yCrosshair - 4, red, green, blue);
		gfx.PutPixel(xCrosshair + 1, yCrosshair - 5, red, green, blue);
		gfx.PutPixel(xCrosshair + 5, yCrosshair, red, green, blue);
		gfx.PutPixel(xCrosshair + 5, yCrosshair + 1, red, green, blue);
		gfx.PutPixel(xCrosshair + 4, yCrosshair + 2, red, green, blue);
		gfx.PutPixel(xCrosshair + 4, yCrosshair + 3, red, green, blue);
		gfx.PutPixel(xCrosshair + 3, yCrosshair + 4, red, green, blue);
		gfx.PutPixel(xCrosshair + 2, yCrosshair + 4, red, green, blue);
		gfx.PutPixel(xCrosshair + 1, yCrosshair + 5, red, green, blue);
		gfx.PutPixel(xCrosshair, yCrosshair + 5, red, green, blue);
		gfx.PutPixel(xCrosshair - 5, yCrosshair + 1, red, green, blue);
		gfx.PutPixel(xCrosshair - 4, yCrosshair + 2, red, green, blue);
		gfx.PutPixel(xCrosshair - 4, yCrosshair + 3, red, green, blue);
		gfx.PutPixel(xCrosshair - 3, yCrosshair + 4, red, green, blue);
		gfx.PutPixel(xCrosshair - 2, yCrosshair + 4, red, green, blue);
		gfx.PutPixel(xCrosshair - 1, yCrosshair + 5, red, green, blue);
	}
}
