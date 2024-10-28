#include "FrameTimer.h"

FrameTimer::FrameTimer()
	: m_last(Clock::now())
{}

float FrameTimer::GetSecondsDeltaTime()
{
	Clock::time_point now = Clock::now();
	std::chrono::duration<float> deltaTime = now - m_last;

	m_last = now;

	return deltaTime.count();
}
