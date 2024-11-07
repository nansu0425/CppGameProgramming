#include "Brick.h"
#include "Graphics.h"
#include "Ball.h"
#include "Paddle.h"

#include <algorithm>

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
