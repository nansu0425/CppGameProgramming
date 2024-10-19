#pragma once

#include <utility>
#include <random>

class Graphics;
class MainWindow;

class GameObject
{
public:
	GameObject(MainWindow& wnd, Graphics& gfx, int x, int y, int width, int height)
		: wnd(wnd)
		, gfx(gfx)
		, x(x)
		, y(y)
		, width(width)
		, height(height)
	{}

	virtual void Draw() const abstract;
	virtual void Move() {}
	bool CheckCollision(const GameObject* pOther) const;

protected:
	void HandleOutWindow();
	virtual void HandleLeftOutWindow() {}
	virtual void HandleRightOutWindow() {}
	virtual void HandleTopOutWindow() {}
	virtual void HandleBottomOutWindow() {}
	int GetLeft() const;
	int GetRight() const;
	int GetTop() const;
	int GetBottom() const;

protected:
	MainWindow& wnd;
	Graphics& gfx;
	int x;
	int y;
	int width;
	int height;
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
		enum Size
		{
			WIDTH = 20,
			HEIGHT = 20,
		};

		Face(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, int x = 0, int y = 0)
			: GameObject(wnd, gfx, x, y, WIDTH, HEIGHT)
		{}

		virtual void Draw() const override;
		virtual void Move() override;

	protected:
		virtual void HandleLeftOutWindow() override;
		virtual void HandleRightOutWindow() override;
		virtual void HandleTopOutWindow() override;
		virtual void HandleBottomOutWindow() override;
	};

	class GameOver : public GameObject
	{
	public:
		enum Size
		{
			WIDTH = 86,
			HEIGHT = 64,
		};

		GameOver(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, int x = 0, int y = 0)
			: GameObject(wnd, gfx, x, y, WIDTH, HEIGHT)
		{}

		virtual void Draw() const override;
	};

	class Title : public GameObject
	{
	public:
		enum Size
		{
			WIDTH = 150,
			HEIGHT = 175,
		};

		Title(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, int x = 0, int y = 0)
			: GameObject(wnd, gfx, x, y, WIDTH, HEIGHT)
		{}

		virtual void Draw() const override;
	};

	class Poo : public GameObject
	{
	public:
		enum Size
		{
			WIDTH = 24,
			HEIGHT = 24,
		};

		Poo(MainWindow& wnd, Graphics& gfx, std::mt19937& rng, int x = -1, int y = -1);

		virtual void Draw() const override;
		virtual void Move() override;

	protected:
		virtual void HandleLeftOutWindow() override;
		virtual void HandleRightOutWindow() override;
		virtual void HandleTopOutWindow() override;
		virtual void HandleBottomOutWindow() override;

	protected:
		int veloX = 0;
		int veloY = 0;
	};
}
