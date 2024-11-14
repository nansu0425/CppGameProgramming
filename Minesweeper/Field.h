#pragma once

#include "RectI.h"
#include "SpriteCodex.h"
#include "Graphics.h"

#include <array>

class Vei2;
class MainWindow;

/*-------------*
 *    Field    *
 *-------------*/

class Field
{
private:
	static constexpr int	s_nMines = 12;
	static constexpr int	s_width = 13;
	static constexpr int	s_height = 9;
	static constexpr RectI	s_rectGrid = RectI(0, s_width - 1, 0, s_height - 1);

	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed,
		};

		void				OnDraw(const Vei2& posGrid, Graphics& gfx, const bool& isOver) const;

		void				SpawnMine();
		bool				HasMine() const;
		void				Reveal();
		bool				IsRevealed() const;
		bool				IsHidden() const;
		void				ToggleFlag();
		void				SetNumNeighborMines(int nNeighborMines);

	private:
		State				m_state = State::Hidden;
		bool				m_hasMine = false;
		int					m_nNeighborMines = -1;
		
	};

	using					ArrayTile = std::array<std::array<Tile, s_width>, s_height>;

public:
							Field();

	void					OnDraw(Graphics& gfx, const bool& isOver) const;
	void					OnUpdate(MainWindow& wnd, bool& isOver);

private:
	void					OnLeftClickMouse(const Vei2& posGrid, bool& isOver);
	void					OnRightClickMouse(const Vei2& posGrid);

	void					DrawBackground(Graphics& gfx) const;
	Vei2					ConvertToGrid(const Vei2& vecScreen) const;
	Vei2					ConvertToScreen(const Vei2& vecGrid) const;
	Tile&					At(const Vei2& posGrid);
	const					Tile& At(const Vei2& posGrid) const;
	int						CountNeighborMines(const Vei2& posGrid);
	bool					IsOnField(const Vei2 posScreen) const;

private:
	ArrayTile				m_grid;
	Vei2					m_posScreen;
};
