#pragma once

#include "Grid.h"
#include "Colors.h"
#include "Wall.h"

#include <forward_list>
#include <random>

class Obstacle
{
public:
	Obstacle(Grid& grid, const PosGrid& pos);

	void	Draw(const Grid& grid) const;
	
public:
	static constexpr Color		s_color = Colors::Gray;

private:
	PosGrid		m_pos;
};

class ObstacleManager
{
private:
	using ListObstacles		= std::forward_list<Obstacle>;
	using UniformDist		= std::uniform_int_distribution<>;
	using RandNumGen		= std::mt19937;

public:
	ObstacleManager(Grid& grid, std::mt19937& rng, int periodSpawn)
		: m_grid(grid)
		, m_rng(rng)
		, m_row(Wall::s_length, grid.s_lenRow - Wall::s_length - 1)
		, m_col(Wall::s_length, grid.s_lenCol - Wall::s_length - 1)
		, m_periodSpawn(periodSpawn)
	{}

	void	DrawObstacles() const;
	void	SpawnObstacle();

private:
	bool	IsCountSpawn();

private:
	ListObstacles		m_obstacles;
	Grid&				m_grid;
	RandNumGen&			m_rng;
	UniformDist			m_row;
	UniformDist			m_col;
	int					m_periodSpawn;
	int					m_counterSpawn = 0;
};
