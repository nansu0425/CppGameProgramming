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
	, rng(rd())
	, grid(gfx)
	, snake(grid, {grid.m_lenRow / 2, grid.m_lenCol / 2}, 100)
{
	std::uniform_int_distribution<> distDirection(0, 3);
	snake.SetDirection(static_cast<Snake::Direction>(distDirection(rng)));
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
	SetDirectionSnake();
	GrowSnake();
	snake.Move();
}

void Game::ComposeFrame()
{
	snake.Draw();
}

void Game::SetDirectionSnake()
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		snake.SetDirection(Snake::Direction::LEFT);
	}

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		snake.SetDirection(Snake::Direction::UP);
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		snake.SetDirection(Snake::Direction::RIGHT);
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		snake.SetDirection(Snake::Direction::DOWN);
	}
}

void Game::GrowSnake()
{
	static int s_countGrow = 0;
	static constexpr int s_periodGrow = 300;

	if (s_countGrow < s_periodGrow)
	{
		++s_countGrow;
		return;
	}
	s_countGrow = 0;

	snake.Grow();
}
