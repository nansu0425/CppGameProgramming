#pragma once

#include "Vector.h"

class Graphics;

class Rectangle
{
public:
	virtual void	Update(float deltaTime) abstract;
	virtual void	Draw(const Graphics& graphics) const abstract;

protected:
	Rectangle(const Vector& position);

protected:
	Vector			m_position;
};

class MovingRectangle : public Rectangle
{
protected:
	MovingRectangle(const Vector& position, const Vector& direction);

	virtual void	Move(float deltaTime) abstract;

protected:
	Vector			m_direction;
};
