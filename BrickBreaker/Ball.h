#pragma once

#include "Globals.h"
#include "Rectangle.h"
#include "Sprites.h"

namespace BrickBreaker
{
	/*------------*
	 *    Ball    *
	 *------------*/

	class Ball
	{
	private:
		using				Rectangle = Rectangle<GBall::g_size>;

	public:
							Ball(const Vector& position, const Vector& direction);

		void				Update(float deltaTime, const Graphics& gfx) { Move(deltaTime, gfx); }
		void				Draw(Graphics& gfx) const { Sprites::DrawBall(GetPosition(), gfx); }
		void				Move(float deltaTime, const Graphics& gfx);

		const Vector&		GetPosition() const { return GetRectangle().GetPosition(); };
		void				SetPosition(const Vector& position) { m_rectangle.SetPosition(position); }
		const Vector&		GetSize() const { return GBall::g_size; }
		const Rectangle&	GetRectangle() const { return m_rectangle; }
		float				GetSpeed() const { return GBall::g_speed; }
		const Vector&		GetDirection() const { return m_direction; }
		void				SetDirection(const Vector& direction) { m_direction = direction; }

	private:
		void				ReboundX(const Vector& direction) { SetDirection(Vector(-direction.x, direction.y)); }
		void				ReboundY(const Vector& direction) { SetDirection(Vector(direction.x, -direction.y)); }
		Rectangle			GetNextMoveRectangle(float deltaTime) const { return GetPosition() + GetDirection().GetNormalized() * GetSpeed() * deltaTime; }
		void				ReboundOutScreen(float deltaTime, const Graphics& gfx, Rectangle& nextRectangle);

	private:
		Rectangle			m_rectangle;
		Vector				m_direction;
	};
}
