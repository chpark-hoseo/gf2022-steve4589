#pragma once
#include <stdio.h>

class Spawn
{
public:
	Spawn(float getDelay, char* getType, int getPoint)
	{
		delay = getDelay;
		type = getType;
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
