#include "Rectangle.h"

Rectangle::Rectangle(const Vector& position)
	: m_position(position)
{}

MovingRectangle::MovingRectangle(const Vector& position, const Vector& direction)
	: Rectangle(position)
	, m_direction(direction)
{}
