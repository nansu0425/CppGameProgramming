#include "Field.h"
#include "Vei2.h"
#include "RectI.h"
#include "MainWindow.h"

#include <cassert>
#include <random>

/*-------------*
 *    Field    *
 *-------------*/

Field::Field()
{
	assert((0 <= s_nMines) && (s_nMines <= s_width * s_height));

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

void Field::Tile::OnDraw(const Vei2& posGrid, Graphics& gfx) const
{
	const Vei2 posScreen = posGrid * SpriteCodex::tileSize;

	assert((0 <= posScreen.x) && (posScreen.x < Graphics::ScreenWidth));
	assert((0 <= posScreen.y) && (posScreen.y < Graphics::ScreenHeight));

	switch (m_state)
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton(posScreen, gfx);
		break;

	case State::Flagged:
		SpriteCodex::DrawTileButton(posScreen, gfx);
		SpriteCodex::DrawTileFlag(posScreen, gfx);
		break;

	case State::Revealed:
		if (HasMine())
		{
			SpriteCodex::DrawTileBomb(posScreen, gfx);
		}
		else
		{
			SpriteCodex::DrawTile0(posScreen, gfx);
		}
		break;

	default:
		assert(true);
		break;
	}
}

void Field::OnDraw(Graphics& gfx) const
{
	DrawBackground(gfx);

	for (Vei2 posGrid = Vei2(0, 0); posGrid.y < s_height; ++posGrid.y)
	{
		for (posGrid.x = 0; posGrid.x < s_width; ++posGrid.x)
		{
			At(posGrid).OnDraw(posGrid, gfx);
		}
	}
}

void Field::OnUpdate(MainWindow& wnd)
{
	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event evt = wnd.mouse.Read();

		switch (evt.GetType())
		{
		case Mouse::Event::Type::LPress:
			if (s_rect.Contains(evt.GetPos()))
			{
				OnLeftClickMouse(ConvertToPosGrid(evt.GetPos()));
			}
			break;

		case Mouse::Event::Type::RPress:
			if (s_rect.Contains(evt.GetPos()))
			{
				OnRightClickMouse(ConvertToPosGrid(evt.GetPos()));
			}
			break;

		default:
			break;
		}
	}
}

void Field::OnLeftClickMouse(const Vei2& posGrid)
{
	if (At(posGrid).IsHidden())
	{
		At(posGrid).Reveal();
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

void Field::DrawBackground(Graphics& gfx) const
{
	gfx.DrawRect(s_rect, SpriteCodex::baseColor);
}

Vei2 Field::ConvertToPosGrid(const Vei2& pos) const
{
	return pos / SpriteCodex::tileSize;
}
