#include "Ball.h"
#include "Paddle.h"
#include "Life.h"

namespace BrickBreaker
{
	/*------------*
	 *    Ball    *
	 *------------*/

	Ball::Ball(Life& life)
		: Ball(GBall::g_initPosition, GBall::g_rangeDirectionX, life)
	{}

	Ball::Ball(const Vector& position, float rangeDirectionX, Life& life)
		: m_rectangle(position)
		, m_life(life)
	{
		std::random_device rd;
		m_rng = std::mt19937(rd());
		m_directionX = DistributionF(-GBall::g_rangeDirectionX,
									 GBall::g_rangeDirectionX);

		Spawn();
	}

	void Ball::Move(float deltaTime, const Graphics& gfx, const Paddle& paddle)
	{
		RectangleBall nextRectangle = GetNextMoveRectangle(deltaTime);

		if (nextRectangle.IsOutScreenY(gfx))
		{
			m_life.Decrease();

			if (!m_life.IsEmpty())
			{
				Spawn();
				return;
			}
		}

		SetPosition(nextRectangle.GetPosition());
	}

	void Ball::Spawn()
	{
		SetPosition(GBall::g_initPosition);
		SetDirection(Vector(m_directionX(m_rng), -1.0f));
	}

	bool Ball::ReboundOutScreen(float deltaTime, const Graphics& gfx, RectangleBall& nextRectangle)
	{
		bool isRebound = false;

		// 다음 이동 위치가 화면의 x축 범위를 넘어가는 경우
		if (nextRectangle.IsOutScreenX(gfx))
		{
			ReboundX(GetDirection());
			nextRectangle = GetNextMoveRectangle(deltaTime);

			isRebound = true;
		}

		// 다음 이동 위치가 화면의 y축 범위를 넘어가는 경우
		if (nextRectangle.IsOutScreenY(gfx))
		{
			ReboundY(GetDirection());
			nextRectangle = GetNextMoveRectangle(deltaTime);

			isRebound = true;
		}

		return isRebound;
	}
}
