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
	, gameObjFactory(wnd, gfx)
{}

Game::~Game()
{
	if (pFace != nullptr)
	{
		delete pFace;
	}

	if (pGameOver != nullptr)
	{
		delete pGameOver;
	}

	if (pTitle != nullptr)
	{
		delete pTitle;
	}

	for (GameObjectType::Poo* pPoo : poos)
	{
		if (pPoo != nullptr)
		{
			delete pPoo;
		}
	}
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
	const float secondsDeltaTime = frameTimer.GetSecondsDeltaTime();

	if (!isStarted)
	{
		StartGame();
		return;
	}

	pFace->Move(secondsDeltaTime);

	if (!poos.empty())
	{
		MovePoos(secondsDeltaTime);
		DeletePoosCollided(pFace);
	}
}

void Game::ComposeFrame()
{
	if (!isStarted)
	{
		pTitle->Draw();
		return;
	}

	if (poos.empty())
	{
		pGameOver->Draw();
	}
	else
	{
		DrawPoos();
	}

	pFace->Draw();
}

void Game::DrawPoos()
{
	for (const GameObjectType::Poo* pPoo : poos)
	{
		pPoo->Draw();
	}
}

void Game::MovePoos(float secondsDeltaTime)
{
	for (GameObjectType::Poo* pPoo : poos)
	{
		pPoo->Move(secondsDeltaTime);
	}
}

void Game::DeletePoosCollided(const GameObject* pObj)
{
	auto iterPoo = poos.begin();

	while (iterPoo != poos.end())
	{
		if ((*iterPoo)->CheckCollision(pObj))
		{
			auto iterErase = iterPoo;
			++iterPoo;

			delete *iterErase;
			poos.erase(iterErase);
		}
		else
		{
			++iterPoo;
		}
	}
}

void Game::StartGame()
{
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		isStarted = true;
	}
}
