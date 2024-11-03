#include "Brick.h"
#include "Graphics.h"
#include "Ball.h"

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
		for (int dx = GBrick::g_thicknessBorder; dx < static_cast<int>(GetSize().x) - GBrick::g_thicknessBorder; ++dx)
		{
			for (int dy = GBrick::g_thicknessBorder; dy < static_cast<int>(GetSize().y) - GBrick::g_thicknessBorder; ++dy)
			{
				gfx.PutPixel(static_cast<int>(GetPosition().x) + dx,
							 static_cast<int>(GetPosition().y) + dy,
							 GetColor());
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

	void BrickManager::Update()
	{
		for (auto& rowBricks : m_bricks)
		{
			for (Brick& brick : rowBricks)
			{
				if (!brick.IsBroken() && 
					brick.IsCollision(m_ball.GetRectangle()))
				{
					brick.SetBroken();

					// TODO: 공 튕기는 것 구현
				}
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
