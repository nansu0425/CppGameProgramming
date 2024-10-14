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
	// 왼쪽 이동 속도 설정
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (!isLimitLeftVeloIncrease)
		{
			isLimitLeftVeloIncrease = true;
			--veloX;
		}
	}
	else
	{
		isLimitLeftVeloIncrease = false;
	}

	// 윗쪽 이동 속도 설정
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (!isLimitUpVeloIncrease)
		{
			isLimitUpVeloIncrease = true;
			--veloY;
		}
	}
	else
	{
		isLimitUpVeloIncrease = false;
	}

	// 오른쪽 이동 속도 설정
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (!isLimitRightVeloIncrease)
		{
			isLimitRightVeloIncrease = true;
			++veloX;
		}
	}
	else
	{
		isLimitRightVeloIncrease = false;
	}

	// 아랫쪽 이동 속도 설정
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (!isLimitDownVeloIncrease)
		{
			isLimitDownVeloIncrease = true;
			++veloY;
		}
	}
	else
	{
		isLimitDownVeloIncrease = false;
	}

	// 이동 속도에 따라 조준선 위치 이동
	xCrosshair += veloX;
	yCrosshair += veloY;

	// 조준선 색 결정
	const bool isRed = wnd.kbd.KeyIsPressed(VK_CONTROL);
	color.SetG(isRed ? 0 : 255);
	color.SetB(isRed ? 0 : 255);

	// 조준선 모양 결정
	isShapeChanged = wnd.kbd.KeyIsPressed(VK_SHIFT);
}

void Game::ComposeFrame()
{
	if (isShapeChanged)
	{
		// 십자선
		gfx.PutPixel(xCrosshair, yCrosshair, color);
		gfx.PutPixel(xCrosshair - 4, yCrosshair, color);
		gfx.PutPixel(xCrosshair - 3, yCrosshair, color);
		gfx.PutPixel(xCrosshair - 2, yCrosshair, color);
		gfx.PutPixel(xCrosshair - 1, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 4, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 3, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 2, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 1, yCrosshair, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 4, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 3, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 2, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 1, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 4, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 3, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 2, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 1, color);

		// 원
		gfx.PutPixel(xCrosshair - 5, yCrosshair, color);
		gfx.PutPixel(xCrosshair - 5, yCrosshair - 1, color);
		gfx.PutPixel(xCrosshair - 4, yCrosshair - 2, color);
		gfx.PutPixel(xCrosshair - 4, yCrosshair - 3, color);
		gfx.PutPixel(xCrosshair - 3, yCrosshair - 4, color);
		gfx.PutPixel(xCrosshair - 2, yCrosshair - 4, color);
		gfx.PutPixel(xCrosshair - 1, yCrosshair - 5, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 5, color);
		gfx.PutPixel(xCrosshair + 5, yCrosshair - 1, color);
		gfx.PutPixel(xCrosshair + 4, yCrosshair - 2, color);
		gfx.PutPixel(xCrosshair + 4, yCrosshair - 3, color);
		gfx.PutPixel(xCrosshair + 3, yCrosshair - 4, color);
		gfx.PutPixel(xCrosshair + 2, yCrosshair - 4, color);
		gfx.PutPixel(xCrosshair + 1, yCrosshair - 5, color);
		gfx.PutPixel(xCrosshair + 5, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 5, yCrosshair + 1, color);
		gfx.PutPixel(xCrosshair + 4, yCrosshair + 2, color);
		gfx.PutPixel(xCrosshair + 4, yCrosshair + 3, color);
		gfx.PutPixel(xCrosshair + 3, yCrosshair + 4, color);
		gfx.PutPixel(xCrosshair + 2, yCrosshair + 4, color);
		gfx.PutPixel(xCrosshair + 1, yCrosshair + 5, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 5, color);
		gfx.PutPixel(xCrosshair - 5, yCrosshair + 1, color);
		gfx.PutPixel(xCrosshair - 4, yCrosshair + 2, color);
		gfx.PutPixel(xCrosshair - 4, yCrosshair + 3, color);
		gfx.PutPixel(xCrosshair - 3, yCrosshair + 4, color);
		gfx.PutPixel(xCrosshair - 2, yCrosshair + 4, color);
		gfx.PutPixel(xCrosshair - 1, yCrosshair + 5, color);
	}
	else
	{
		// 십자선
		gfx.PutPixel(xCrosshair - 5, yCrosshair, color);
		gfx.PutPixel(xCrosshair - 4, yCrosshair, color);
		gfx.PutPixel(xCrosshair - 3, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 3, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 4, yCrosshair, color);
		gfx.PutPixel(xCrosshair + 5, yCrosshair, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 5, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 4, color);
		gfx.PutPixel(xCrosshair, yCrosshair - 3, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 3, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 4, color);
		gfx.PutPixel(xCrosshair, yCrosshair + 5, color);
	}
}
