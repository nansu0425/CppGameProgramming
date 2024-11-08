#include "Brick.h"
#include "Graphics.h"
#include "Ball.h"
#include "Paddle.h"

#include <algorithm>
#include <cmath>

namespace BrickBreaker
{
	/*-------------*
	 *    Brick    *
	 *-------------*/

	Brick::Brick(const Vector& position, const Color& color)
		: m_rectangle(position)
		, m_color(color)
	{}

	void Brick::Draw(Graphics& gfx) const
	{
		RectangleBrick::Draw(gfx, GetPosition(), GetColor(), GBrick::g_thicknessBorder);
	}

	void Brick::Update(Ball& ball, const Paddle& paddle, bool& isOtherBrickCollisionBall)
	{
		if (!IsBroken() &&
			IsCollision(ball.GetRectangle()))
		{
			SetBroken();
			
			if (!isOtherBrickCollisionBall)
			{
				HandleCollisionBall(ball);
				isOtherBrickCollisionBall = true;
			}
			
			ball.DeterminePaddleCanHandleCollision(paddle);
		}
	}

	void Brick::HandleCollisionBall(Ball& ball)
	{
		const float diffLeft = ball.GetRectangle().GetLeft() - GetRectangle().GetLeft();
		const float diffRight = GetRectangle().GetRight() - ball.GetRectangle().GetRight();
		const float diffTop = ball.GetRectangle().GetTop() - GetRectangle().GetTop();
		const float diffBottom = GetRectangle().GetBottom() - ball.GetRectangle().GetBottom();

		// Ball의 x축 방향을 바꾼다
		if (std::min(diffLeft, diffRight) <= std::min(diffTop, diffBottom))
		{
			// 왼쪽 변 충돌
			if (diffLeft < 0.0f)
			{
				ball.SetDirection(Vector(-std::abs(ball.GetDirection().x), 
										 ball.GetDirection().y));
			}
			// 오른쪽 변 충돌
			else if (diffRight < 0.0f)
			{
				ball.SetDirection(Vector(std::abs(ball.GetDirection().x),
										 ball.GetDirection().y));
			}
		}

		// Ball의 y축 방향을 바꾼다
		if (std::min(diffTop, diffBottom) <= std::min(diffLeft, diffRight))
		{
			// 윗쪽 변 충돌
			if (diffTop < 0.0f)
			{
				ball.SetDirection(Vector(ball.GetDirection().x,
										 -std::abs(ball.GetDirection().y)));
			}
			// 아랫쪽 변 충돌
			else if (diffBottom < 0.0f)
			{
				ball.SetDirection(Vector(ball.GetDirection().x,
										 std::abs(ball.GetDirection().y)));
			}
		}
	}

	/*--------------------*
	 *    BrickManager    *
	 *--------------------*/

	BrickManager::BrickManager(Ball& ball)
		: m_ball(ball)
	{
		for (size_t row = 0; row < GBrickManager::g_rowBricks; ++row)
		{
			for (size_t col = 0; col < GBrickManager::g_colBricks; ++col)
			{
				const Vector& position = {GBrickManager::g_position.x + GBrick::g_size.x * static_cast<float>(col),
										  GBrickManager::g_position.y + GBrick::g_size.y * static_cast<float>(row)};

				m_bricks[row][col] = Brick(position, GBrickManager::g_colors[row]);
			}
		}
	}

	void BrickManager::Update(const Paddle& paddle)
	{
		m_isOtherBrickCollisionBall = false;

		for (auto& rowBricks : m_bricks)
		{
			for (Brick& brick : rowBricks)
			{
				brick.Update(m_ball, paddle, m_isOtherBrickCollisionBall);
			}
		}
	}

	void BrickManager::Draw(Graphics& gfx) const
	{
		for (auto& rowBricks : m_bricks)
		{
			for (const Brick& brick : rowBricks)
			{
				if (!brick.IsBroken())
				{
					brick.Draw(gfx);
				}
			}
		}
	}
}
