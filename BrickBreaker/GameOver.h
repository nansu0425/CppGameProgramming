#pragma once

#include "Vector.h"
#include "Graphics.h"

namespace BrickBreaker
{
	/*----------------*
	 *    GameOver    *
	 *----------------*/

	class GameOver
	{
	public:
		static void					Draw(Graphics& gfx);

		void						SetOver() { m_isOver = true; }
		bool						IsOver() const { return m_isOver; }

	private:
		bool						m_isOver = false;

		static constexpr Vector		s_size = Vector(86.0f, 64.0f);
		static constexpr Vector		s_position = Vector((Graphics::ScreenWidth - s_size.x) / 2,
														(Graphics::ScreenHeight - s_size.y) / 2);
	};
}
