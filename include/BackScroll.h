#pragma once
#include <SDLGameObject.h>
#include <vector>
#include <stdarg.h> //���� ���� 

class BackScroll : public SDLGameObject
{
private:
	virtual void draw() {}
	virtual void update() { Scroll(); }
	virtual void clean() {}

	void Scroll();

	vector<SDLGameObject*> backs;
	float speed[3] = { 0.3f, 0.45f, 0.6f };
	float middle = 0;
public:
	BackScroll(const LoaderParams* pParams, SDLGameObject* backFrame, SDLGameObject* backFrame1, SDLGameObject* backFrame2);

	//InItBacks();
};