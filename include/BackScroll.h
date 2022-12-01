#pragma once
#include <SDLGameObject.h>
#include <vector>
#include <stdarg.h> //가변 인자 

class BackScroll : public SDLGameObject
{
private:
	virtual void draw() {}
	virtual void update() { Scroll(); }
	virtual void clean() {}

	void Scroll();

	vector<SDLGameObject*> backs;
	float speed[3] = { 0.25f, 0.2f, 0.15f };
	float middle = 0;
public:
	BackScroll(const LoaderParams* pParams, SDLGameObject* backFrame, SDLGameObject* backFrame1, SDLGameObject* backFrame2);
};