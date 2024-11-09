#include "Paddle.h"
#include "MainWindow.h"
#include "Ball.h"
#include "Wall.h"

namespace BrickBreaker
{
	/*--------------*
	 *    Paddle    *
	 *--------------*/

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

		if (m_canHandleCollisionBall &&
			m_rectangle.IsCollision(m_ball.GetRectangle()))
		{
			HandleCollisionBall(deltaTime);
			DisableHandleCollisionBall();
		}
	}

	void Paddle::Draw() const
	{
		RectanglePaddle::Draw(m_gfx, m_rectangle.GetPosition(), GetColor());
	}

	void Paddle::Move()
	{
		const float xMouse = static_cast<float>(m_wnd.mouse.GetPosX());
		m_velocity = Vector(xMouse - m_rectangle.GetCenter().x, 0.0f);

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

		Vector velocityReboundBall;

		// Ball이 Paddle의 왼쪽, 오른쪽 변에서 튕기는 경우
		if (std::min(diffLeft, diffRight) <= std::min(diffTop, diffBottom))
		{
			m_ball.ReboundX(m_ball.GetDirection());
			velocityReboundBall = m_ball.GetDirection().GetNormalized() * m_ball.GetSpeed() * deltaTime;
		}

		// Ball이 Paddle의 윗쪽, 아랫쪽 변에서 튕기는 경우
		if (std::min(diffTop, diffBottom) <= std::min(diffLeft, diffRight))
		{
			const Vector directionReboundBall = (m_ball.GetRectangle().GetCenter() - m_rectangle.GetCenter()).GetNormalized();
			velocityReboundBall = directionReboundBall * m_ball.GetSpeed() * deltaTime;
		}

		// Paddle의 velocity를 튕기는 Ball의 velocity에 더한다
		velocityReboundBall += m_velocity * s_factorVelocityOnReboundBall;

		Vector directionReboundBall = velocityReboundBall;

		// 위로 튕기는 Ball의 velocity가 최소 기울기보다 작으면 최소 기울기에 맞춘다
		if ((velocityReboundBall.y < 0.0f) &&
			(std::abs(velocityReboundBall.y / velocityReboundBall.x) < s_minTanReboundBall))
		{
			directionReboundBall = Vector((std::signbit(velocityReboundBall.x) ? -1.0f : 1.0f), 
										  -s_minTanReboundBall);
		}

		m_ball.SetDirection(directionReboundBall);
	}

	bool Paddle::IsCollisionWall(const RectanglePaddle& rectangle)
	{
		const float leftWall = WallManager::GetPosition().x 
							   + Wall::GetSize().x 
							   - 1.0f;
		const float rightWall = WallManager::GetPosition().x 
							   + (WallManager::GetWidth() * Wall::GetSize().x) 
							   - Wall::GetSize().x + 1.0f;

		return ((rectangle.GetLeft() <= leftWall) || 
				(rightWall <= rectangle.GetRight()));
	}
}