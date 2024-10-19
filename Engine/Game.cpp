﻿/****************************************************************************************** 
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
#include "math.h"

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
	MoveWhiteBox();
	ScaleWhiteBox();
}

void Game::ComposeFrame()
{
	DrawWhiteBox();
}

void Game::DrawWhiteBox()
{
	for (int dx = 0; dx < width; ++dx)
	{
		for (int dy = 0; dy < height; ++dy)
		{
			gfx.PutPixel(x + dx, y + dy, 255, 255, 255);
		}
	}
}

void Game::MoveWhiteBox()
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		--x;
	}

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		--y;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		++x;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		++y;
	}
}

void Game::ScaleWhiteBox()
{
	if (wnd.kbd.KeyIsPressed('A'))
	{
		--width;
	}

	if (wnd.kbd.KeyIsPressed('W'))
	{
		--height;
	}

	if (wnd.kbd.KeyIsPressed('D'))
	{
		++width;
	}

	if (wnd.kbd.KeyIsPressed('S'))
	{
		++height;
	}
}
