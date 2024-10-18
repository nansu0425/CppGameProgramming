#pragma once

class Graphics;
class MainWindow;

class GameObject
{
public:
	GameObject(int x, int y, int width, int height, MainWindow& wnd, Graphics& gfx)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
		, wnd(wnd)
		, gfx(gfx)
	{}

	virtual void Draw() const abstract;
	virtual void Move();
	bool CheckCollision(const GameObject* pOther) const;

protected:
	void ClampPositionScreen();
	int GetLeft() const;
	int GetRight() const;
	int GetTop() const;
	int GetBottom() const;

protected:
	int x;
	int y;
	int width;
	int height;
	MainWindow& wnd;
	Graphics& gfx;
};

class GameObjectFactory
{
public:
	GameObjectFactory(MainWindow& wnd, Graphics& gfx)
		: wnd(wnd)
		, gfx(gfx)
	{}

	template<typename T>
	T* Create(int x, int y)
	{
		return new T(x, y, wnd, gfx);
	}

private:
	MainWindow& wnd;
	Graphics& gfx;
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

		Face(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, WIDTH, HEIGHT, wnd, gfx)
		{}

		virtual void Draw() const override;
		virtual void Move() override;
	};

	class GameOver : public GameObject
	{
	public:
		enum Size
		{
			WIDTH = 86,
			HEIGHT = 64,
		};

		GameOver(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, WIDTH, HEIGHT, wnd, gfx)
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

		Title(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, WIDTH, HEIGHT, wnd, gfx)
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

		Poo(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, WIDTH, HEIGHT, wnd, gfx)
		{}

		virtual void Draw() const override;
	};
}
