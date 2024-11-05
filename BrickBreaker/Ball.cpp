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

	void Ball::Move(float deltaTime, const Graphics& gfx)
	{
		RectangleBall nextRectangle = GetNextMoveRectangle(deltaTime);
		ReboundOutScreen(deltaTime, gfx, nextRectangle);

		SetPosition(nextRectangle.GetPosition());
	}

	void Ball::ReboundOutScreen(float deltaTime, const Graphics& gfx, RectangleBall& nextRectangle)
	{
		// 다음 이동 위치가 화면의 x축 범위를 넘어가는 경우
		if (nextRectangle.IsOutScreenX(gfx))
		{
			ReboundX(GetDirection());
			nextRectangle = GetNextMoveRectangle(deltaTime);
		}

		// 다음 이동 위치가 화면의 y축 범위를 넘어가는 경우
		if (nextRectangle.IsOutScreenY(gfx))
		{
			ReboundY(GetDirection());
			nextRectangle = GetNextMoveRectangle(deltaTime);
		}
	}
}
