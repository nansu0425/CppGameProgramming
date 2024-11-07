#pragma once

#include "Vector.h"
#include "Colors.h"
#include "Graphics.h"

namespace BrickBreaker
{
	namespace GBrick
	{
		constexpr Vector			g_size(40.0f, 20.0f);
		constexpr int				g_thicknessBorder = 1;
	}

	namespace GBrickManager
	{
		constexpr size_t			g_rowBricks = 4;
		constexpr size_t			g_colBricks = 18;
		constexpr Color				g_colors[g_rowBricks] =
		{
			Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan,
		};
		constexpr Vector			g_position(40.0f, 40.0f);
	}

	namespace GBall
	{
		constexpr Vector			g_size(14.0f, 14.0f);
		constexpr size_t			g_speed = 600;
		constexpr Vector			g_initPosition(400.0f - g_size.x / 2,
												   400.0f - g_size.y / 2);
		constexpr float				g_rangeDirectionX = 0.7f;
	}

	namespace GPaddle
	{
		constexpr Vector			g_size(100.0f, 30.0f);
		constexpr float				g_speed = 500.0f;
		constexpr Vector			g_initPosition(400.0f - g_size.x / 2, 500.0f);
		constexpr Color				g_color = Colors::White;
	}

	namespace GWall
	{
		constexpr Vector			g_size(20.0f, 20.0f);
		constexpr Color				g_color = Colors::Gray;
		constexpr int				g_thicknessBorder = 1;
	}

	namespace GWallManager
	{
		constexpr size_t			g_width = 32;
		constexpr size_t			g_height = Graphics::ScreenHeight / static_cast<int>(GWall::g_size.y);
	}
}
