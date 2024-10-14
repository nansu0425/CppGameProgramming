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

void Game::UpdateModel()
{
	// 왼쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		--xMovingCrosshair;
	}
	// 윗쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		--yMovingCrosshair;
	}
	// 오른쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		++xMovingCrosshair;
	}
	// 아랫쪽 이동
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		++yMovingCrosshair;
	}

	// x축 스크린 범위를 못 넘게 처리
	if (xMovingCrosshair - 5 < 0)
	{
		xMovingCrosshair = 5;
	}
	else if (xMovingCrosshair + 5 >= gfx.ScreenWidth)
	{
		xMovingCrosshair = gfx.ScreenWidth - 6;
	}
	// y축 스크린 범위를 못 넘게 처리
	if (yMovingCrosshair - 5 < 0)
	{
		yMovingCrosshair = 5;
	}
	else if (yMovingCrosshair + 5 >= gfx.ScreenHeight)
	{
		yMovingCrosshair = gfx.ScreenHeight - 6;
	}

	const float distance = sqrtf(powf(float(xMovingCrosshair - xFixedCrosshair), 2.0f) +
								 powf(float(yMovingCrosshair - yFixedCrosshair), 2.0f));

	// 움직이는 조준선과 고정된 조준선이 겹치면 움직이는 조준선은 빨간색이 된다
	if (distance <= 10.0f)
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

void Game::ComposeFrame()
{
	// 움직이는 조준선
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 4, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 3, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 2, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 1, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 4, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 3, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 2, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 1, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair - 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair - 3, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair - 2, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair - 1, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair + 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair + 3, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair + 2, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair + 1, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 5, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 5, yMovingCrosshair - 1, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 4, yMovingCrosshair - 2, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 4, yMovingCrosshair - 3, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 3, yMovingCrosshair - 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 2, yMovingCrosshair - 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 1, yMovingCrosshair - 5, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair - 5, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 5, yMovingCrosshair - 1, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 4, yMovingCrosshair - 2, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 4, yMovingCrosshair - 3, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 3, yMovingCrosshair - 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 2, yMovingCrosshair - 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 1, yMovingCrosshair - 5, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 5, yMovingCrosshair, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 5, yMovingCrosshair + 1, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 4, yMovingCrosshair + 2, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 4, yMovingCrosshair + 3, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 3, yMovingCrosshair + 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 2, yMovingCrosshair + 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair + 1, yMovingCrosshair + 5, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair, yMovingCrosshair + 5, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 5, yMovingCrosshair + 1, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 4, yMovingCrosshair + 2, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 4, yMovingCrosshair + 3, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 3, yMovingCrosshair + 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 2, yMovingCrosshair + 4, colorMovingCrosshair);
	gfx.PutPixel(xMovingCrosshair - 1, yMovingCrosshair + 5, colorMovingCrosshair);

	// 고정된 조준선
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 4, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 3, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 2, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 1, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 4, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 3, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 2, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 1, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair - 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair - 3, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair - 2, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair - 1, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair + 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair + 3, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair + 2, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair + 1, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 5, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 5, yFixedCrosshair - 1, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 4, yFixedCrosshair - 2, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 4, yFixedCrosshair - 3, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 3, yFixedCrosshair - 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 2, yFixedCrosshair - 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 1, yFixedCrosshair - 5, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair - 5, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 5, yFixedCrosshair - 1, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 4, yFixedCrosshair - 2, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 4, yFixedCrosshair - 3, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 3, yFixedCrosshair - 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 2, yFixedCrosshair - 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 1, yFixedCrosshair - 5, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 5, yFixedCrosshair, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 5, yFixedCrosshair + 1, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 4, yFixedCrosshair + 2, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 4, yFixedCrosshair + 3, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 3, yFixedCrosshair + 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 2, yFixedCrosshair + 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair + 1, yFixedCrosshair + 5, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair, yFixedCrosshair + 5, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 5, yFixedCrosshair + 1, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 4, yFixedCrosshair + 2, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 4, yFixedCrosshair + 3, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 3, yFixedCrosshair + 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 2, yFixedCrosshair + 4, colorFixedCrosshair);
	gfx.PutPixel(xFixedCrosshair - 1, yFixedCrosshair + 5, colorFixedCrosshair);
}
