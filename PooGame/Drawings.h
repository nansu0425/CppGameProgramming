#pragma once

#include "Graphics.h"

class Drawings
{
public:
	static void DrawFace(Graphics& gfx, int x, int y);
	static void DrawGameOver(Graphics& gfx, int x, int y);
	static void DrawPoo(Graphics& gfx, int x, int y);
	static void DrawTitle(Graphics& gfx, int x, int y);
};
