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
	: wnd( wnd )
	, gfx( wnd )
	, grid(gfx)
	, rng(rd())
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
	std::uniform_int_distribution<> distColor(0, 255);

	for (int row = 0; row < grid.m_lenRow; ++row)
	{
		for (int col = 0; col < grid.m_lenCol; ++col)
		{
			const Color color =
			{
				static_cast<unsigned char>(distColor(rng)),
				static_cast<unsigned char>(distColor(rng)),
				static_cast<unsigned char>(distColor(rng)),
			};

			grid.SetColorCell(row, col, color);
		}
	}
}

void Game::ComposeFrame()
{
	grid.DrawCells();
}
