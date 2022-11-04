#pragma once
#include <SDLGameObject.h>
#include <Animation.h>

class HealthBar : public SDLGameObject
{
public:
	HealthBar(const LoaderParams* pParams, string getTag, int frameCount);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void SetMode();
private:
	Animation* animation = new Animation();
};