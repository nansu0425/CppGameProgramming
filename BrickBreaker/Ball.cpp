#include "Ball.h"

namespace BrickBreaker
{
	/*------------*
	 *    Ball    *
	 *------------*/

	Ball::Ball(const Vector& position, const Vector& direction)
		: m_rectangle(position)
		, m_direction(direction)
	{}
}
