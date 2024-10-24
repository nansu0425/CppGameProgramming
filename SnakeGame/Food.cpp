#include "Food.h"

#include <cassert>

Food::Food(Grid& grid, const PosGrid& pos)
	: m_pos(pos)
{
	grid.SetColorCell(m_pos, s_color);
	grid.SetTypeOccupied(m_pos, ObjectType::FOOD);
}

void Food::Draw(const Grid& grid) const
{
	grid.Draw(m_pos);
}

void FoodManager::DrawFoods() const
{
	for (const auto& pair : m_foods)
	{
		pair.second.Draw(m_grid);
	}
}

void FoodManager::SpawnFood()
{
	if (!IsCountSpawn())
	{
		return;
	}

	PosGrid pos = {m_row(m_rng), m_col(m_rng)};

	while (m_grid.GetTypeOccupied(pos) != ObjectType::NONE)
	{
		pos = {m_row(m_rng), m_col(m_rng)};
	}

	m_foods.emplace(ConvertKey(pos), Food(m_grid, pos));
}

void FoodManager::EatFood(const PosGrid& pos)
{
	assert(m_grid.GetTypeOccupied(pos) == ObjectType::FOOD);

	m_foods.erase(ConvertKey(pos));
	m_grid.SetTypeOccupied(pos, ObjectType::NONE);
}

bool FoodManager::IsCountSpawn()
{
	if (m_counterSpawn < m_periodSpawn)
	{
		++m_counterSpawn;
		return false;
	}

	m_counterSpawn = 0;

	return true;
}
