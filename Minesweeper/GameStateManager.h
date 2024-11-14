#pragma once

class Graphics;

class GameStateManager
{
private:
	enum class PlayerState
	{
		none,
		winner,
		loser,
	};

public:
	void			DrawOnGameOver(Graphics& gfx) const;
	bool			IsGameOver() const;
	void			SetGameOver(bool isWinner);
	bool			IsWinner() const;
	bool			IsLoser() const;

private:
	PlayerState		m_playerState = PlayerState::none;
	bool			m_isGameOver = false;
	
};
