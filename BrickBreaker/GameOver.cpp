#include "GameOver.h"
#include "Graphics.h"
#include "Sprites.h"

namespace BrickBreaker
{
	/*----------------*
	 *    GameOver    *
	 *----------------*/

	void GameOver::Draw(Graphics& gfx)
	{
		Sprites::DrawGameOver(s_position, gfx);
	}
}
