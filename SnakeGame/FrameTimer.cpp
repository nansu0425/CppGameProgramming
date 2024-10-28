#include "FrameTimer.h"

FrameTimer::FrameTimer()
	: m_last(Clock::now())
{}

void FrameTimer::UpdateDeltaTime()
{
	Clock::time_point now = Clock::now();
	std::chrono::duration<float> deltaTime = now - m_last;

	m_last = now;
	m_secondsDeltaTime = deltaTime.count();
}
