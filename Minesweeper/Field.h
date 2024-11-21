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
public:
	enum class Size
	{
		Small,
		Medium,
		Large,
	};

private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed,
		};

		void				OnDraw(const Vei2& posBoard, Graphics& gfx, const GameStateManager& gameStateManager) const;

		void				SpawnMine();
		bool				HasMine() const;
		void				Reveal();
		bool				IsRevealed() const;
		bool				IsHidden() const;
		void				ToggleFlag();
		void				SetNumNeighborMines(int numNeighborMines);
		bool				HasNoNeighborMines() const;

	private:
		State				m_state = State::Hidden;
		bool				m_hasMine = false;
		int					m_numNeighborMines = -1;
		
	};

public:
							Field(Size size);
							~Field();

	void					OnDraw(Graphics& gfx, const GameStateManager& gameStateManager) const;
	void					OnUpdate(MainWindow& wnd, GameStateManager& gameStateManager);

private:
	void					OnLeftClickMouse(const Vei2& posBoard, GameStateManager& stateManager);
	void					OnRightClickMouse(const Vei2& posBoard);

	void					DrawBackground(Graphics& gfx) const;
	void					DrawBorder(const RectI& rectScreen, Graphics& gfx) const;
	Vei2					ConvertToGrid(const Vei2& vecScreen) const;
	Vei2					ConvertToScreen(const Vei2& vecGrid) const;
	Tile&					At(const Vei2& posBoard);
	const					Tile& At(const Vei2& posBoard) const;
	int						CountNeighborMines(const Vei2& posBoard);
	bool					IsOnField(const Vei2 posScreen) const;
	void					RevealTileAt(const Vei2& posBoard);
	void					RevealNeighborTilesAt(const Vei2& posBoard);

private:
	static constexpr int	s_thicknessBorder = 10;
	static constexpr Color	s_colorBorder = Colors::Blue;

	Size					m_size;
	int						m_numMines = -1;
	int						m_width = -1;
	int						m_height = -1;
	RectI					m_rectGrid;  
	Vei2					m_posScreen;
	Tile**					m_board = nullptr;
	int						m_numUnrevealedTiles = -1;
};
