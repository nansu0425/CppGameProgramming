#pragma once

struct Vector
{
	Vector() = default;
	Vector(float x, float y);

	float		GetLength() const;
	Vector		GetNormalized() const;

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
