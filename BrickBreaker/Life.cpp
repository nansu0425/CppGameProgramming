#include "Life.h"
#include "Sprites.h"
#include "GameOver.h"

namespace BrickBreaker
{
	/*------------*
	 *    Life    *
	 *------------*/

	void Life::Draw(Graphics& gfx)
	{
		for (int col = 0; col < m_count; ++col)
		{
			Sprites::DrawPoo(s_position + Vector(s_size.x * col, 0.0f), gfx);
		}
	}
}