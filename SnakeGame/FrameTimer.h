#pragma once

#include <chrono>

class FrameTimer
{
public:
	using Clock = std::chrono::steady_clock;

	FrameTimer();

	void					UpdateDeltaTime();
	float					GetSecondsDeltaTime() const { return m_secondsDeltaTime; }

private:
	Clock::time_point		m_last;
	float					m_secondsDeltaTime = 0.0f;
};
