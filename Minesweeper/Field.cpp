﻿#include "Field.h"
#include "Vei2.h"
#include "RectI.h"
#include "MainWindow.h"

#include <cassert>
#include <random>
#include <algorithm>

/*-------------*
 *    Field    *
 *-------------*/

Field::Field()
	: m_posScreen((Graphics::ScreenWidth - s_width * SpriteCodex::tileSize) / 2,
				  (Graphics::ScreenHeight - s_height * SpriteCodex::tileSize) / 2)
{
	assert((0 <= s_nMines) && (s_nMines <= s_width * s_height));

	// spawn mines
	std::random_device rd;
	std::mt19937 rng(rd());

	std::uniform_int_distribution<int> distX(0, s_width - 1);
	std::uniform_int_distribution<int> distY(0, s_height - 1);
	
	for (int count = 0; count < s_nMines; ++count)
	{
		while (true)
		{
			const Vei2 pos = Vei2(distX(rng), distY(rng));

			if (!At(pos).HasMine())
			{
				At(pos).SpawnMine();
				break;
			}
		}
	}

	// Set the number of neighbor mines
	for (Vei2 posGrid = Vei2(0, 0); posGrid.y < s_height; ++posGrid.y)
	{
		for (posGrid.x = 0; posGrid.x < s_width; ++posGrid.x)
		{
			At(posGrid).SetNumNeighborMines(CountNeighborMines(posGrid));
		}
	}
}

void Field::Tile::SpawnMine()
{
	assert(!m_hasMine);

	m_hasMine = true;
}

bool Field::Tile::HasMine() const
{
	return m_hasMine;
}

void Field::Tile::Reveal()
{
	assert(m_state == State::Hidden);

	m_state = State::Revealed;
}

bool Field::Tile::IsRevealed() const
{
	return (m_state == State::Revealed);
}

bool Field::Tile::IsHidden() const
{
	return (m_state == State::Hidden);
}

void Field::Tile::ToggleFlag()
{
	switch (m_state)
	{
	case State::Hidden:
		m_state = State::Flagged;
		break;

	case State::Flagged:
		m_state = State::Hidden;
		break;

	default:
		assert(true);
		break;
	}
}

void Field::Tile::SetNumNeighborMines(int nNeighborMines)
{
	assert((-1 <= nNeighborMines) &&
		   (nNeighborMines <= 8));

	m_nNeighborMines = nNeighborMines;
}

void Field::Tile::OnDraw(const Vei2& posScreen, Graphics& gfx, const bool& isOver) const
{
	switch (m_state)
	{
	case State::Hidden:
		if (isOver && HasMine())
		{
			SpriteCodex::DrawTileBomb(posScreen, gfx);
		}
		else
		{
			SpriteCodex::DrawTileButton(posScreen, gfx);
		}
		break;

	case State::Flagged:
		if (isOver)
		{
			SpriteCodex::DrawTileBomb(posScreen, gfx);

			if (HasMine())
			{
				SpriteCodex::DrawTileFlag(posScreen, gfx);
			}
			else
			{
				SpriteCodex::DrawTileCross(posScreen, gfx);
			}
		}
		else
		{
			SpriteCodex::DrawTileButton(posScreen, gfx);
			SpriteCodex::DrawTileFlag(posScreen, gfx);
		}
		break;

	case State::Revealed:
		if (HasMine())
		{
			SpriteCodex::DrawTileBombRed(posScreen, gfx);
		}
		else
		{
			SpriteCodex::DrawTileNumber(m_nNeighborMines, posScreen, gfx);
		}
		break;

	default:
		assert(true);
		break;
	}
}

void Field::OnDraw(Graphics& gfx, const bool& isOver) const
{
	DrawBackground(gfx);

	for (Vei2 posGrid = Vei2(0, 0); posGrid.y < s_height; ++posGrid.y)
	{
		for (posGrid.x = 0; posGrid.x < s_width; ++posGrid.x)
		{
			At(posGrid).OnDraw(ConvertToScreen(posGrid), gfx, isOver);
		}
	}
}

