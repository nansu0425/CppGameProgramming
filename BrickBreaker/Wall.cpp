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

	void Wall::Update(Ball& ball, Paddle& paddle, bool isWallTop)
	{
		// Ball과 충돌 발생
		if (m_rectangle.IsCollision(ball.GetRectangle()))
		{
			HandleCollisionBall(ball, isWallTop);
			
			paddle.EnableHandleCollisionBall();
		}
	}

	void Wall::Draw(Graphics& gfx) const
	{
		RectangleWall::Draw(gfx, m_rectangle.GetPosition(), GetColor(), GetThicknessBorder());
	}

	void Wall::HandleCollisionBall(Ball& ball, bool isWallTop) const
	{
		const Vector& dirBall = ball.GetDirection();
		const bool isCollisionLeftWall = ((ball.GetRectangle().GetLeft() <= m_rectangle.GetRight()) &&
										  (m_rectangle.GetRight() < ball.GetRectangle().GetRight()));
		const bool isCollisionRightWall = ((m_rectangle.GetLeft() <= ball.GetRectangle().GetRight()) &&
										   (ball.GetRectangle().GetLeft() < m_rectangle.GetLeft()));

		// 윗쪽 벽 충돌
		if (isWallTop)
		{
			ball.SetDirection(Vector(dirBall.x, 
									 std::abs(dirBall.y)));
		}
		// 왼쪽 벽 충돌
		else if (isCollisionLeftWall)
		{
			ball.SetDirection(Vector(std::abs(dirBall.x), 
									 dirBall.y));
		}
		// 오른쪽 벽 충돌
		else if (isCollisionRightWall)
		{
			ball.SetDirection(Vector(std::abs(dirBall.x) * -1, 
									 dirBall.y));
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
		// 윗쪽 벽
		for (Wall& wall : m_wallsTop)
		{
			wall.Update(ball, paddle, true);
		}

		// 왼쪽 벽
		for (Wall& wall : m_wallsLeft)
		{
			wall.Update(ball, paddle, false);
		}

		// 오른쪽 벽
		for (Wall& wall : m_wallsRight)
		{
			wall.Update(ball, paddle, false);
		}
	}
}
