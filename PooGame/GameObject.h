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
		Face(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, 20, 20, wnd, gfx)
		{}

		virtual void Draw() const override;
		virtual void Move() override;
	};

	class GameOver : public GameObject
	{
	public:
		GameOver(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, 86, 64, wnd, gfx)
		{}

		virtual void Draw() const override;
	};

	class Title : public GameObject
	{
	public:
		Title(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, 150, 175, wnd, gfx)
		{}

		virtual void Draw() const override;
	};

	class Poo : public GameObject
	{
	public:
		Poo(int x, int y, MainWindow& wnd, Graphics& gfx)
			: GameObject(x, y, 24, 24, wnd, gfx)
		{}

		virtual void Draw() const override;
		bool GetCollisionFlag() const;
		void SetCollisionFlag(bool flag);

	private:
		bool collisionFlag = false;
	};
}
