#pragma once

#include "Grid.h"
#include "Colors.h"

#include <unordered_map>
#include <random>

class Food
{
public:
	Food(Grid& grid, const PosGrid& pos);

	void	Draw(const Grid& grid) const;

public:
	static constexpr Color		s_color = Colors::Red;

private:
	PosGrid		m_pos;
};

class FoodManager
{
private:
	using MapFoods		= std::unordered_map<int, Food>;
	using UniformDist	= std::uniform_int_distribution<>;
	using RandNumGen	= std::mt19937;

public:
	FoodManager(Grid& grid, std::mt19937& rng, int periodSpawn)
		: m_grid(grid)
		, m_rng(rng)
		, m_row(0, grid.m_lenRow - 1)
		, m_col(0, grid.m_lenCol - 1)
		, m_periodSpawn(periodSpawn)
	{}

	void	DrawFoods() const;
	void	SpawnFood();
	void	EatFood(const PosGrid& pos);

private:
	bool	IsCountSpawn();
	int		ConvertKey(const PosGrid& pos) { return 10 * pos.row + pos.col; }

public:
	MapFoods		m_foods;
	Grid&			m_grid;
	RandNumGen&		m_rng;
	UniformDist		m_row;
	UniformDist		m_col;
	int				m_periodSpawn;
	int				m_counterSpawn = 0;
};
