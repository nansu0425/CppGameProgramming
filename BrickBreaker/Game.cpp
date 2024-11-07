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
#include "Globals.h"

Game::Game( MainWindow& wnd )
	: m_wnd( wnd )
	, m_gfx( wnd )
	, m_brickManager(m_ball)
	, m_paddle(m_gfx, m_wnd, m_ball)
	, m_wallManager(m_gfx)
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

	m_paddle.Update(deltaTime);
	m_brickManager.Update(m_paddle);
	m_ball.Update(deltaTime, m_gfx, m_paddle);
	m_wallManager.Update(m_ball, m_paddle);
}

void Game::ComposeFrame()
{
	m_wallManager.Draw();
	m_brickManager.Draw(m_gfx);
	m_ball.Draw(m_gfx);
	m_paddle.Draw();
}
