#include "Grid.h"

#include <cassert>

PosGrid PosGrid::operator+(const PosGrid& other) const
{
	return {row + other.row, col + other.col};
}

void Grid::Cell::Draw(Graphics& gfx) const
{
	for (int dx = 0; dx < lenSide; ++dx)
	{
		for (int dy = 0; dy < lenSide; ++dy)
		{
			gfx.PutPixel(x + dx, y + dy, color);
		}
	}
}

Grid::Grid(Graphics& gfx)
	: m_cells(m_lenRow, std::vector<Cell>(m_lenCol))
	, m_gfx(gfx)
{
	for (int row = 0; row < m_lenRow; ++row)
	{
		for (int col = 0; col < m_lenCol; ++col)
		{
			m_cells[row][col] = {col * Cell::lenSide, row * Cell::lenSide};
		}
	}
}

void Grid::Draw(const PosGrid& pos) const
{
	m_cells[pos.row][pos.col].Draw(m_gfx);
}

void Grid::DrawCells() const
{
	for (const std::vector<Cell>& cellsRow : m_cells)
	{
		for (const Cell& cell : cellsRow)
		{
			cell.Draw(m_gfx);
		}
	}
}

void Grid::SetColorCell(const PosGrid& pos, Color color)
{
	assert((0 <= pos.row) && (pos.row < m_lenRow));
	assert((0 <= pos.col) && (pos.col < m_lenCol));

	m_cells[pos.row][pos.col].color = color;
}

bool Grid::IsCellOccupied(const PosGrid& pos) const
{
	return m_cells[pos.row][pos.col].isOccupied;
}

void Grid::SetCellIsOccupied(const PosGrid& pos, bool isOccupied)
{
	m_cells[pos.row][pos.col].isOccupied = isOccupied;
}
