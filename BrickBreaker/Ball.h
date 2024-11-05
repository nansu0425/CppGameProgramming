#pragma once

#include "Globals.h"
#include "Rectangle.h"
#include "Sprites.h"

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
								Ball(const Vector& position, const Vector& direction);

		void					Update(float deltaTime, const Graphics& gfx) { Move(deltaTime, gfx); }
		void					Draw(Graphics& gfx) const { Sprites::DrawBall(GetPosition(), gfx); }
		void					Move(float deltaTime, const Graphics& gfx);
		void					ReboundX(const Vector& direction) { SetDirection(Vector(-direction.x, direction.y)); }
		void					ReboundY(const Vector& direction) { SetDirection(Vector(direction.x, -direction.y)); }
		template<const Vector& sizeOther>
		void					ReboundCollision(const Rectangle<sizeOther>& other);

		const Vector&			GetPosition() const { return GetRectangle().GetPosition(); };
		void					SetPosition(const Vector& position) { m_rectangle.SetPosition(position); }
		const Vector&			GetSize() const { return GBall::g_size; }
		const RectangleBall&	GetRectangle() const { return m_rectangle; }
		float					GetSpeed() const { return GBall::g_speed; }
		const Vector&			GetDirection() const { return m_direction; }
		void					SetDirection(const Vector& direction) { m_direction = direction; }

	private:
		RectangleBall			GetNextMoveRectangle(float deltaTime) const { return GetPosition() + GetDirection().GetNormalized() * GetSpeed() * deltaTime; }
		void					ReboundOutScreen(float deltaTime, const Graphics& gfx, RectangleBall& nextRectangle);

	private:
		RectangleBall			m_rectangle;
		Vector					m_direction;
	};

	template<const Vector& sizeOther>
	inline void Ball::ReboundCollision(const Rectangle<sizeOther>& other)
	{
		const float diffLeft = GetRectangle().GetLeft() - other.GetLeft();
		const float diffRight = other.GetRight() - GetRectangle().GetRight();
		const float diffTop = GetRectangle().GetTop() - other.GetTop();
		const float diffBottom = other.GetBottom() - GetRectangle().GetBottom();

		if ((diffLeft >= 0) &&
			(diffRight >= 0))
		{
			ReboundY(GetDirection());
		}
		else if ((diffTop >= 0) &&
				 (diffBottom >= 0))
		{
			ReboundX(GetDirection());
		}
		else if (std::min(diffLeft, diffRight) < std::min(diffTop, diffBottom))
		{
			ReboundX(GetDirection());
		}
		else if (std::min(diffTop, diffBottom) < std::min(diffLeft, diffRight))
		{
			ReboundY(GetDirection());
		}
		else
		{
			ReboundX(GetDirection());
			ReboundY(GetDirection());
		}
	}
}
