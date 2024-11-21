#include "Field.h"
#include "Vei2.h"
#include "RectI.h"
#include "MainWindow.h"
#include "GameStateManager.h"

#include <cassert>
#include <random>
#include <algorithm>

/*-------------*
 *    Field    *
 *-------------*/

Field::Field(Size size)
	: m_size(size)
{
	// size 값에 따라 지뢰 개수, 너비, 높이 설정
	switch (size)
	{
	case Size::Small:
		m_numMines = 5;
		m_width = 11;
		m_height = 7;

		break;

	case Size::Medium:
		m_numMines = 20;
		m_width = 21;
		m_height = 15;

		break;

	case Size::Large:
		m_numMines = 80;
		m_width = 31;
		m_height = 23;

		break;
	
	default:
		assert(true);

		break;
	}

	assert((0 <= m_numMines) && 
		   (m_numMines <= m_width * m_height));

	// 보드를 나타내는 사각형의 크기, 위치 설정
	m_rectGrid = RectI(0, m_width - 1, 0, m_height - 1);
	m_posScreen = Vei2((Graphics::ScreenWidth - m_width * SpriteCodex::tileSize) / 2,
					   (Graphics::ScreenHeight - m_height * SpriteCodex::tileSize) / 2);

	// create tiles
	m_board = new Tile*[m_height];
	
	for (int row = 0; row < m_height; ++row)
	{
		m_board[row] = new Tile[m_width];
	}

	m_numUnrevealedTiles = m_width * m_height;

	// spawn mines
	std::random_device rd;
	std::mt19937 rng(rd());

	std::uniform_int_distribution<int> distX(0, m_width - 1);
	std::uniform_int_distribution<int> distY(0, m_height - 1);
	
	for (int count = 0; count < m_numMines; ++count)
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
	for (Vei2 posBoard = Vei2(0, 0); posBoard.y < m_height; ++posBoard.y)
	{
		for (posBoard.x = 0; posBoard.x < m_width; ++posBoard.x)
		{
			At(posBoard).SetNumNeighborMines(CountNeighborMines(posBoard));
		}
	}
}

