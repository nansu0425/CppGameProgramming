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
	/*--------------*
	 *    Paddle    *
	 *--------------*/

	class Paddle
	{
	private:
		using					RectanglePaddle = Rectangle<GPaddle::g_size>;

	public:
								Paddle(Graphics& gfx, const MainWindow& wnd, Ball& ball);
								Paddle(Graphics& gfx, const MainWindow& wnd, Ball& ball, const Vector& position);

		void					Update(float deltaTime);
		void					Draw() const;
		const RectanglePaddle&	GetRectangle() const { return m_rectangle; }

		static float			GetSpeed() { return GPaddle::g_speed; }
		static const Vector&	GetSize() { return GPaddle::g_size; }
		static const Color&		GetColor() { return GPaddle::g_color; }

	private:
		void					Move();
		RectanglePaddle			GetNextMoveRectangle() const { return m_rectangle.GetPosition() + m_velocity; }
		void					HandleCollisionBall(float deltaTime);
		bool					IsCollisionWall(const RectanglePaddle& rectangle);

	private:
		static constexpr float	s_factorVelocityOnReboundBall = 0.8f;
		static constexpr float	s_minTanReboundBall = 0.5f;

		Graphics&				m_gfx;
		const MainWindow&		m_wnd;
		Ball&					m_ball;
		RectanglePaddle			m_rectangle;
		Vector					m_direction;
		Vector					m_velocity;
		bool					m_isCollisionWall = false;
	};
}
