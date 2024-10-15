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

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
	int ClampCircleWindowX(int x, int r);
	int ClampCircleWindowY(int y, int r);
	void MoveCircle(int& x, int& y);
	bool CheckCollisionCircles(float x1, float y1, float r1, float x2, float y2, float r2);
	void DrawCrosshair(int x, int y, Color color);
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	int xMovingCrosshair = 400;
	int yMovingCrosshair = 300;
	int xFixedCrosshair1 = 200;
	int yFixedCrosshair1 = 300;
	int xFixedCrosshair2 = 500;
	int yFixedCrosshair2 = 100;
	int xFixedCrosshair3 = 300;
	int yFixedCrosshair3 = 250;
	int xFixedCrosshair4 = 600;
	int yFixedCrosshair4 = 500;
	Color colorMovingCrosshair = Color(255, 255, 255);
	Color colorFixedCrosshair = Color(0, 255, 0);
};