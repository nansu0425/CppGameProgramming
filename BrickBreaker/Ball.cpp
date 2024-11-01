#include "Ball.h"
#include "Graphics.h"
#include "Sprites.h"

/////////////////////////////////////////Method Definitions/////////////////////////////////////////

namespace BrickBreaker
{
	/*------------*
	 *    Ball    *
	 *------------*/

	Ball::Ball(const Vector& position, const Vector& direction)
		: m_rectangle(position)
		, m_direction(direction)
	{}

	void Ball::Update(float deltaTime)
	{
		Move(deltaTime);
	}

	void Ball::Draw(Graphics& gfx) const
	{
		Sprites::DrawBall(GetPosition(), gfx);
	}

	void Ball::Move(float deltaTime)
	{
		SetPosition(GetPosition() + 
					GetDirection().GetNormalized() * GetSpeed() * deltaTime);
	}

	const Vector& Ball::GetPosition() const
	{
		return GetRectangle().GetPosition();
	}

	void Ball::SetPosition(const Vector& position)
	{
		m_rectangle.SetPosition(position);
	}

	const Vector& Ball::GetSize() const
	{
		return GBall::g_size;
	}

	const Rectangle<GBall::g_size>& Ball::GetRectangle() const
	{
		return m_rectangle;
	}

	float Ball::GetSpeed() const
	{
		return GBall::g_speed;
	}

	const Vector& Ball::GetDirection() const
	{
		return m_direction;
	}

	void Ball::SetDirection(const Vector& direction)
	{
		m_direction = direction;
	}
}
