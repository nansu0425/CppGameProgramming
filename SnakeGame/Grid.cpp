#include "Grid.h"
#include "Wall.h"

#include <cassert>

PosGrid PosGrid::operator+(const PosGrid& other) const
{
	return {row + other.row, col + other.col};
}

void Grid::Cell::Draw(Graphics& gfx) const
{
	for (int dx = Grid::s_lenBorderLine; dx < lenSide - Grid::s_lenBorderLine; ++dx)
	{
		for (int dy = Grid::s_lenBorderLine; dy < lenSide - Grid::s_lenBorderLine; ++dy)
		{
			gfx.PutPixel(x + dx, y + dy, color);
		}
	}
}

void Grid::Cell::DrawTopWall(Graphics& gfx, bool isCorner) const
{
	for (int dx = 0; dx < ((isCorner) ? Wall::s_thickness : lenSide); ++dx)
	{
		for (int dy = lenSide - 1; dy > lenSide - 1 - Wall::s_thickness; --dy)
		{
			gfx.PutPixel(x + dx, y + dy, color);
		}
	}
}

void Grid::Cell::DrawRightWall(Graphics& gfx, bool isCorner) const
{
	for (int dx = 0; dx < Wall::s_thickness; ++dx)
	{
		for (int dy = 0; dy < ((isCorner) ? Wall::s_thickness : lenSide); ++dy)
		{
			gfx.PutPixel(x + dx, y + dy, color);
		}
	}
}

void Grid::Cell::DrawBottomWall(Graphics& gfx, bool isCorner) const
{
	for (int dx = ((isCorner) ? lenSide - Wall::s_thickness : 0); dx < lenSide; ++dx)
	{
		for (int dy = 0; dy < Wall::s_thickness; ++dy)
		{
			gfx.PutPixel(x + dx, y + dy, color);
		}
	}
}

void Grid::Cell::DrawLeftWall(Graphics& gfx, bool isCorner) const
{
	for (int dx = lenSide - 1; dx > lenSide - 1 - Wall::s_thickness; --dx)
	{
		for (int dy = ((isCorner) ? lenSide - Wall::s_thickness : 0); dy < lenSide; ++dy)
		{
			gfx.PutPixel(x + dx, y + dy, color);
		}
	}
}

Grid::Grid(Graphics& gfx)
	: m_cells(s_lenRow, std::vector<Cell>(s_lenCol))
	, m_gfx(gfx)
{
	for (int row = 0; row < s_lenRow; ++row)
	{
		for (int col = 0; col < s_lenCol; ++col)
		{
			m_cells[row][col] = {col * Cell::lenSide, row * Cell::lenSide};
		}
	}
}

void Grid::Draw(const PosGrid& pos) const
{
	if (m_cells[pos.row][pos.col].occupied == ObjectType::WALL)
	{
		DrawWall(pos);
		return;
	}

	m_cells[pos.row][pos.col].Draw(m_gfx);
}

void Grid::DrawWall(const PosGrid& pos) const
{
	// top
	if (!Wall::isLeft(pos) && Wall::isTop(pos))
	{
		m_cells[pos.row][pos.col].DrawTopWall(m_gfx, Wall::isRight(pos));
		return;
	}

	// right
	if (!Wall::isTop(pos) && Wall::isRight(pos))
	{
		m_cells[pos.row][pos.col].DrawRightWall(m_gfx, Wall::isBottom(pos));
		return;
	}

	// bottom
	if (!Wall::isRight(pos) && Wall::isBottom(pos))
	{
		m_cells[pos.row][pos.col].DrawBottomWall(m_gfx, Wall::isLeft(pos));
		return;
	}

	// left
	if (!Wall::isBottom(pos) && Wall::isLeft(pos))
	{
		m_cells[pos.row][pos.col].DrawLeftWall(m_gfx, Wall::isTop(pos));
		return;
	}
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
	assert((0 <= pos.row) && (pos.row < s_lenRow));
	assert((0 <= pos.col) && (pos.col < s_lenCol));

	m_cells[pos.row][pos.col].color = color;
}

ObjectType Grid::GetTypeOccupied(const PosGrid& pos) const
{
	return m_cells[pos.row][pos.col].occupied;
}

void Grid::SetTypeOccupied(const PosGrid& pos, ObjectType type)
{
	m_cells[pos.row][pos.col].occupied = type;
}
