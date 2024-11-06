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

		if (m_ball.CanPaddleHandleCollision() &&
			m_rectangle.IsCollision(m_ball.GetRectangle()))
		{
			HandleCollisionBall();
			m_ball.DeterminePaddleCanHandleCollision(*this);
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

		// Ball의 x축 방향을 반대로 바꾼다
		if (std::min(diffLeft, diffRight) <= std::min(diffTop, diffBottom))
		{
			m_ball.ReboundX(m_ball.GetDirection());
		}

		// Ball의 y축 방향을 반대로 바꾼다
		if (std::min(diffTop, diffBottom) <= std::min(diffLeft, diffRight))
		{
			m_ball.ReboundY(m_ball.GetDirection());
		}

		// 튕기는 Ball의 속도 벡터에 Paddle의 속도 벡터를 더한다
		if (m_direction.x != 0.0f)
		{
			const Vector& velocityBall = m_ball.GetDirection().GetNormalized() * m_ball.GetSpeed();
			const Vector& velocityPaddle = m_direction.GetNormalized() * GetSpeed();

			m_ball.SetDirection(velocityBall + velocityPaddle);
		}
	}
}