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
#include "Drawings.h"

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
	MoveFace();

	face.x = ClampScreenX(face.x, 19);
	face.y = ClampScreenY(face.y, 19);
}

void Game::ComposeFrame()
{
	DrawPoos();
	DrawFace();
}

void Game::DrawFace()
{
	Drawings::DrawFace(gfx, face.x, face.y);
}

void Game::DrawGameOver()
{
	Drawings::DrawGameOver(gfx, gameOver.x, gameOver.y);
}

void Game::DrawPoos()
{
	for (const Position& poo : poos)
	{
		DrawPoo(poo);
	}
}

void Game::DrawPoo(const Position& poo)
{
	Drawings::DrawPoo(gfx, poo.x, poo.y);
}

void Game::DrawTitle()
{
	Drawings::DrawTitle(gfx, title.x, title.y);
}

void Game::MoveFace()
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		--face.x;
	}

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		--face.y;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		++face.x;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		++face.y;
	}
}

int Game::ClampScreenX(int x, int width)
{
	const int left = x;
	const int right = x + width;

	if (left < 0)
	{
		return 0;
	}

	if (right >= gfx.ScreenWidth)
	{
		return gfx.ScreenWidth - width - 1;
	}

	return x;
}

int Game::ClampScreenY(int y, int height)
{
	const int top = y;
	const int bottom = y + height;

	if (top < 0)
	{
		return 0;
	}

	if (bottom >= gfx.ScreenHeight)
	{
		return gfx.ScreenHeight - height - 1;
	}

	return y;
}
