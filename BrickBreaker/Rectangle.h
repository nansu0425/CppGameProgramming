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
		static void			Draw(Graphics& gfx, const Vector& position, Color color, int thicknessBorder = 0);

		float				GetLeft() const { return GetPosition().x; }
		float				GetRight() const { return GetPosition().x + GetSize().x - 1.0f; }
		float				GetTop() const { return GetPosition().y; }
		float				GetBottom() const { return GetPosition().y + GetSize().y - 1.0f; }
		bool				IsOutScreenX(const Graphics& gfx) const { return ((GetLeft() < 0.0f) || (gfx.ScreenWidth <= GetRight())); }
		bool				IsOutScreenY(const Graphics& gfx) const { return ((GetTop() < 0.0f) || (gfx.ScreenHeight <= GetBottom())); }
		template<const Vector& sizeOther>
		bool				IsCollision(const Rectangle<sizeOther>& other) const;
			 
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

	template<const Vector& size>
	inline void Rectangle<size>::Draw(Graphics& gfx, const Vector& position, Color color, int thicknessBorder)
	{
		for (int dx = thicknessBorder; dx < static_cast<int>(size.x) - thicknessBorder; ++dx)
		{
			for (int dy = thicknessBorder; dy < static_cast<int>(size.y) - thicknessBorder; ++dy)
			{
				gfx.PutPixel(static_cast<int>(position.x) + dx,
							 static_cast<int>(position.y) + dy,
							 color);
			}
		}
	}

	template<const Vector& size>
	template<const Vector& sizeOther>
	inline bool Rectangle<size>::IsCollision(const Rectangle<sizeOther>& other) const
	{
		return ((other.GetLeft() <= GetRight()) &&
				(GetLeft() <= other.GetRight()) &&
				(other.GetTop() <= GetBottom()) &&
				(GetTop() <= other.GetBottom()));
	}
}
