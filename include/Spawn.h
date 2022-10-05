#pragma once
#include <stdio.h>

class Spawn
{
public:
	Spawn(float getDelay, float* getSpeed, int getPoint)
	{
		delay = getDelay;
		speed = getSpeed;
		point = getPoint;
	};
	float GetDelay() { return delay; }
	char* GetType() { return type; }
	int GetPoint() { return point; }

private:
	float delay;
	char* type;
	int point;
};