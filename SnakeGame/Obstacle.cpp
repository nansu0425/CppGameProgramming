#include "Obstacle.h"

Obstacle::Obstacle(Grid& grid, const PosGrid& pos)
	: m_pos(pos)
{
	grid.SetColorCell(m_pos, s_color);
	grid.SetTypeOccupied(m_pos, ObjectType::OBSTACLE);
}

void Obstacle::Draw(const Grid& grid) const
{
	grid.Draw(m_pos);
}

void ObstacleManager::DrawObstacles() const
{
	for (const Obstacle& o : m_obstacles)
	{
		o.Draw(m_grid);
	}
}

void ObstacleManager::SpawnObstacle()
{
	if (!IsCountSpawn())
	{
		return;
	}

	PosGrid newPos = {m_row(m_rng), m_col(m_rng)};

	while (m_grid.GetTypeOccupied(newPos) != ObjectType::NONE)
	{
		newPos = {m_row(m_rng), m_col(m_rng)};
	}

	m_obstacles.emplace_front(m_grid, newPos);
}

bool ObstacleManager::IsCountSpawn()
{
	if (m_counterSpawn < m_periodSpawn)
	{
		++m_counterSpawn;
		return false;
	}

	m_counterSpawn = 0;

	return true;
}
