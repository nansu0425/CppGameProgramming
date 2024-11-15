#pragma once

#include "RectI.h"
#include "SpriteCodex.h"
#include "Colors.h"

#include <array>

class Vei2;
class MainWindow;
class Graphics;
class GameStateManager;

/*-------------*
 *    Field    *
 *-------------*/

class Field
{
private:
	static constexpr int	s_nMines = 10;
	static constexpr int	s_width = 13;
	static constexpr int	s_height = 7;
	static constexpr RectI	s_rectGrid = RectI(0, s_width - 1, 0, s_height - 1);
	static constexpr int	s_thicknessBorder = 10;
	static constexpr Color	s_colorBorder = Colors::Blue;

	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed,
		};

		void				OnDraw(const Vei2& posGrid, Graphics& gfx, const GameStateManager& gameStateManager) const;

		void				SpawnMine();
		bool				HasMine() const;
		void				Reveal();
		bool				IsRevealed() const;
		bool				IsHidden() const;
		void				ToggleFlag();
		void				SetNumNeighborMines(int nNeighborMines);
		bool				HasNoNeighborMines() const;

	private:
		State				m_state = State::Hidden;
		bool				m_hasMine = false;
		int					m_nNeighborMines = -1;
		
	};

	using					ArrayTile = std::array<std::array<Tile, s_width>, s_height>;

public:
							Field();

	void					OnDraw(Graphics& gfx, const GameStateManager& gameStateManager) const;
	void					OnUpdate(MainWindow& wnd, GameStateManager& gameStateManager);

private:
	void					OnLeftClickMouse(const Vei2& posGrid, GameStateManager& stateManager);
	void					OnRightClickMouse(const Vei2& posGrid);

	void					DrawBackground(Graphics& gfx) const;
	void					DrawBorder(const RectI& rectScreen, Graphics& gfx) const;
	Vei2					ConvertToGrid(const Vei2& vecScreen) const;
	Vei2					ConvertToScreen(const Vei2& vecGrid) const;
	Tile&					At(const Vei2& posGrid);
	const					Tile& At(const Vei2& posGrid) const;
	int						CountNeighborMines(const Vei2& posGrid);
	bool					IsOnField(const Vei2 posScreen) const;
	void					RevealTileAt(const Vei2& posGrid);
	void					RevealNeighborTilesAt(const Vei2& posGrid);

private:
	ArrayTile				m_grid;
	Vei2					m_posScreen;
	int						m_nUnrevealedTiles = s_width * s_height;
};
