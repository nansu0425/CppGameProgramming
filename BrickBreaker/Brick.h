#pragma once

#include "ObjectInterfaces.h"
#include "Rectangle.h"
#include "Globals.h"
#include "Graphics.h"

/////////////////////////////////////////Method Declarations/////////////////////////////////////////

namespace BrickBreaker
{
	/*-------------*
	 *    Brick    *
	 *-------------*/

	template<const Color& color>
	class Brick : public IRectangleObject<GBrick::g_size>
	{
	public:
		constexpr Brick(const Vector& position);

		virtual void								Update(float deltaTime) final;
		virtual void								Draw(Graphics& gfx) const final;

		virtual const Vector&						GetPosition() const final;
		virtual void								SetPosition(const Vector& position) final;
		virtual const Vector&						GetSize() const final;
		virtual const Rectangle<GBrick::g_size>&	GetRectangle() const final;
		const Color&								GetColor() const;

	private:
		Rectangle<GBrick::g_size>					m_rectangle;
	};
}

/////////////////////////////////////////Method Definitions/////////////////////////////////////////

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
	inline void Brick<color>::Update(float deltaTime)
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

	template<const Color& color>
	inline const Vector& Brick<color>::GetPosition() const
	{
		return m_rectangle.GetPosition();
	}

	template<const Color& color>
	inline void Brick<color>::SetPosition(const Vector& position)
	{
		m_rectangle.SetPosition(position);
	}

	template<const Color& color>
	inline const Vector& Brick<color>::GetSize() const
	{
		return GBrick::g_size;
	}

	template<const Color& color>
	inline const Rectangle<GBrick::g_size>& Brick<color>::GetRectangle() const
	{
		return m_rectangle;
	}

	template<const Color& color>
	inline const Color& Brick<color>::GetColor() const
	{
		return color;
	}
}
