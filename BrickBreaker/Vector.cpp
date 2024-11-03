#include "Vector.h"

/*--------------*
 *    Vector    *
 *--------------*/

Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Vector& Vector::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;

	return *this;
}

Vector& Vector::operator/=(float rhs)
{
	x /= rhs;
	y /= rhs;

	return *this;
}
