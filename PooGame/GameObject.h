#pragma once

#include <utility>
#include <random>

class Graphics;
class MainWindow;

class GameObject
{
public:
	GameObject(MainWindow& wnd, Graphics& gfx, float x, float y, float width, float height)
		: wnd(wnd)
		, gfx(gfx)
		, x(x)
		, y(y)
		, width(width)
		, height(height)
	{}

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
	MainWindow& wnd;
	Graphics& gfx;
	float x;
	float y;
	float width;
	float height;
};

class GameObjectFactory
{
public:
	GameObjectFactory(MainWindow& wnd, Graphics& gfx)
		: wnd(wnd)
		, gfx(gfx)
		, rng(rd())
	{}

	template<typename T, typename... Args>
	T* Create(Args&&... args)
	{
		return new T(wnd, gfx, rng, std::forward<Args>(args)...);
	}

private:
	MainWindow& wnd;
	Graphics& gfx;
	std::random_device rd;
	std::mt19937 rng;
};

namespace GameObjectType
{
	class Face : public GameObject
	{
	public:
		static constexpr float s_width = 20.0f;
		static constexpr float s_height = 20.0f;

		Face(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, float x = 0, float y = 0)
			: GameObject(wnd, gfx, x, y, s_width, s_height)
		{}

		virtual void Draw() const override;
		virtual void Move(float secondsDeltaTime) override;

	protected:
		virtual void HandleLeftOutWindow() override;
		virtual void HandleRightOutWindow() override;
		virtual void HandleTopOutWindow() override;
		virtual void HandleBottomOutWindow() override;

	protected:
		float velocityY = 60;
		float velocityX = 60;
	};

	class GameOver : public GameObject
	{
	public:
		static constexpr float s_width = 86.0f;
		static constexpr float s_height = 64.0f;

		GameOver(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, float x = 0, float y = 0)
			: GameObject(wnd, gfx, x, y, s_width, s_height)
		{}

		virtual void Draw() const override;
	};

	class Title : public GameObject
	{
	public:
		static constexpr float s_width = 150.0f;
		static constexpr float s_height = 175.0f;

		Title(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, float x = 0, float y = 0)
			: GameObject(wnd, gfx, x, y, s_width, s_height)
		{}

		virtual void Draw() const override;
	};

	class Poo : public GameObject
	{
	public:
		static constexpr float s_width = 24.0f;
		static constexpr float s_height = 24.0f;

		Poo(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, float x = -1, float y = -1);

		virtual void Draw() const override;
		virtual void Move(float secondsDeltaTime) override;

	protected:
		virtual void HandleLeftOutWindow() override;
		virtual void HandleRightOutWindow() override;
		virtual void HandleTopOutWindow() override;
		virtual void HandleBottomOutWindow() override;

	protected:
		int directionY = 0;
		int directionX = 0;
	};
}
