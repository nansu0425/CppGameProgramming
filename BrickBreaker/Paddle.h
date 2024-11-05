﻿#pragma once

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

		float					GetSpeed() const { return GPaddle::g_speed; }

	private:
		void					Move(float deltaTime);

	private:
		Graphics&				m_gfx;
		const MainWindow&		m_wnd;
		Ball&					m_ball;
		Color					m_color = Colors::Gray;
		RectanglePaddle			m_rectangle;
		Vector					m_direction;
		
	};
}
