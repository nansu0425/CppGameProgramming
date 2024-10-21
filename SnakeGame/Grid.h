#pragma once

#include "Colors.h"
#include "Graphics.h"

#include <vector>

class Grid
{
private:
	struct Cell
	{
		int						x = 0;
		int						y = 0;
		Color					color;
		static constexpr int	lenSide = 20;

		void Draw(Graphics& gfx) const;
	};

public:
	Grid(Graphics& gfx);

	void DrawCells() const;
	void SetColorCell(int row, int col, Color color);

public:
	static constexpr int			m_lenRow = 10;
	static constexpr int			m_lenCol = 10;

private:
	std::vector<std::vector<Cell>>	m_cells;
	Graphics&						m_gfx;
};
