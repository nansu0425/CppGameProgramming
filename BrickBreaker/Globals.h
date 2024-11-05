#pragma once

#include "Vector.h"
#include "Colors.h"

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
		constexpr size_t			g_speed = 400;
	}

	namespace GPaddle
	{
		constexpr Vector			g_size(100.0f, 30.0f);
		constexpr float				g_speed = 500.0f;
	}
}
