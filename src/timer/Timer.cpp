#pragma once
#include <Timer.h>
#include <iostream>

Timer* Timer::timer_instance = 0;

double Timer::StartTimer() 
{
	curTime = SDL_GetTicks();
	timer = (curTime - waitTime) * 0.001; //1000 -> 1��

	return timer;
}

void Timer::WaitTime() //timer�� 0���� �ʱ�ȭ�ϴ� �����Դϴ� 
{
	waitTime = SDL_GetTicks();
}