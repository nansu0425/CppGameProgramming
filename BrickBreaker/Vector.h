#pragma once

#include <cmath>

/*--------------*
 *    Vector    *
 *--------------*/

struct Vector
{
	constexpr	Vector() = default;
	constexpr	Vector(float x, float y);

	float		GetLength() const { return std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f)); }
	Vector		GetNormalized() const { return *this / GetLength(); }
	bool		IsZero() const { return ((x == 0) && (y == 0)); }

	Vector		operator+(const Vector& rhs) const { return Vector(x + rhs.x, y + rhs.y); }
	Vector&		operator+=(const Vector& rhs);
	Vector		operator-(const Vector& rhs) const { return Vector(x - rhs.x, y - rhs.y); }
	Vector&		operator-=(const Vector& rhs);
	Vector		operator*(float rhs) const { return Vector(x * rhs, y * rhs); }
	Vector&		operator*=(float rhs);
	Vector		operator/(float rhs) const { return Vector(x / rhs, y / rhs); }
	Vector&		operator/=(float rhs);

	float		x = 0.0f;
	float		y = 0.0f;
};

/*--------------*
 *    Vector    *
 *--------------*/

constexpr Vector::Vector(float x, float y)
	: x(x)
	, y(y)
{}
