#pragma once

#include "Vector.h"

namespace BrickBreaker
{
	/////////////////////////////////////////Method Declarations/////////////////////////////////////////

	/*-----------------*
	 *    Rectangle    *
	 *-----------------*/

	template<const Vector& size>
	class Rectangle
	{
	public:
		constexpr Rectangle(const Vector& position);

		const Vector&					GetPosition() const;
		void							SetPosition(const Vector& position);
		const Vector&					GetSize() const;

	private:
		Vector							m_position;
	};

	/////////////////////////////////////////Method Definitions/////////////////////////////////////////

	/*-----------------*
	 *    Rectangle    *
	 *-----------------*/

	template<const Vector& size>
	inline constexpr Rectangle<size>::Rectangle(const Vector& position)
		: m_position(position)
	{}

	template<const Vector& size>
	inline const Vector& Rectangle<size>::GetPosition() const
	{
		return m_position;
	}

	template<const Vector& size>
	inline void Rectangle<size>::SetPosition(const Vector& position)
	{
		m_position = position;
	}

	template<const Vector& size>
	inline const Vector& Rectangle<size>::GetSize() const
	{
		return size;
	}
}
