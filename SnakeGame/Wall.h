#pragma once

#include "Grid.h"

#include <vector>

class Wall
{
private:
	using Vector	= std::vector<PosGrid>;

public:
	Wall(Grid& grid);

	void		Draw() const;

	static bool		isTop(const PosGrid& pos) { return (pos.row == Wall::s_length); }
	static bool		isRight(const PosGrid& pos) { return (pos.col == Grid::s_lenCol - Wall::s_length - 1); }
	static bool		isBottom(const PosGrid& pos) { return (pos.row == Grid::s_lenRow - Wall::s_length - 1); }
	static bool		isLeft(const PosGrid& pos) { return (pos.col == Wall::s_length); }

public:
	static constexpr int	s_length = 2;
	static constexpr int	s_thickness = 3;

private:
	Grid&		m_grid;
	Vector		m_vecPos;
};
