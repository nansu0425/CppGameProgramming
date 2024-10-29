#pragma once

#include <chrono>

class FrameTimer
{
private:
	using Clock			= std::chrono::steady_clock;

public:
	FrameTimer();

	float				CalculateDeltaTime();

private:
	Clock::time_point	m_last;
};
