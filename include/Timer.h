#pragma once
#include <SDL2/SDL.h>

class Timer
{
public:
	static Timer* GetInstance()
	{
		if (timer_instance == 0)
			timer_instance = new Timer();
		return timer_instance;
	};
	double StartTimer();
	void WaitTime();

private:
	static Timer* timer_instance;
	double timer;
	double curTime;
	double waitTime;
};