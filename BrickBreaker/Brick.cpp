#include "Brick.h"
#include "Graphics.h"
#include "Ball.h"

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
		/*for (int dx = GBrick::g_thicknessBorder; dx < static_cast<int>(GetSize().x) - GBrick::g_thicknessBorder; ++dx)
		{
			for (int dy = GBrick::g_thicknessBorder; dy < static_cast<int>(GetSize().y) - GBrick::g_thicknessBorder; ++dy)
			{
				gfx.PutPixel(static_cast<int>(GetPosition().x) + dx,
							 static_cast<int>(GetPosition().y) + dy,
							 GetColor());
			}
		}*/

		RectangleBrick::Draw(gfx, GetPosition(), GetColor(), GBrick::g_thicknessBorder);
	}

	void Brick::Update(Ball& ball)
	{
		if (!IsBroken() &&
			IsCollision(ball.GetRectangle()))
		{
			SetBroken();
			ReboundBall(ball);
		}
	}

	void Brick::ReboundBall(Ball& ball)
	{
		const float diffLeft = ball.GetRectangle().GetLeft() - GetRectangle().GetLeft();
		const float diffRight = GetRectangle().GetRight() - ball.GetRectangle().GetRight();
		const float diffTop = ball.GetRectangle().GetTop() - GetRectangle().GetTop();
		const float diffBottom = GetRectangle().GetBottom() - ball.GetRectangle().GetBottom();

		if ((diffLeft >= 0) &&
			(diffRight >= 0))
		{
			ball.ReboundY(ball.GetDirection());
		}
		else if ((diffTop >= 0) &&
				 (diffBottom >= 0))
		{
			ball.ReboundX(ball.GetDirection());
		}
		else if (std::min(diffLeft, diffRight) < std::min(diffTop, diffBottom))
		{
			ball.ReboundX(ball.GetDirection());
		}
		else if (std::min(diffTop, diffBottom) < std::min(diffLeft, diffRight))
		{
			ball.ReboundY(ball.GetDirection());
		}
		else
		{
			ball.ReboundX(ball.GetDirection());
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

	void BrickManager::Update()
	{
		for (auto& rowBricks : m_bricks)
		{
			for (Brick& brick : rowBricks)
			{
				brick.Update(m_ball);
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