void Field::OnUpdate(MainWindow& wnd, bool& isOver)
{
	if (isOver)
	{
		return;
	}

	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event evt = wnd.mouse.Read();

		switch (evt.GetType())
		{
		case Mouse::Event::Type::LPress:
			if (IsOnField(evt.GetPos()))
			{
				OnLeftClickMouse(ConvertToGrid(evt.GetPos()), isOver);
			}
			break;

		case Mouse::Event::Type::RPress:
			if (IsOnField(evt.GetPos()))
			{
				OnRightClickMouse(ConvertToGrid(evt.GetPos()));
			}
			break;

		default:
			break;
		}
	}
}

void Field::OnLeftClickMouse(const Vei2& posGrid, bool& isOver)
{
	if (At(posGrid).IsHidden())
	{
		At(posGrid).Reveal();

		if (At(posGrid).HasMine())
		{
			isOver = true;
		}
	}
}

void Field::OnRightClickMouse(const Vei2& posGrid)
{
	if (!At(posGrid).IsRevealed())
	{
		At(posGrid).ToggleFlag();
	}
}

Field::Tile& Field::At(const Vei2& posGrid)
{
	assert((0 <= posGrid.x) && (posGrid.x < s_width));
	assert((0 <= posGrid.y) && (posGrid.y < s_height));

	return m_grid[posGrid.y][posGrid.x];
}

const Field::Tile& Field::At(const Vei2& posGrid) const
{
	assert((0 <= posGrid.x) && (posGrid.x < s_width));
	assert((0 <= posGrid.y) && (posGrid.y < s_height));

	return m_grid[posGrid.y][posGrid.x];
}

int Field::CountNeighborMines(const Vei2& posGrid)
{
	int count = 0;

	if (At(posGrid).HasMine())
	{
		--count;

		return count;
	}

	const int xStart = std::max(0, posGrid.x - 1);
	const int xEnd = std::min(s_width - 1, posGrid.x + 1);
	const int yStart = std::max(0, posGrid.y - 1);
	const int yEnd = std::min(s_height - 1, posGrid.y + 1);

	for (Vei2 posNeighbor = Vei2(xStart, yStart); posNeighbor.y <= yEnd; ++posNeighbor.y)
	{
		for (posNeighbor.x = xStart; posNeighbor.x <= xEnd; ++posNeighbor.x)
		{
			if (At(posNeighbor).HasMine())
			{
				++count;
			}
		}
	}

	return count;
}

bool Field::IsOnField(const Vei2 posScreen) const
{
	return ((m_posScreen.x <= posScreen.x) &&
			(posScreen.x < m_posScreen.x + s_width * SpriteCodex::tileSize) &&
			(m_posScreen.y <= posScreen.y) &&
			(posScreen.y < m_posScreen.y + s_height * SpriteCodex::tileSize));
}

void Field::DrawBackground(Graphics& gfx) const
{
	const RectI rectScreen = RectI(m_posScreen,
								   Vei2(m_posScreen.x + (s_rectGrid.right + 1) * SpriteCodex::tileSize,
										m_posScreen.y + (s_rectGrid.bottom + 1) * SpriteCodex::tileSize));

	assert((m_posScreen.x <= rectScreen.left) &&
		   (m_posScreen.y <= rectScreen.top) &&
		   (m_posScreen.x <= m_posScreen.x + (s_width + 1) * SpriteCodex::tileSize) &&
		   (m_posScreen.y <= m_posScreen.y + (s_height + 1) * SpriteCodex::tileSize));


	gfx.DrawRect(rectScreen, SpriteCodex::baseColor);
}

Vei2 Field::ConvertToGrid(const Vei2& vecScreen) const
{
	const Vei2 vecGrid = (vecScreen - m_posScreen) / SpriteCodex::tileSize;

	assert((0 <= vecGrid.x) &&
		   (vecGrid.x < s_width));
	assert((0 <= vecGrid.y) &&
		   (vecGrid.y < s_height));

	return vecGrid;
}

Vei2 Field::ConvertToScreen(const Vei2& vecGrid) const
{
	const Vei2 vecScreen = m_posScreen + vecGrid * SpriteCodex::tileSize;

	assert((m_posScreen.x <= vecScreen.x) &&
		   (vecScreen.x < m_posScreen.x + s_width * SpriteCodex::tileSize));
	assert((m_posScreen.y <= vecScreen.y) &&
		   (vecScreen.y < m_posScreen.y + s_height * SpriteCodex::tileSize));

	return vecScreen;
}
