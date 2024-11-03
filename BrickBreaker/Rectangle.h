#pragma once

#include "Vector.h"
#include "Graphics.h"

namespace BrickBreaker
{
	/*-----------------*
	 *    Rectangle    *
	 *-----------------*/

	template<const Vector& size>
	class Rectangle
	{
	public:
		constexpr			Rectangle() = default;
		constexpr			Rectangle(const Vector& position);

		const Vector&		GetPosition() const { return m_position; }
		void				SetPosition(const Vector& position) { m_position = position; }
		const Vector&		GetSize() const { return size; }

		float				GetLeft() const { return GetPosition().x; }
		float				GetRight() const { return GetPosition().x + GetSize().x - 1.0f; }
		float				GetTop() const { return GetPosition().y; }
		float				GetBottom() const { return GetPosition().y + GetSize().y - 1.0f; }
		bool				IsOutScreenX(const Graphics& gfx) const { return ((GetLeft() < 0.0f) || (gfx.ScreenWidth <= GetRight())); }
		bool				IsOutScreenY(const Graphics& gfx) const { return ((GetTop() < 0.0f) || (gfx.ScreenHeight <= GetBottom())); }
			 
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
