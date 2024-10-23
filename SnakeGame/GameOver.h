#pragma once

class Graphics;

class GameOver
{
public:
	GameOver(int x, int y)
		: m_x(x)
		, m_y(y)
	{}

	void	Draw(Graphics& gfx) const;

	bool	IsOver() const { return m_isOver; }
	void	SetOver() { m_isOver = true; }

public:
	static constexpr int	s_width = 86;
	static constexpr int	s_height = 64;

private:
	int		m_x;
	int		m_y;
	bool	m_isOver = false;
};
