#include "Systems/Time.h"

Time::Time() : now_(std::chrono::high_resolution_clock::now()), dt_(0)
{
	timeScale_ = 1.0f;
}

void Time::update()
{
	auto timeNow = std::chrono::high_resolution_clock::now();
	dt_ = std::chrono::duration<float, std::chrono::seconds::period>(timeNow - now_).count();
	now_ = timeNow;
}

float Time::deltaTime()
{
	if (dt_ > 0.1f) return 0.1f * timeScale_;
	else return dt_ * timeScale_;
}

float Time::forcedDeltaTime()
{
	if (dt_ > 0.1f) return 0.1f;
	else return dt_;
}