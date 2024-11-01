#pragma once

#include "ObjectInterfaces.h"
#include "Globals.h"
#include "Rectangle.h"

/////////////////////////////////////////Method Declarations/////////////////////////////////////////

namespace BrickBreaker
{
	/*------------*
	 *    Ball    *
	 *------------*/

	class Ball : public IRectangleObject<GBall::g_size>, public IMovingObject<GBall::g_speed>
	{
	public:
		Ball(const Vector& position, const Vector& direction);

		virtual void							Update(float deltaTime) final;
		virtual void							Draw(Graphics& gfx) const final;
		virtual void							Move(float deltaTime) final;

		virtual const Vector&					GetPosition() const final;
		virtual void							SetPosition(const Vector& position) final;
		virtual const Vector&					GetSize() const final;
		virtual const Rectangle<GBall::g_size>&	GetRectangle() const final;
		virtual float							GetSpeed() const final;
		virtual const Vector&					GetDirection() const final;
		virtual void							SetDirection(const Vector& direction) final;

	private:
		Rectangle<GBall::g_size>				m_rectangle;
		Vector									m_direction;
	};
}
