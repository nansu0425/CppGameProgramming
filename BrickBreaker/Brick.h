#pragma once

#include "Rectangle.h"
#include "Globals.h"
#include "Graphics.h"

namespace BrickBreaker
{
	/*-------------*
	 *    Brick    *
	 *-------------*/

	template<const Color& color>
	class Brick
	{
	private:
		using				Rectangle = Rectangle<GBrick::g_size>;

	public:
		constexpr			Brick(const Vector& position);

		void				Draw(Graphics& gfx) const;
		void				Update(float deltaTime) {}

		const Vector&		GetPosition() const { return m_rectangle.GetPosition(); }
		void				SetPosition(const Vector& position) { m_rectangle.SetPosition(position); }
		const Vector&		GetSize() const { return GBrick::g_size; }
		const Rectangle&	GetRectangle() const { return m_rectangle; }
		const Color&		GetColor() const { return color; }

	private:
		Rectangle			m_rectangle;
	};
}

namespace BrickBreaker
{
	/*-------------*
	 *    Brick    *
	 *-------------*/

	template<const Color& color>
	inline constexpr Brick<color>::Brick(const Vector& position)
		: m_rectangle(position)
	{}

	template<const Color& color>
	inline void Brick<color>::Draw(Graphics& gfx) const
	{
		for (int dx = 0; dx < static_cast<int>(GetSize().x); ++dx)
		{
			for (int dy = 0; dy < static_cast<int>(GetSize().y); ++dy)
			{
				gfx.PutPixel(static_cast<int>(GetPosition().x) + dx, 
							 static_cast<int>(GetPosition().y) + dy, 
							 color);
			}
		}
	}
}
