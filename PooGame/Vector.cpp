#include "Vector.h"

#include <cmath>

Vector::Vector(float x, float y)
	: x(x)
	, y(y)
{}

float Vector::GetLength() const
{
	return std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f));
}

Vector Vector::GetNormalized() const
{
	return *this / GetLength();
}

Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(x + rhs.x, y + rhs.y);
}

Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vector Vector::operator-(const Vector& rhs) const
{
	return Vector(x - rhs.x, y - rhs.y);
}

Vector& Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Vector Vector::operator*(float rhs) const
{
	return Vector(x * rhs, y * rhs);
}

Vector& Vector::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;

	return *this;
}

Vector Vector::operator/(float rhs) const
{
	return Vector(x / rhs, y / rhs);
}

Vector& Vector::operator/=(float rhs)
{
	x /= rhs;
	y /= rhs;

	return *this;
}
