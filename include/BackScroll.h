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
	void ChangeSprites(string sprite1, string sprite2, string sprite3);

	vector<SDLGameObject*> backs;
	float speed[3] = { 0.25f, 0.2f, 0.15f };
	float middle = 0;
public:
	BackScroll(const LoaderParams* pParams, SDLGameObject* backFrame, SDLGameObject* backFrame1, SDLGameObject* backFrame2);

	//InItBacks();
};