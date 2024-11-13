#pragma once

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

	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed,
		};

		void				OnDraw(const Vei2& posGrid, Graphics& gfx) const;

		void				SpawnMine();
		bool				HasMine() const;
		void				Reveal();
		bool				IsRevealed() const;
		bool				IsHidden() const;

	private:
		State				m_state = State::Hidden;
		bool				m_hasMine = false;
		
	};

	using					ArrayTile = std::array<std::array<Tile, s_width>, s_height>;

public:
							Field();

	void					OnDraw(Graphics& gfx) const;
	void					OnUpdate(MainWindow& wnd);
	void					OnClick(const Vei2& posGrid);

	Tile&					At(const Vei2& posGrid);
	const Tile&				At(const Vei2& posGrid) const;

private:
	void					DrawBackground(Graphics& gfx) const;
	Vei2					ConvertToPosGrid(const Vei2& pos) const;

private:
	ArrayTile				m_grid;
};
