#pragma once

#include "Grid.h"
#include "Colors.h"
#include "Wall.h"

#include <forward_list>
#include <random>

class FrameTimer;

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
	ObstacleManager(Grid& grid, std::mt19937& rng, float periodSpawn, const FrameTimer& frameTimer);

	void	DrawObstacles() const;
	void	SpawnObstacle();

private:
	bool	CanSpawn();

private:
	ListObstacles		m_obstacles;
	Grid&				m_grid;
	RandNumGen&			m_rng;
	const FrameTimer&	m_frameTimer;
	UniformDist			m_row;
	UniformDist			m_col;
	float				m_periodSpawn;
	float				m_sumDeltaTime = 0.0f;
};
