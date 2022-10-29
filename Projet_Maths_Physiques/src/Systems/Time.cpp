#include "Systems/Time.h"

Time::Time() : now_(std::chrono::high_resolution_clock::now()), dt_(0)
{

}

void Time::update()
{
	auto timeNow = std::chrono::high_resolution_clock::now();
	dt_ = std::chrono::duration<float, std::chrono::seconds::period>(timeNow - now_).count();
	now_ = timeNow;
}