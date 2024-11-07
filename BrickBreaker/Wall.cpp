#include "Wall.h"
#include "Graphics.h"
#include "Ball.h"

#include <algorithm>

namespace BrickBreaker
{
	/*------------*
	 *    Wall    *
	 *------------*/

	void Wall::Update(Ball& ball, const Paddle& paddle, bool& canHandleCollisionBall, bool& isCollisionBall)
	{
		// Ball의 충돌 처리를 할 수 있는 상태
		if (canHandleCollisionBall)
		{
			if (m_rectangle.IsCollision(ball.GetRectangle()))
			{
				HandleCollisionBall(ball);
				ball.DeterminePaddleCanHandleCollision(paddle);
				
				// Ball과 한번이라도 충돌이 발생하면 충돌 처리를 할 수 없는 상태가 된다
				canHandleCollisionBall = false;
				isCollisionBall = true;
			}
		}
		// 이전에 Ball과 충돌하지 않았으면 현재 Wall와 충돌이 있는지 검사
		else
		{
			isCollisionBall = m_rectangle.IsCollision(ball.GetRectangle());
		}
	}

	void Wall::Draw(Graphics& gfx) const
	{
		RectangleWall::Draw(gfx, m_rectangle.GetPosition(), GetColor(), GetThicknessBorder());
	}

	void Wall::HandleCollisionBall(Ball& ball) const
	{
		const float diffLeft = ball.GetRectangle().GetLeft() - m_rectangle.GetLeft();
		const float diffRight = m_rectangle.GetRight() - ball.GetRectangle().GetRight();
		const float diffTop = ball.GetRectangle().GetTop() - m_rectangle.GetTop();
		const float diffBottom = m_rectangle.GetBottom() - ball.GetRectangle().GetBottom();

		// Ball의 x축 방향을 반대로 바꾼다
		if (std::min(diffLeft, diffRight) <= std::min(diffTop, diffBottom))
		{
			ball.ReboundX(ball.GetDirection());
		}

		// Ball의 y축 방향을 반대로 바꾼다
		if (std::min(diffTop, diffBottom) <= std::min(diffLeft, diffRight))
		{
			ball.ReboundY(ball.GetDirection());
		}
	}

	/*-------------------*
	 *    WallManager    *
	 *-------------------*/

	WallManager::WallManager(Graphics& gfx)
		: m_gfx(gfx)
		, m_position((Graphics::ScreenWidth / 20 - GetWidth()) / 2 * 20.0f, 0.0f)
	{
		// 윗쪽 벽의 위치 설정
		for (int col = 1; col < GetWidth() - 1; ++col)
		{
			m_wallsTop[col - 1].SetPosition(Vector(m_position.x + Wall::GetSize().x * col, 
												   m_position.y));
		}

		// 왼쪽, 오른쪽 벽의 위치 설정
		for (int row = 0; row < GetHeight(); ++row)
		{
			m_wallsLeft[row].SetPosition(Vector(m_wallsTop[0].GetPosition().x,
												m_position.y + Wall::GetSize().y * row));

			m_wallsRight[row].SetPosition(Vector(m_wallsTop[GetWidth() - 3].GetPosition().x,
												 m_position.y + Wall::GetSize().y * row));
		}
	}

	void WallManager::Draw() const
	{
		for (const Wall& wall : m_wallsTop)
		{
			wall.Draw(m_gfx);
		}

		for (const Wall& wall : m_wallsLeft)
		{
			wall.Draw(m_gfx);
		}

		for (const Wall& wall : m_wallsRight)
		{
			wall.Draw(m_gfx);
		}
	}

	void WallManager::Update(Ball& ball, const Paddle& paddle)
	{
		bool isCollisionBall = false;

		for (Wall& wall : m_wallsTop)
		{
			wall.Update(ball, paddle, m_canHandleCollisionBall, isCollisionBall);

			if (isCollisionBall)
			{
				return;
			}
		}

		for (Wall& wall : m_wallsLeft)
		{
			wall.Update(ball, paddle, m_canHandleCollisionBall, isCollisionBall);

			if (isCollisionBall)
			{
				return;
			}
		}

		for (Wall& wall : m_wallsRight)
		{
			wall.Update(ball, paddle, m_canHandleCollisionBall, isCollisionBall);

			if (isCollisionBall)
			{
				return;
			}
		}

		// Ball이 모든 Wall와 충돌하지 않으면 Ball의 충돌을 처리할 수 있는 상태가 된다
		m_canHandleCollisionBall = true;
	}
}
