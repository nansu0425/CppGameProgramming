#include "Paddle.h"
#include "MainWindow.h"

namespace BrickBreaker
{
	Paddle::Paddle(Graphics& gfx, const MainWindow& wnd, Ball& ball, const Vector& position)
		: m_gfx(gfx)
		, m_wnd(wnd)
		, m_ball(ball)
		, m_rectangle(position)
	{}

	void Paddle::Update(float deltaTime)
	{
		Move(deltaTime);
	}

	void Paddle::Draw() const
	{
		RectanglePaddle::Draw(m_gfx, m_rectangle.GetPosition(), m_color);
	}

	void Paddle::Move(float deltaTime)
	{
		m_direction.x = 0.0f;

		if (m_wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			--m_direction.x;
		}
		
		if (m_wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			++m_direction.x;
		}

		if (m_direction.x != 0.0f)
		{
			m_rectangle.SetPosition(m_rectangle.GetPosition() + m_direction * GetSpeed() * deltaTime);
		}
	}
}