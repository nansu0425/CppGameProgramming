#include "Wall.h"
#include "Graphics.h"
#include "Ball.h"

#include <algorithm>
#include <cmath>

namespace BrickBreaker
{
	/*------------*
	 *    Wall    *
	 *------------*/

	void Wall::Update(Ball& ball, const Paddle& paddle, bool& canHandleCollisionBall, bool& isCollisionBall, bool isWallTop)
	{
		// Ball의 충돌 처리를 할 수 있는 상태
		if (canHandleCollisionBall)
		{
			if (m_rectangle.IsCollision(ball.GetRectangle()))
			{
				HandleCollisionBall(ball, isWallTop);
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

	void Wall::HandleCollisionBall(Ball& ball, bool isWallTop) const
	{
		const Vector& dirBall = ball.GetDirection();
		const float diffLeft = ball.GetRectangle().GetLeft() - m_rectangle.GetLeft();
		const float diffRight = m_rectangle.GetRight() - ball.GetRectangle().GetRight();

		// 윗쪽 벽 충돌
		if (isWallTop)
		{
			ball.SetDirection(Vector(dirBall.x, std::abs(dirBall.y)));
		}
		// 왼쪽 벽 충돌
		else if (diffLeft < 0)
		{
			ball.SetDirection(Vector(-1 * std::abs(dirBall.x), dirBall.y));
		}
		// 오른쪽 벽 충돌
		else if (diffRight < 0)
		{
			ball.SetDirection(Vector(std::abs(dirBall.x), dirBall.y));
		}
	}

	/*-------------------*
	 *    WallManager    *
	 *-------------------*/

	WallManager::WallManager(Graphics& gfx)
		: m_gfx(gfx)
	{
		// 윗쪽 벽의 위치 설정
		for (int col = 1; col < GetWidth() - 1; ++col)
		{
			m_wallsTop[col - 1].SetPosition(Vector(GetPosition().x + Wall::GetSize().x * col, 
												   GetPosition().y));
		}

		// 왼쪽, 오른쪽 벽의 위치 설정
		for (int row = 0; row < GetHeight(); ++row)
		{
			m_wallsLeft[row].SetPosition(Vector(m_wallsTop[0].GetPosition().x - Wall::GetSize().x,
												GetPosition().y + Wall::GetSize().y * row));

			m_wallsRight[row].SetPosition(Vector(m_wallsTop[GetWidth() - 3].GetPosition().x + Wall::GetSize().x,
												 GetPosition().y + Wall::GetSize().y * row));
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

	void WallManager::Update(Ball& ball, Paddle& paddle)
	{
		bool isCollisionBall = false;

		// 윗쪽 벽
		for (Wall& wall : m_wallsTop)
		{
			wall.Update(ball, paddle, m_canHandleCollisionBall, isCollisionBall, true);

			if (isCollisionBall)
			{
				return;
			}
		}

		// 왼쪽 벽
		for (Wall& wall : m_wallsLeft)
		{
			wall.Update(ball, paddle, m_canHandleCollisionBall, isCollisionBall, false);

			if (isCollisionBall)
			{
				return;
			}
		}

		// 오른쪽 벽
		for (Wall& wall : m_wallsRight)
		{
			wall.Update(ball, paddle, m_canHandleCollisionBall, isCollisionBall, false);

			if (isCollisionBall)
			{
				return;
			}
		}

		// Ball이 모든 Wall와 충돌하지 않으면 Ball의 충돌을 처리할 수 있는 상태가 된다
		m_canHandleCollisionBall = true;
	}
}
