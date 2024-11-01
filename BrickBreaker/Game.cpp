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
#include "Brick.h"

Game::Game( MainWindow& wnd )
	: m_wnd( wnd )
	, m_gfx( wnd )
	, m_yellowBrick(Vector(200.0f, 300.0f))
	, m_redBrick(Vector(400.0f, 300.0f))
	, m_ball(Vector(100.0f, 200.0f), Vector(1.0f, 2.0f))
{}

void Game::Go()
{
	m_gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	m_gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float deltaTime = m_timer.CalculateDeltaTime();

	m_yellowBrick.Update(deltaTime);
	m_yellowBrick.Update(deltaTime);
	m_ball.Update(deltaTime);
}

void Game::ComposeFrame()
{
	m_yellowBrick.Draw(m_gfx);
	m_redBrick.Draw(m_gfx);
	m_ball.Draw(m_gfx);
}
