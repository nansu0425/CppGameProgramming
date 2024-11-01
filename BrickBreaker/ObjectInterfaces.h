#pragma once

/////////////////////////////////////////Forward Declarations/////////////////////////////////////////

class Graphics;
struct Vector;

namespace BrickBreaker
{
	template<const Vector& size>
	class Rectangle;
}

/////////////////////////////////////////Method Declarations/////////////////////////////////////////

namespace BrickBreaker
{
	/*-------------------*
	 *    IGameObject    *
	 *-------------------*/

	class IGameObject
	{
	public:
		virtual void					Update(float deltaTime) abstract;
		virtual void					Draw(Graphics& gfx) const abstract;

		virtual const Vector&			GetPosition() const abstract;
		virtual void					SetPosition(const Vector& position) abstract;
		virtual const Vector&			GetSize() const abstract;
	};

	/*------------------------*
	 *    IRectangleObject    *
	 *------------------------*/

	template<const Vector& size>
	class IRectangleObject : public IGameObject
	{
	public:
		virtual const Rectangle<size>&	GetRectangle() const abstract;
	};

	/*---------------------*
	 *    IMovingObject    *
	 *---------------------*/

	template<size_t speed>
	class IMovingObject : public IGameObject
	{
	public:
		virtual void					Move(float deltaTime) abstract;

		virtual float					GetSpeed() const abstract;
		virtual const Vector&			GetDirection() const abstract;
		virtual void					SetDirection(const Vector& direction) abstract;
	};
}
