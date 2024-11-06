#pragma once

#include "Rectangle.h"
#include "Globals.h"

class MainWindow;

namespace BrickBreaker
{
	class Ball;
}

namespace BrickBreaker
{
	/*-------------*
	 *    Brick    *
	 *-------------*/

	class Paddle
	{
	private:
		using					RectanglePaddle = Rectangle<GPaddle::g_size>;

	public:
								Paddle(Graphics& gfx, const MainWindow& wnd, Ball& ball, const Vector& position);

		void					Update(float deltaTime);
		void					Draw() const;
		const RectanglePaddle&	GetRectangle() const { return m_rectangle; }

		float					GetSpeed() const { return GPaddle::g_speed; }
		const Vector&			GetSize() const { return GPaddle::g_size; }

	private:
		void					Move();
		RectanglePaddle			GetNextMoveRectangle() const { return m_rectangle.GetPosition() + m_velocity; }
		void					HandleCollisionBall(float deltaTime);

	private:
		Graphics&				m_gfx;
		const MainWindow&		m_wnd;
		Ball&					m_ball;
		Color					m_color = Colors::Gray;
		RectanglePaddle			m_rectangle;
		Vector					m_direction;
		Vector					m_velocity;
	};
}
