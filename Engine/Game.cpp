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

int Game::ClampCircleWindowX(int x, int r)
{
	const int left = x - r;
	const int right = x + r;

	if (left < 0)
	{
		return r;
	}
	
	if (right >= gfx.ScreenWidth)
	{
		return gfx.ScreenWidth - r - 1;
	}

	return x;
}

int Game::ClampCircleWindowY(int y, int r)
{
	const int up = y - r;
	const int down = y + r;

	if (up < 0)
	{
		return r;
	}

	if (down >= gfx.ScreenHeight)
	{
		return gfx.ScreenHeight - r - 1;
	}

	return y;
}

void Game::MoveCircle(int& x, int& y)
{
	// 왼쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		--x;
	}
	// 윗쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		--y;
	}
	// 오른쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		++x;
	}
	// 아랫쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		++y;
	}

	x = ClampCircleWindowX(x, 5);
	y = ClampCircleWindowY(y, 5);
}

bool Game::CheckCollisionCircles(float x1, float y1, float r1, float x2, float y2, float r2)
{
	const float distance = sqrtf(powf(float(x1 - x2), 2.0f) + powf(float(y1 - y2), 2.0f));

	return (distance <= r1 + r2);
}

void Game::UpdateModel()
{
	// 방향기를 누르면 MovingCrosshair를 이동시킨다
	MoveCircle(xMovingCrosshair, yMovingCrosshair);

	// MovingCrosshair와 FixedCrosshair가 충돌하면 MovingCrosshair는 빨간색이 된다
	if (CheckCollisionCircles(float(xMovingCrosshair), float(yMovingCrosshair), 5.0f, float(xFixedCrosshair1), float(yFixedCrosshair1), 5.0f) ||
		CheckCollisionCircles(float(xMovingCrosshair), float(yMovingCrosshair), 5.0f, float(xFixedCrosshair2), float(yFixedCrosshair2), 5.0f) ||
		CheckCollisionCircles(float(xMovingCrosshair), float(yMovingCrosshair), 5.0f, float(xFixedCrosshair3), float(yFixedCrosshair3), 5.0f) ||
		CheckCollisionCircles(float(xMovingCrosshair), float(yMovingCrosshair), 5.0f, float(xFixedCrosshair4), float(yFixedCrosshair4), 5.0f))
	{
		colorMovingCrosshair.SetG(0);
		colorMovingCrosshair.SetB(0);
	}
	else
	{
		colorMovingCrosshair.SetG(255);
		colorMovingCrosshair.SetB(255);
	}
}

void Game::DrawCrosshair(int x, int y, Color color)
{
	gfx.PutPixel(x, y, color);
	gfx.PutPixel(x - 4, y, color);
	gfx.PutPixel(x - 3, y, color);
	gfx.PutPixel(x - 2, y, color);
	gfx.PutPixel(x - 1, y, color);
	gfx.PutPixel(x + 4, y, color);
	gfx.PutPixel(x + 3, y, color);
	gfx.PutPixel(x + 2, y, color);
	gfx.PutPixel(x + 1, y, color);
	gfx.PutPixel(x, y - 4, color);
	gfx.PutPixel(x, y - 3, color);
	gfx.PutPixel(x, y - 2, color);
	gfx.PutPixel(x, y - 1, color);
	gfx.PutPixel(x, y + 4, color);
	gfx.PutPixel(x, y + 3, color);
	gfx.PutPixel(x, y + 2, color);
	gfx.PutPixel(x, y + 1, color);
	gfx.PutPixel(x - 5, y, color);
	gfx.PutPixel(x - 5, y - 1, color);
	gfx.PutPixel(x - 4, y - 2, color);
	gfx.PutPixel(x - 4, y - 3, color);
	gfx.PutPixel(x - 3, y - 4, color);
	gfx.PutPixel(x - 2, y - 4, color);
	gfx.PutPixel(x - 1, y - 5, color);
	gfx.PutPixel(x, y - 5, color);
	gfx.PutPixel(x + 5, y - 1, color);
	gfx.PutPixel(x + 4, y - 2, color);
	gfx.PutPixel(x + 4, y - 3, color);
	gfx.PutPixel(x + 3, y - 4, color);
	gfx.PutPixel(x + 2, y - 4, color);
	gfx.PutPixel(x + 1, y - 5, color);
	gfx.PutPixel(x + 5, y, color);
	gfx.PutPixel(x + 5, y + 1, color);
	gfx.PutPixel(x + 4, y + 2, color);
	gfx.PutPixel(x + 4, y + 3, color);
	gfx.PutPixel(x + 3, y + 4, color);
	gfx.PutPixel(x + 2, y + 4, color);
	gfx.PutPixel(x + 1, y + 5, color);
	gfx.PutPixel(x, y + 5, color);
	gfx.PutPixel(x - 5, y + 1, color);
	gfx.PutPixel(x - 4, y + 2, color);
	gfx.PutPixel(x - 4, y + 3, color);
	gfx.PutPixel(x - 3, y + 4, color);
	gfx.PutPixel(x - 2, y + 4, color);
	gfx.PutPixel(x - 1, y + 5, color);
}

void Game::ComposeFrame()
{
	DrawCrosshair(xMovingCrosshair, yMovingCrosshair, colorMovingCrosshair);
	DrawCrosshair(xFixedCrosshair1, yFixedCrosshair1, colorFixedCrosshair);
	DrawCrosshair(xFixedCrosshair2, yFixedCrosshair2, colorFixedCrosshair);
	DrawCrosshair(xFixedCrosshair3, yFixedCrosshair3, colorFixedCrosshair);
	DrawCrosshair(xFixedCrosshair4, yFixedCrosshair4, colorFixedCrosshair);
}
