#include "Wall.h"
#include "Graphics.h"

namespace BrickBreaker
{
	/*------------*
	 *    Wall    *
	 *------------*/

	void Wall::Draw(Graphics& gfx) const
	{
		RectangleWall::Draw(gfx, m_rectangle.GetPosition(), GetColor(), GetThicknessBorder());
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
}
