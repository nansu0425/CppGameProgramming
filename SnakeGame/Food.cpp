#include "Food.h"
#include "Wall.h"

#include <cassert>

Food::Food(Grid& grid, std::mt19937& rng)
	: m_grid(grid)
	, m_rng(rng)
	, m_row(Wall::s_length, grid.s_lenRow - Wall::s_length - 1)
	, m_col(Wall::s_length, grid.s_lenCol - Wall::s_length - 1)
{
	Spawn();
}

void Food::Draw() const
{
	m_grid.Draw(m_pos);
}

void Food::Respawn()
{
	PosGrid prevFood = m_pos;
	Spawn();
	m_grid.SetTypeOccupied(prevFood, ObjectType::NONE);
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
