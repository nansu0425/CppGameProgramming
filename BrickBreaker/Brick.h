#pragma once

#include "Rectangle.h"
#include "Globals.h"
#include "array"

class Graphics;
class Color;

namespace BrickBreaker
{
	class Ball;
	class Paddle;
}

namespace BrickBreaker
{
	/*-------------*
	 *    Brick    *
	 *-------------*/

	class Brick
	{
	private:
		using					RectangleBrick = Rectangle<GBrick::g_size>;

	public:
								Brick() = default;
								Brick(const Vector& position, const Color& color);

		void					Draw(Graphics& gfx) const;
		void					Update(Ball& ball, const Paddle& paddle, bool& isOtherBrickCollisionBall);

		const Vector&			GetPosition() const { return m_rectangle.GetPosition(); }
		void					SetPosition(const Vector& position) { m_rectangle.SetPosition(position); }
		const Vector&			GetSize() const { return GBrick::g_size; }
		const RectangleBrick&	GetRectangle() const { return m_rectangle; }
		const Color&			GetColor() const { return m_color; }
		bool					IsBroken() const { return m_bBroken; }
		void					SetBroken() { m_bBroken = true; }
		template<const Vector& sizeOther>
		bool					IsCollision(const Rectangle<sizeOther>& other) const { return m_rectangle.IsCollision(other); }

	private:
		void					HandleCollisionBall(Ball& ball);

	private:
		RectangleBrick			m_rectangle;
		Color					m_color;
		bool					m_bBroken = false;
	};

	/*--------------------*
	 *    BrickManager    *
	 *--------------------*/

	class BrickManager
	{
	private:
		using				Array = std::array<std::array<Brick, GBrickManager::g_colBricks>, GBrickManager::g_rowBricks>;

	public:
							BrickManager(Ball& ball);

		void				Update(const Paddle& paddle);
		void				Draw(Graphics& gfx) const;

	private:
		Ball&				m_ball;
		Array				m_bricks;
		bool				m_isOtherBrickCollisionBall = false;
	};
}
