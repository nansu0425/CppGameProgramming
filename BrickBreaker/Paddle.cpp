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
		Move();

		if (m_ball.CanPaddleHandleCollision() &&
			m_rectangle.IsCollision(m_ball.GetRectangle()))
		{
			HandleCollisionBall(deltaTime);
			m_ball.DeterminePaddleCanHandleCollision(*this);
		}
	}

	void Paddle::Draw() const
	{
		RectanglePaddle::Draw(m_gfx, m_rectangle.GetPosition(), m_color);
	}

	void Paddle::Move()
	{
		const Vector mouse(static_cast<float>(m_wnd.mouse.GetPosX()), 
						   static_cast<float>(m_wnd.mouse.GetPosY()));
		const Vector center(m_rectangle.GetPosition() + GetSize() / 2);

		m_velocity = Vector(mouse.x - center.x, 0.0f);

		const RectanglePaddle& next = GetNextMoveRectangle();

		if (next.IsOutScreenX(m_gfx))
		{
			return;
		}

		m_rectangle = next;
	}

	void Paddle::HandleCollisionBall(float deltaTime)
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

		// Ball이 튕길 때 Paddle의 속도 벡터를 더한다
		Vector velocityBall = m_ball.GetDirection().GetNormalized() * m_ball.GetSpeed() * deltaTime;

		// Paddle이 멈춰있을 땐 Ball 속도 벡터의 x성분 영향력이 감소한다
		if (m_velocity.x == 0.0f)
		{
			velocityBall.x /= 2;
		}
		
		// Paddle의 실제 속도 벡터보다 영향력을 줄인다
		m_ball.SetDirection(velocityBall + m_velocity / 2);
		
	}
}