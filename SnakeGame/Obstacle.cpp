#include "Obstacle.h"
#include "FrameTimer.h"

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

ObstacleManager::ObstacleManager(Grid& grid, std::mt19937& rng, float periodSpawn, const FrameTimer& frameTimer)
	: m_grid(grid)
	, m_rng(rng)
	, m_frameTimer(frameTimer)
	, m_row(Wall::s_length, grid.s_lenRow - Wall::s_length - 1)
	, m_col(Wall::s_length, grid.s_lenCol - Wall::s_length - 1)
	, m_periodSpawn(periodSpawn)
{}

void ObstacleManager::DrawObstacles() const
{
	for (const Obstacle& o : m_obstacles)
	{
		o.Draw(m_grid);
	}
}

void ObstacleManager::SpawnObstacle()
{
	if (!CanSpawn())
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

bool ObstacleManager::CanSpawn()
{
	if (m_sumDeltaTime < m_periodSpawn)
	{
		m_sumDeltaTime += m_frameTimer.GetSecondsDeltaTime();
		return false;
	}

	m_sumDeltaTime = 0.0f;

	return true;
}
