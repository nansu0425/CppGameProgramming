﻿#include "RectI.h"

RectI::RectI( const Vei2& topLeft,const Vei2 & bottomRight )
	:
	RectI( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
{
}

RectI::RectI( const Vei2& topLeft,int width,int height )
	:
	RectI( topLeft,topLeft + Vei2( width,height ) )
{
}

bool RectI::IsOverlappingWith( const RectI& other ) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool RectI::IsContainedBy( const RectI & other ) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

bool RectI::Contains(const Vei2& point) const
{
	return ((left <= point.x) &&
			(point.x < right) &&
			(top <= point.y) &&
			(point.y < bottom));
}

RectI RectI::FromCenter( const Vei2 & center,int halfWidth,int halfHeight )
{
	const Vei2 half( halfWidth,halfHeight );
	return RectI( center - half,center + half );
}

RectI RectI::GetExpanded( int offset ) const
{
	return RectI( left - offset,right + offset,top - offset,bottom + offset );
}

Vei2 RectI::GetCenter() const
{
	return Vei2( (left + right) / 2,(top + bottom) / 2 );
}

Vei2 RectI::GetPosition() const
{
	return Vei2(left, top);
}

RectI RectI::operator*(int scalar) const
{
	return RectI(left * scalar, 
				 right * scalar, 
				 top * scalar, 
				 bottom * scalar);
}
