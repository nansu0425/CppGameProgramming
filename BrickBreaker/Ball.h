#pragma once

#include "Globals.h"
#include "Rectangle.h"
#include "Sprites.h"
#include "Paddle.h"

#include <algorithm>

namespace BrickBreaker
{
	/*------------*
	 *    Ball    *
	 *------------*/

	class Ball
	{
	private:
		using					RectangleBall = Rectangle<GBall::g_size>;

	public:
								Ball(class GameOver& gameOver);
								Ball(const Vector& position, const Vector& direction, class GameOver& gameOver);
								Ball(const Vector& position, float rangeDirectionX, class GameOver& gameOver);

		void					Update(float deltaTime, const Graphics& gfx, const Paddle& paddle) { Move(deltaTime, gfx, paddle); }
		void					Draw(Graphics& gfx) const { Sprites::DrawBall(GetPosition(), gfx); }
		void					Move(float deltaTime, const Graphics& gfx, const Paddle& paddle);
		void					ReboundX(const Vector& direction) { SetDirection(Vector(-direction.x, direction.y)); }
		void					ReboundY(const Vector& direction) { SetDirection(Vector(direction.x, -direction.y)); }
		void					DeterminePaddleCanHandleCollision(const Paddle& paddle) { m_canPaddleHandleCollision = !m_rectangle.IsCollision(paddle.GetRectangle()); }
		bool					CanPaddleHandleCollision() const { return m_canPaddleHandleCollision; }

		const Vector&			GetPosition() const { return GetRectangle().GetPosition(); };
		void					SetPosition(const Vector& position) { m_rectangle.SetPosition(position); }
		const Vector&			GetSize() const { return GBall::g_size; }
		const RectangleBall&	GetRectangle() const { return m_rectangle; }
		float					GetSpeed() const { return GBall::g_speed; }
		const Vector&			GetDirection() const { return m_direction; }
		void					SetDirection(const Vector& direction) { m_direction = direction; }

	private:
		RectangleBall			GetNextMoveRectangle(float deltaTime) const { return GetPosition() + GetDirection().GetNormalized() * GetSpeed() * deltaTime; }
		bool					ReboundOutScreen(float deltaTime, const Graphics& gfx, RectangleBall& nextRectangle);

	private:
		class GameOver&			m_gameOver;
		RectangleBall			m_rectangle;
		Vector					m_direction;
		bool					m_canPaddleHandleCollision = true;
	};
}
