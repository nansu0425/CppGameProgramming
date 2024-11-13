#pragma once

#include "RectI.h"
#include "SpriteCodex.h"

#include <array>

class Vei2;
class Graphics;
class MainWindow;

/*-------------*
 *    Field    *
 *-------------*/

class Field
{
private:
	static constexpr int	s_nMines = 20;
	static constexpr int	s_width = 20;
	static constexpr int	s_height = 16;
	static constexpr RectI	s_rect = RectI(0, 
										   s_width * SpriteCodex::tileSize,
										   0, 
										   s_height * SpriteCodex::tileSize);

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
		void				InitNumNeighborMines(int nNeighborMines);

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
	Vei2					ConvertToPosGrid(const Vei2& pos) const;
	Tile&					At(const Vei2& posGrid);
	const					Tile& At(const Vei2& posGrid) const;
	int						CountNeighborMines(const Vei2& posGrid);

private:
	ArrayTile				m_grid;
};
