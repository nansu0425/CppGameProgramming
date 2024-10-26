#include "Wall.h"
#include "Colors.h"

Wall::Wall(Grid& grid)
	: m_grid(grid)
{
	m_vecPos.reserve((m_grid.s_lenRow - 2) * 2 + (m_grid.s_lenCol - 2) * 2);

	// top
	for (int col = s_length + 1; col < grid.s_lenCol - s_length; ++col)
	{
		m_vecPos.emplace_back(PosGrid{s_length, col});
	}

	// right
	for (int row = s_length + 1; row < grid.s_lenRow - s_length; ++row)
	{
		m_vecPos.emplace_back(PosGrid{row, grid.s_lenCol - s_length - 1});
	}

	// bottom
	for (int col = s_length; col < grid.s_lenCol - s_length - 1; ++col)
	{
		m_vecPos.emplace_back(PosGrid{grid.s_lenRow - s_length - 1, col});
	}

	// left
	for (int row = s_length; row < grid.s_lenRow - s_length - 1; ++row)
	{
		
		m_vecPos.emplace_back(PosGrid{row, s_length});
	}

	for (const PosGrid& pos : m_vecPos)
	{
		m_grid.SetTypeOccupied(pos, ObjectType::WALL);
		m_grid.SetColorCell(pos, Colors::Blue);
	}
}

void Wall::Draw() const
{
	for (const PosGrid& pos : m_vecPos)
	{
		m_grid.Draw(pos);
	}
}
