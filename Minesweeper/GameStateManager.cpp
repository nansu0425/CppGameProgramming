#include "GameStateManager.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Vei2.h"

#include <cassert>

void GameStateManager::DrawOnGameOver(Graphics& gfx) const
{
	assert(IsGameOver());

	switch (m_playerState)
	{
	case PlayerState::winner:
		SpriteCodex::DrawWin(Vei2(400, 300), gfx);
		break;

	case PlayerState::loser:
		break;

	default:
		assert(true);
		break;
	}
}

bool GameStateManager::IsGameOver() const
{
	return m_isGameOver;
}

void GameStateManager::SetGameOver(bool isWinner)
{
	assert(!m_isGameOver &&
		   (m_playerState == PlayerState::none));

	m_isGameOver = true;

	if (isWinner)
	{
		m_playerState = PlayerState::winner;
	}
	else
	{
		m_playerState = PlayerState::loser;
	}
}

bool GameStateManager::IsWinner() const
{
	return (m_playerState == PlayerState::winner);
}

bool GameStateManager::IsLoser() const
{
	return (m_playerState == PlayerState::loser);
}
