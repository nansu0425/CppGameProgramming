#include "Paddle.h"
#include "MainWindow.h"
#include "Ball.h"
#include "Wall.h"

namespace BrickBreaker
{
	Paddle::Paddle(Graphics& gfx, const MainWindow& wnd, Ball& ball)
		: Paddle(gfx, wnd, ball, GPaddle::g_initPosition)
	{}
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
		RectanglePaddle::Draw(m_gfx, m_rectangle.GetPosition(), GetColor());
	}

	void Paddle::Move()
	{
		const Vector mouse(static_cast<float>(m_wnd.mouse.GetPosX()), 
						   static_cast<float>(m_wnd.mouse.GetPosY()));
		const Vector center(m_rectangle.GetPosition() + GetSize() / 2);

		m_velocity = Vector(mouse.x - center.x, 0.0f);

		const RectanglePaddle& next = GetNextMoveRectangle();

		if (IsCollisionWall(next))
		{
			m_velocity = Vector();
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

		Vector velocityReboundBall = m_ball.GetDirection().GetNormalized() * m_ball.GetSpeed() * deltaTime;

		// Paddle이 멈춰있을 땐 Ball velocity의 x성분 영향력이 감소한다
		if (m_velocity.x == 0.0f)
		{
			velocityReboundBall.x /= 2;
		}
		// Paddle이 움직일 땐 Paddle의 실제 velocity보다 영향력을 줄인다
		else
		{
			velocityReboundBall += m_velocity / 2;
		}
		
		m_ball.SetDirection(velocityReboundBall);
		
	}

	bool Paddle::IsCollisionWall(const RectanglePaddle& rectangle)
	{
		const float leftWall = WallManager::GetPosition().x 
							   + Wall::GetSize().x 
							   - 1.0f;
		const float rightWall = WallManager::GetPosition().x 
							   + (WallManager::GetWidth() * Wall::GetSize().x) 
							   - Wall::GetSize().x + 1.0f;

		return ((rectangle.GetLeft() <= leftWall) || (rightWall <= rectangle.GetRight()));
	}
}