#include "Paddle.h"
#include "MainWindow.h"
#include "Ball.h"

namespace BrickBreaker
{
	Paddle::Paddle(Graphics& gfx, const MainWindow& wnd, Ball& ball, const Vector& position)
		: m_gfx(gfx)
		, m_wnd(wnd)
		, m_ball(ball)
		, m_rectangle(position)
	{}

	void Paddle::Update(float deltaTime)
	{
		// 이동
		Move(deltaTime);

		// Ball 충돌 처리
		if (m_rectangle.IsCollision(m_ball.GetRectangle()))
		{
			m_ball.ReboundCollision(m_rectangle);
		}
	}

	void Paddle::Draw() const
	{
		RectanglePaddle::Draw(m_gfx, m_rectangle.GetPosition(), m_color);
	}

	void Paddle::Move(float deltaTime)
	{
		m_direction.x = 0.0f;

		if (m_wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			--m_direction.x;
		}
		
		if (m_wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			++m_direction.x;
		}

		const RectanglePaddle& next = GetNextMoveRectangle(deltaTime);

		if (next.IsOutScreenX(m_gfx))
		{
			return;
		}

		m_rectangle = next;
	}
}