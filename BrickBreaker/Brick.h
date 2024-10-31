#pragma once

#include "Rectangle.h"
#include "Constants.h"

namespace BrickBreaker
{
	/////////////////////////////////////////Declarations/////////////////////////////////////////

	template<const Color& color>
	class Brick : public Rectangle<Size::Brick, color>
	{
	public:
		constexpr Brick(const Vector& position);

		virtual void				Update(float deltaTime) final;
		virtual void				Draw(Graphics& graphics) const final;
	};

	/////////////////////////////////////////Definitions/////////////////////////////////////////

	template<const Color& color>
	inline constexpr Brick<color>::Brick(const Vector& position)
		: Rectangle<Size::Brick, color>(position)
	{}

	template<const Color& color>
	inline void Brick<color>::Update(float deltaTime)
	{}

	template<const Color& color>
	inline void Brick<color>::Draw(Graphics& graphics) const
	{
		Rectangle<Size::Brick, color>::Draw(graphics, this);
	}
}
