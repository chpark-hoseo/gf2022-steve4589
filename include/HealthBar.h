#pragma once
#include <SDLGameObject.h>
#include <Animation.h>

class HealthBar : public SDLGameObject
{
public:
	HealthBar(const LoaderParams* pParams);
	virtual void draw() {}
	virtual void update() { }
	virtual void clean() {}
private:
	Animation* animation;
	void ResiceRect();
	//
};