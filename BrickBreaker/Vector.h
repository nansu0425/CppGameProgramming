#pragma once

struct Vector
{
	constexpr	Vector() = default;
	
	constexpr	Vector(float x, float y)
		: x(x)
		, y(y)
	{}
	
	constexpr	Vector(size_t x, size_t y)
		: x(static_cast<float>(x))
		, y(static_cast<float>(y))
	{}

	float		GetLength() const;
	Vector		GetNormalized() const;
	bool		IsZero() const;

	Vector		operator+(const Vector& rhs) const;
	Vector&		operator+=(const Vector& rhs);
	Vector		operator-(const Vector& rhs) const;
	Vector&		operator-=(const Vector& rhs);
	Vector		operator*(float rhs) const;
	Vector&		operator*=(float rhs);
	Vector		operator/(float rhs) const;
	Vector&		operator/=(float rhs);

	float		x = 0.0f;
	float		y = 0.0f;
};
