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
		Move(deltaTime);

		if ((m_ball.GetDirection().y > 0.0f) &&
			m_rectangle.IsCollision(m_ball.GetRectangle()))
		{
			HandleCollisionBall();
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

	void Paddle::HandleCollisionBall()
	{
		const float diffLeft = m_ball.GetRectangle().GetLeft() - m_rectangle.GetLeft();
		const float diffRight = m_rectangle.GetRight() - m_ball.GetRectangle().GetRight();
		const float diffTop = m_ball.GetRectangle().GetTop() - m_rectangle.GetTop();
		const float diffBottom = m_rectangle.GetBottom() - m_ball.GetRectangle().GetBottom();

		// Paddle의 윗쪽 변과 충돌할 때만 공을 튕긴다
		if (!((diffBottom > 0) && (diffTop < 0)))
		{
			return;
		}

		// 충돌 인정 범위
		if (diffTop <= std::min(diffLeft, diffRight))
		{
			m_ball.ReboundY(m_ball.GetDirection());
		}
	}
}