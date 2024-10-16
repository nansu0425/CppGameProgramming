#pragma once

class Graphics;
class MainWindow;

class GameObject
{
public:
	GameObject(int x, int y, int width, int height)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
	{}

	virtual void Draw(Graphics& gfx) const abstract;
	virtual void Move(const MainWindow& wnd, const Graphics& gfx);
	bool CheckCollision(const GameObject& other) const;

protected:
	void ClampPositionScreen(const Graphics& gfx);
	int GetLeft() const;
	int GetRight() const;
	int GetTop() const;
	int GetBottom() const;

protected:
	int x;
	int y;
	int width;
	int height;
};

class Face : public GameObject
{
public:
	Face(int x, int y)
		: GameObject(x, y, 20, 20)
	{}

	virtual void Draw(Graphics& gfx) const override;
	virtual void Move(const MainWindow& wnd, const Graphics& gfx) override;
};

class GameOver : public GameObject
{
public:
	GameOver(int x, int y)
		: GameObject(x, y, 86, 64)
	{}

	virtual void Draw(Graphics& gfx) const override;
};

class Title : public GameObject
{
public:
	Title(int x, int y)
		: GameObject(x, y, 150, 175)
	{}

	virtual void Draw(Graphics& gfx) const override;
};

class Poo : public GameObject
{
public:
	Poo(int x, int y)
		: GameObject(x, y, 24, 24)
	{}

	virtual void Draw(Graphics& gfx) const override;
	bool GetCollisionFlag() const;
	void SetCollisionFlag(bool flag);

private:
	bool collisionFlag = false;
};
