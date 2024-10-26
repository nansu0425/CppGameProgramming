#pragma once

#include "Colors.h"
#include "Graphics.h"

#include <vector>

struct PosGrid
{
	int row = 0;
	int col = 0;

	PosGrid		operator+(const PosGrid& other) const;
};

enum class ObjectType
{
	NONE,
	SNAKE,
	FOOD,
	OBSTACLE,
	WALL,
};

class Grid
{
private:
	struct Cell
	{
		int						x = 0;
		int						y = 0;
		Color					color;
		ObjectType				occupied = ObjectType::NONE;
		static constexpr int	lenSide = 20;

		void	Draw(Graphics& gfx) const;
		void	DrawTopWall(Graphics& gfx, bool isCorner) const;
		void	DrawRightWall(Graphics& gfx, bool isCorner) const;
		void	DrawBottomWall(Graphics& gfx, bool isCorner) const;
		void	DrawLeftWall(Graphics& gfx, bool isCorner) const;
	};

public:
	Grid(Graphics& gfx);

	void		Draw(const PosGrid& pos) const;
	void		DrawWall(const PosGrid& pos) const;
	void		DrawCells() const;
	void		SetColorCell(const PosGrid& pos, Color color);
	ObjectType	GetTypeOccupied(const PosGrid& pos) const;
	void		SetTypeOccupied(const PosGrid& pos, ObjectType type);

public:
	static constexpr int			s_lenRow = 30;
	static constexpr int			s_lenCol = 40;
	static constexpr int			s_lenBorderLine = 1;

private:
	std::vector<std::vector<Cell>>	m_cells;
	Graphics&						m_gfx;
};
