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
	static enum class Crosshair
	{
		RETICLE,
		SCOPE
	} crosshair = Crosshair::RETICLE;

	static int s_xReticle = 400;
	static int s_yReticle = 300;
	static bool s_isRed = false;

	while (!wnd.kbd.KeyIsEmpty())
	{
		const Keyboard::Event evt = wnd.kbd.ReadKey();

		if (evt.IsPress())
		{
			switch (evt.GetCode())
			{
			case VK_LEFT:
				s_xReticle -= 50;
				break;
			case VK_UP:
				s_yReticle -= 50;
				break;
			case VK_RIGHT:
				s_xReticle += 50;
				break;
			case VK_DOWN:
				s_yReticle += 50;
				break;
			case VK_CONTROL:
				s_isRed = !s_isRed;
				break;
			case VK_SHIFT:
				crosshair = (crosshair == Crosshair::RETICLE) ? Crosshair::SCOPE : Crosshair::RETICLE;
				break;
			default:
				break;
			}
		}
	}

	const int red = 255;
	const int green = s_isRed ? 0 : 255;
	const int blue = s_isRed ? 0 : 255;

	switch (crosshair)
	{
	case Crosshair::RETICLE:
		gfx.PutPixel(s_xReticle - 5, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle - 4, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle - 3, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 3, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 4, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 5, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 5, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 4, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 3, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 3, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 4, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 5, red, green, blue);
		break;
	case Crosshair::SCOPE:
		// 십자선
		gfx.PutPixel(s_xReticle, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle - 4, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle - 3, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle - 2, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle - 1, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 4, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 3, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 2, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 1, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 4, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 3, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 2, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 1, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 4, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 3, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 2, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 1, red, green, blue);

		// 원
		gfx.PutPixel(s_xReticle - 5, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle - 5, s_yReticle - 1, red, green, blue);
		gfx.PutPixel(s_xReticle - 4, s_yReticle - 2, red, green, blue);
		gfx.PutPixel(s_xReticle - 4, s_yReticle - 3, red, green, blue);
		gfx.PutPixel(s_xReticle - 3, s_yReticle - 4, red, green, blue);
		gfx.PutPixel(s_xReticle - 2, s_yReticle - 4, red, green, blue);
		gfx.PutPixel(s_xReticle - 1, s_yReticle - 5, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle - 5, red, green, blue);
		gfx.PutPixel(s_xReticle + 5, s_yReticle - 1, red, green, blue);
		gfx.PutPixel(s_xReticle + 4, s_yReticle - 2, red, green, blue);
		gfx.PutPixel(s_xReticle + 4, s_yReticle - 3, red, green, blue);
		gfx.PutPixel(s_xReticle + 3, s_yReticle - 4, red, green, blue);
		gfx.PutPixel(s_xReticle + 2, s_yReticle - 4, red, green, blue);
		gfx.PutPixel(s_xReticle + 1, s_yReticle - 5, red, green, blue);
		gfx.PutPixel(s_xReticle + 5, s_yReticle, red, green, blue);
		gfx.PutPixel(s_xReticle + 5, s_yReticle + 1, red, green, blue);
		gfx.PutPixel(s_xReticle + 4, s_yReticle + 2, red, green, blue);
		gfx.PutPixel(s_xReticle + 4, s_yReticle + 3, red, green, blue);
		gfx.PutPixel(s_xReticle + 3, s_yReticle + 4, red, green, blue);
		gfx.PutPixel(s_xReticle + 2, s_yReticle + 4, red, green, blue);
		gfx.PutPixel(s_xReticle + 1, s_yReticle + 5, red, green, blue);
		gfx.PutPixel(s_xReticle, s_yReticle + 5, red, green, blue);
		gfx.PutPixel(s_xReticle - 5, s_yReticle + 1, red, green, blue);
		gfx.PutPixel(s_xReticle - 4, s_yReticle + 2, red, green, blue);
		gfx.PutPixel(s_xReticle - 4, s_yReticle + 3, red, green, blue);
		gfx.PutPixel(s_xReticle - 3, s_yReticle + 4, red, green, blue);
		gfx.PutPixel(s_xReticle - 2, s_yReticle + 4, red, green, blue);
		gfx.PutPixel(s_xReticle - 1, s_yReticle + 5, red, green, blue);
		break;
	default:
		break;
	}
}
