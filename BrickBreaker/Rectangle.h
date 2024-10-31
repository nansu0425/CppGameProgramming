#pragma once

#include "Vector.h"
#include "Graphics.h"
#include "Colors.h"

namespace BrickBreaker
{
	/////////////////////////////////////////Declarations/////////////////////////////////////////

	template<const Vector& size, const Color& color = Color()>
	class Rectangle
	{
	public:
		virtual void				Update(float deltaTime) abstract;
		virtual void				Draw(Graphics& graphics) const abstract;
		const Vector&				GetPosition() const;
		const Vector&				GetSize() const;
		const Color&				GetColor() const;

	protected:
		constexpr Rectangle(const Vector& position);

		static void					Draw(Graphics& graphics, const Rectangle* pRectangle);

	private:
		Vector						m_position;
		
		static constexpr Vector		s_size = size;
		static constexpr Color		s_color = color;
	};

	template<const Vector& size, size_t speed, const Color& color = Color()>
	class MovingRectangle : public Rectangle<size, color>
	{
	protected:
		constexpr MovingRectangle(const Vector& position, const Vector& direction);

		virtual void				Move(float deltaTime) abstract;

	private:
		Vector						m_direction;

		static constexpr float		s_speed = static_cast<float>(speed);
	};

	/////////////////////////////////////////Definitions/////////////////////////////////////////

	template<const Vector& size, const Color& color>
	inline constexpr Rectangle<size, color>::Rectangle(const Vector& position)
		: m_position(position)
	{}

	template<const Vector& size, const Color& color>
	inline const Vector& Rectangle<size, color>::GetPosition() const
	{
		return m_position;
	}

	template<const Vector& size, const Color& color>
	inline const Vector& Rectangle<size, color>::GetSize() const
	{
		return s_size;
	}

	template<const Vector& size, const Color& color>
	inline const Color& Rectangle<size, color>::GetColor() const
	{
		return s_color;
	}

	template<const Vector& size, const Color& color>
	inline void Rectangle<size, color>::Draw(Graphics& graphics, const Rectangle* pRectangle)
	{
		for (int dx = 0; dx < static_cast<int>(size.x); ++dx)
		{
			for (int dy = 0; dy < static_cast<int>(size.y); ++dy)
			{
				graphics.PutPixel(static_cast<int>(pRectangle->GetPosition().x) + dx,
								  static_cast<int>(pRectangle->GetPosition().y) + dy,
								  color);
			}
		}
	}

	template<const Vector& size, size_t speed, const Color& color>
	inline constexpr MovingRectangle<size, speed, color>::MovingRectangle(const Vector& position, const Vector& direction)
		: Rectangle<size, color>(position)
		, m_direction(direction)
	{}
}
