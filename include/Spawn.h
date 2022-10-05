#pragma once
#include <stdio.h>

class Spawn
{
public:
	Spawn(float getDelay, float getSpeed, int getPoint)
	{
		delay = getDelay;
		speed = getSpeed;
		point = getPoint;
	};
	float GetDelay() { return delay; }
	float GetType() { return speed; }
	int GetPoint() { return point; }

private:
	float delay;
	float speed;
	int point;
};