#pragma once

#include "Vector.h"

#include <utility>
#include <random>

class Graphics;
class MainWindow;
class Mouse;

class GameObject
{
public:
	GameObject(Graphics& gfx, const Vector& position, const Vector& size);

	virtual void Draw() const abstract;
	virtual void Move(float secondsDeltaTime) {}
	bool CheckCollision(const GameObject* pOther) const;

protected:
	void HandleOutWindow();
	virtual void HandleLeftOutWindow() {}
	virtual void HandleRightOutWindow() {}
	virtual void HandleTopOutWindow() {}
	virtual void HandleBottomOutWindow() {}
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom() const;

protected:
	Graphics& gfx;
	Vector position;
	Vector size;
};

class GameObjectFactory
{
public:
	GameObjectFactory(Graphics& gfx)
		: gfx(gfx)
		, rng(rd())
	{}

	template<typename T, typename... Args>
	T* Create(Args&&... args)
	{
		return new T(gfx, rng, std::forward<Args>(args)...);
	}

private:
	Graphics& gfx;
	std::random_device rd;
	std::mt19937 rng;
};

namespace GameObjectType
{
	class Face : public GameObject
	{
	public:
		static constexpr Vector s_size = Vector(20.0f, 20.0f);

		Face(Graphics& gfx, std::mt19937& rng, const Vector& position, const Mouse& mouse)
			: GameObject(gfx, position, s_size)
			, mouse(mouse)
		{}

		virtual void Draw() const override;
		virtual void Move(float secondsDeltaTime) override;

	protected:
		virtual void HandleLeftOutWindow() override;
		virtual void HandleRightOutWindow() override;
		virtual void HandleTopOutWindow() override;
		virtual void HandleBottomOutWindow() override;

	protected:
		const Mouse& mouse;
		static constexpr float s_speed = 120.0f;
		Vector direction;
	};

	class GameOver : public GameObject
	{
	public:
		static constexpr Vector s_size = Vector(86.0f, 64.0f);

		GameOver(Graphics& gfx, std::mt19937& rng, const Vector& position)
			: GameObject(gfx, position, s_size)
		{}

		virtual void Draw() const override;
	};

	class Title : public GameObject
	{
	public:
		static constexpr Vector s_size = Vector(150.0f, 175.0f);

		Title(Graphics& gfx, std::mt19937& rng, const Vector& position)
			: GameObject(gfx, position, s_size)
		{}

		virtual void Draw() const override;
	};

	class Poo : public GameObject
	{
	public:
		static constexpr Vector s_size = Vector(24.0f, 24.0f);

		Poo(Graphics& gfx, std::mt19937& rng, const Vector& position = Vector(-1.0f, -1.0f));

		virtual void Draw() const override;
		virtual void Move(float secondsDeltaTime) override;

	protected:
		virtual void HandleLeftOutWindow() override;
		virtual void HandleRightOutWindow() override;
		virtual void HandleTopOutWindow() override;
		virtual void HandleBottomOutWindow() override;

	protected:
		static constexpr float s_minSpeed = 60.0f;
		static constexpr float s_maxSpeed = 180.0f;
		Vector direction;
		float speed = 0.0f;
	};
}
