#include <Timer.h>
#include <iostream>

Timer* Timer::timer_instance = 0;

double Timer::StartTimer() 
{
	curTime = SDL_GetTicks();
	timer = (curTime - waitTime) * 0.001; //1000 -> 1초

	return timer;
}

void Timer::WaitTime() //timer를 0으로 초기화하는 역할입니다 
{
	waitTime = SDL_GetTicks();
}