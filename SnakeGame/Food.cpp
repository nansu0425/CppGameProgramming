#include "Food.h"

#include <cassert>

Food::Food(Grid& grid, std::mt19937& rng)
	: m_grid(grid)
	, m_rng(rng)
	, m_row(0, grid.m_lenRow - 1)
	, m_col(0, grid.m_lenCol - 1)
{
	Spawn();
}

void Food::Draw() const
{
	m_grid.Draw(m_pos);
}

void Food::Respawn()
{
	m_grid.SetTypeOccupied(m_pos, ObjectType::NONE);
	Spawn();
}

void Food::Spawn()
{
	PosGrid newPos = {m_row(m_rng), m_col(m_rng)};

	while (m_grid.GetTypeOccupied(newPos) != ObjectType::NONE)
	{
		newPos = {m_row(m_rng), m_col(m_rng)};
	}

	m_pos = newPos;
	m_grid.SetColorCell(m_pos, s_color);
	m_grid.SetTypeOccupied(m_pos, ObjectType::FOOD);
}
