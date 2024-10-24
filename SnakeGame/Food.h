#pragma once

#include "Grid.h"
#include "Colors.h"

#include <unordered_map>
#include <random>

class Food
{
private:
	using UniformDist	= std::uniform_int_distribution<>;
	using RandNumGen	= std::mt19937;

public:
	Food(Grid& grid, std::mt19937& rng);

	void	Draw() const;
	void	Respawn();

private:
	void	Spawn();

public:
	static constexpr Color		s_color = Colors::Red;

private:
	Grid&			m_grid;
	RandNumGen&		m_rng;
	UniformDist		m_row;
	UniformDist		m_col;
	PosGrid			m_pos;
};
