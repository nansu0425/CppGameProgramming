#pragma once

#include "Vector.h"

namespace BrickBreaker
{
	/*-----------------*
	 *    Rectangle    *
	 *-----------------*/

	template<const Vector& size>
	class Rectangle
	{
	public:
		constexpr			Rectangle(const Vector& position);

		const Vector&		GetPosition() const { return m_position; }
		void				SetPosition(const Vector& position) { m_position = position; }
		const Vector&		GetSize() const { return size; }

	private:
		Vector				m_position;
	};
}

namespace BrickBreaker
{
	/*-----------------*
	 *    Rectangle    *
	 *-----------------*/

	template<const Vector& size>
	inline constexpr Rectangle<size>::Rectangle(const Vector& position)
		: m_position(position)
	{}
}
