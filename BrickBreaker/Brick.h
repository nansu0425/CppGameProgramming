#pragma once

#include "Rectangle.h"
#include "Globals.h"
#include "array"

class Graphics;
class Color;

namespace BrickBreaker
{
	class Ball;
}

namespace BrickBreaker
{
	/*-------------*
	 *    Brick    *
	 *-------------*/

	class Brick
	{
	private:
		using				Rectangle = Rectangle<GBrick::g_size>;

	public:
							Brick() = default;
							Brick(const Vector& position, const Color& color);

		void				Draw(Graphics& gfx) const;
		void				Update(float deltaTime) {}

		const Vector&		GetPosition() const { return m_rectangle.GetPosition(); }
		void				SetPosition(const Vector& position) { m_rectangle.SetPosition(position); }
		const Vector&		GetSize() const { return GBrick::g_size; }
		const Rectangle&	GetRectangle() const { return m_rectangle; }
		const Color&		GetColor() const { return m_color; }
		bool				IsBroken() const { return m_bBroken; }
		void				SetBroken() { m_bBroken = true; }

	private:
		Rectangle			m_rectangle;
		Color				m_color;
		bool				m_bBroken = false;
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

		void				Draw(Graphics& gfx) const;

	private:
		Ball&				m_ball;
		Array				m_bricks;
	};
}