Field::~Field()
{
	if (m_board != nullptr)
	{
		for (int row = 0; row < m_height; ++row)
		{
			if (m_board[row] != nullptr)
			{
				delete[] m_board[row];
			}
		}

		delete[] m_board;
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

void Field::Tile::SetNumNeighborMines(int numNeighborMines)
{
	assert((-1 <= numNeighborMines) &&
		   (numNeighborMines <= 8));

	m_numNeighborMines = numNeighborMines;
}

bool Field::Tile::HasNoNeighborMines() const
{
	return (m_numNeighborMines == 0);
}

void Field::Tile::OnDraw(const Vei2& posScreen, Graphics& gfx, const GameStateManager& gameStateManager) const
{
	switch (m_state)
	{
	case State::Hidden:
		if (gameStateManager.IsGameOver() &&
			HasMine())
		{
			SpriteCodex::DrawTileBomb(posScreen, gfx);
		}
		else
		{
			SpriteCodex::DrawTileButton(posScreen, gfx);
		}
		break;

	case State::Flagged:
		if (gameStateManager.IsGameOver())
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
			SpriteCodex::DrawTileNumber(m_numNeighborMines, posScreen, gfx);
		}
		break;

	default:
		assert(true);
		break;
	}
}

void Field::OnDraw(Graphics& gfx, const GameStateManager& stateManager) const
{
	DrawBackground(gfx);

	for (Vei2 posBoard = Vei2(0, 0); posBoard.y < m_height; ++posBoard.y)
	{
		for (posBoard.x = 0; posBoard.x < m_width; ++posBoard.x)
		{
			At(posBoard).OnDraw(ConvertToScreen(posBoard), gfx, stateManager);
		}
	}
}

void Field::OnUpdate(MainWindow& wnd, GameStateManager& gameStateManager)
{
	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event evt = wnd.mouse.Read();

		switch (evt.GetType())
		{
		case Mouse::Event::Type::LPress:
			if (IsOnField(evt.GetPos()))
			{
				OnLeftClickMouse(ConvertToGrid(evt.GetPos()), gameStateManager);
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

void Field::OnLeftClickMouse(const Vei2& posBoard, GameStateManager& gameStateManager)
{
	if (At(posBoard).IsHidden())
	{
		RevealTileAt(posBoard);

		// 게임 패배
		if (At(posBoard).HasMine())
		{
			gameStateManager.SetGameOver(false);
		}
		// 게임 승리
		else if (m_numUnrevealedTiles == m_numMines)
		{
			gameStateManager.SetGameOver(true);
		}
	}
}

void Field::OnRightClickMouse(const Vei2& posBoard)
{
	if (!At(posBoard).IsRevealed())
	{
		At(posBoard).ToggleFlag();
	}
}

Field::Tile& Field::At(const Vei2& posBoard)
{
	assert((0 <= posBoard.x) && (posBoard.x < m_width));
	assert((0 <= posBoard.y) && (posBoard.y < m_height));

	return m_board[posBoard.y][posBoard.x];
}

const Field::Tile& Field::At(const Vei2& posBoard) const
{
	assert((0 <= posBoard.x) && (posBoard.x < m_width));
	assert((0 <= posBoard.y) && (posBoard.y < m_height));

	return m_board[posBoard.y][posBoard.x];
}

int Field::CountNeighborMines(const Vei2& posBoard)
{
	int count = 0;

	if (At(posBoard).HasMine())
	{
		--count;

		return count;
	}

	const int xStart = std::max(0, posBoard.x - 1);
	const int xEnd = std::min(m_width - 1, posBoard.x + 1);
	const int yStart = std::max(0, posBoard.y - 1);
	const int yEnd = std::min(m_height - 1, posBoard.y + 1);

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
			(posScreen.x < m_posScreen.x + m_width * SpriteCodex::tileSize) &&
			(m_posScreen.y <= posScreen.y) &&
			(posScreen.y < m_posScreen.y + m_height * SpriteCodex::tileSize));
}

void Field::RevealTileAt(const Vei2& posBoard)
{
	At(posBoard).Reveal();
	--m_numUnrevealedTiles;

	if (!At(posBoard).HasMine() &&
		At(posBoard).HasNoNeighborMines())
	{
		RevealNeighborTilesAt(posBoard);
	}
}

void Field::RevealNeighborTilesAt(const Vei2& posBoard)
{
	assert(!At(posBoard).HasMine());

	const int xStart = std::max(0, posBoard.x - 1);
	const int xEnd = std::min(m_width - 1, posBoard.x + 1);
	const int yStart = std::max(0, posBoard.y - 1);
	const int yEnd = std::min(m_height - 1, posBoard.y + 1);

	for (Vei2 posNeighbor = Vei2(xStart, yStart); posNeighbor.y <= yEnd; ++posNeighbor.y)
	{
		for (posNeighbor.x = xStart; posNeighbor.x <= xEnd; ++posNeighbor.x)
		{
			if (At(posNeighbor).IsHidden())
			{
				RevealTileAt(posNeighbor);
			}
		}
	}
}

void Field::DrawBackground(Graphics& gfx) const
{
	const RectI rectScreen = RectI(m_posScreen,
								   Vei2(m_posScreen.x + (m_rectGrid.right + 1) * SpriteCodex::tileSize,
										m_posScreen.y + (m_rectGrid.bottom + 1) * SpriteCodex::tileSize));

	assert((m_posScreen.x <= rectScreen.left) &&
		   (m_posScreen.y <= rectScreen.top) &&
		   (m_posScreen.x <= m_posScreen.x + (m_width + 1) * SpriteCodex::tileSize) &&
		   (m_posScreen.y <= m_posScreen.y + (m_height + 1) * SpriteCodex::tileSize));

	gfx.DrawRect(rectScreen, SpriteCodex::baseColor);
	DrawBorder(rectScreen, gfx);
}

void Field::DrawBorder(const RectI& rectScreen, Graphics& gfx) const
{
	// top border
	gfx.DrawRect(RectI(Vei2(rectScreen.left, rectScreen.top - s_thicknessBorder),
					   Vei2(rectScreen.right + s_thicknessBorder - 1, rectScreen.top)),
				 s_colorBorder);

	// right border
	gfx.DrawRect(RectI(Vei2(rectScreen.right, rectScreen.top),
					   Vei2(rectScreen.right + s_thicknessBorder - 1, rectScreen.bottom + s_thicknessBorder - 1)),
				 s_colorBorder);

	// bottom border
	gfx.DrawRect(RectI(Vei2(rectScreen.left - s_thicknessBorder, rectScreen.bottom),
					   Vei2(rectScreen.right, rectScreen.bottom + s_thicknessBorder - 1)),
				 s_colorBorder);

	// left border
	gfx.DrawRect(RectI(Vei2(rectScreen.left - s_thicknessBorder, rectScreen.top - s_thicknessBorder),
					   Vei2(rectScreen.left, rectScreen.bottom)),
				 s_colorBorder);
}

Vei2 Field::ConvertToGrid(const Vei2& vecScreen) const
{
	const Vei2 vecGrid = (vecScreen - m_posScreen) / SpriteCodex::tileSize;

	assert((0 <= vecGrid.x) &&
		   (vecGrid.x < m_width));
	assert((0 <= vecGrid.y) &&
		   (vecGrid.y < m_height));

	return vecGrid;
}

Vei2 Field::ConvertToScreen(const Vei2& vecGrid) const
{
	const Vei2 vecScreen = m_posScreen + vecGrid * SpriteCodex::tileSize;

	assert((m_posScreen.x <= vecScreen.x) &&
		   (vecScreen.x < m_posScreen.x + m_width * SpriteCodex::tileSize));
	assert((m_posScreen.y <= vecScreen.y) &&
		   (vecScreen.y < m_posScreen.y + m_height * SpriteCodex::tileSize));

	return vecScreen;
}
