/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "GameObject.h"

#include <list>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	~Game();
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
	void DrawPoos();
	void MovePoos();
	void DeletePoosCollided(const GameObject* pObj);
	void StartGame();
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	GameObjectFactory					gameObjFactory;
	GameObjectType::Face*				pFace = gameObjFactory.Create<GameObjectType::Face>(400, 300);
	GameObjectType::GameOver*			pGameOver = gameObjFactory.Create<GameObjectType::GameOver>(400 - GameObjectType::GameOver::WIDTH / 2, 
																									300 - GameObjectType::GameOver::HEIGHT / 2);
	GameObjectType::Title*				pTitle = gameObjFactory.Create<GameObjectType::Title>(400 - GameObjectType::Title::WIDTH / 2,
																							  300 - GameObjectType::Title::HEIGHT / 2);
	std::list<GameObjectType::Poo*>		poos =
	{ 
		gameObjFactory.Create<GameObjectType::Poo>(), 
		gameObjFactory.Create<GameObjectType::Poo>(),
		gameObjFactory.Create<GameObjectType::Poo>(),
	};
	bool isStarted = false;
};