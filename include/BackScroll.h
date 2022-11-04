#pragma once
#include <SDLGameObject.h>
#include <vector>

class BackScroll : public SDLGameObject
{
private:
	BackScroll(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	vector<SDLGameObject*> backs;
public:
	//InItBacks();
};