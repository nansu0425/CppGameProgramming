#include "Ball.h"
#include "Paddle.h"
#include "GameOver.h"

#include <random>

namespace BrickBreaker
{
	/*------------*
	 *    Ball    *
	 *------------*/

	Ball::Ball(GameOver& gameOver)
		: Ball(GBall::g_initPosition, GBall::g_rangeDirectionX, gameOver)
	{}

	Ball::Ball(const Vector& position, const Vector& direction, GameOver& gameOver)
		: m_rectangle(position)
		, m_direction(direction)
		, m_gameOver(gameOver)
	{}

	Ball::Ball(const Vector& position, float rangeDirectionX, GameOver& gameOver)
		: m_rectangle(position)
		, m_gameOver(gameOver)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_real_distribution<float> directionX(-rangeDirectionX, rangeDirectionX);
		
		m_direction = Vector(directionX(rng), -1.0f);
	}

	void Ball::Move(float deltaTime, const Graphics& gfx, const Paddle& paddle)
	{
		RectangleBall nextRectangle = GetNextMoveRectangle(deltaTime);
		
		if (ReboundOutScreen(deltaTime, gfx, nextRectangle))
		{
			// DeterminePaddleCanHandleCollision(paddle);
			
			// 게임 종료
			m_gameOver.SetOver();
		}

		SetPosition(nextRectangle.GetPosition());
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
