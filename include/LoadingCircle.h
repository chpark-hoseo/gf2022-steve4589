#pragma once
#include <SDLGameObject.h>

class LoadingCircle : public SDLGameObject
{
public:
	LoadingCircle(const LoaderParams* pParams, int size);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update() 
	{
		if (!onOff) return;
		MoveCircle();
		SDLGameObject::update();
	}
	virtual void clean() {}
private:
	int circleSize = 0;

	void MoveCircle() {} 
};
