#pragma once

#include "Rectangle.h"
#include "Globals.h"

#include <array>

class Graphics;

namespace BrickBreaker
{
	class Ball;
	class Paddle;
}

namespace BrickBreaker
{
	/*------------*
	 *    Wall    *
	 *------------*/

	class Wall
	{
	private:
		using					RectangleWall = Rectangle<GWall::g_size>;

	public:
		void					Update(Ball& ball, Paddle& paddle, bool isWallTop);
		void					Draw(Graphics& gfx) const;

		static const Color&		GetColor() { return GWall::g_color; }
		static int				GetThicknessBorder() { return GWall::g_thicknessBorder; }
		static const Vector&	GetSize() { return GWall::g_size; }

		const Vector&			GetPosition() const { return m_rectangle.GetPosition(); }
		void					SetPosition(const Vector& position) { m_rectangle.SetPosition(position); }

	private:
		void					HandleCollisionBall(Ball& ball, bool isWallTop) const;

	private:
		RectangleWall			m_rectangle;
	};

	/*-------------------*
	 *    WallManager    *
	 *-------------------*/

	class WallManager
	{
	private:
		using					RectangleWall = Rectangle<GWall::g_size>;
		using					ArrayTop = std::array<Wall, GWallManager::g_width - 2>;
		using					ArrayLeft = std::array<Wall, GWallManager::g_height>;
		using					ArrayRight = std::array<Wall, GWallManager::g_height>;

	public:
								WallManager(Graphics& gfx);

		void					Draw() const;
		void					Update(Ball& ball, Paddle& paddle);
		
		static size_t			GetWidth() { return GWallManager::g_width; }
		static size_t			GetHeight()  { return GWallManager::g_height; }
		static const Vector&	GetPosition() { return GWallManager::g_position; }

	private:
		Graphics&				m_gfx;
		ArrayTop				m_wallsTop;
		ArrayLeft				m_wallsLeft;
		ArrayRight				m_wallsRight;
	};
}
