﻿#pragma once

#include "Vector.h"

class Graphics;

namespace BrickBreaker
{
	/*------------*
	 *    Life    *
	 *------------*/

	class Life
	{
	public:
									Life(class GameOver& gameOver);

		void						Draw(Graphics& gfx);

		int							IsEmpty() const { return (m_count == 0); }
		void						Decrease();

	private:
		static constexpr int		s_initCount = 3;
		static constexpr Vector		s_size = Vector(24.0f, 24.0f);
		static constexpr Vector		s_position = Vector(0.0f, 0.0f);

		class GameOver&				m_gameOver;
		int							m_count = s_initCount;
	};
}