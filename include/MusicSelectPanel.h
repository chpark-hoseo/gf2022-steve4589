#pragma once
#include <SDLGameObject.h>
class MusicSelectPanel : public SDLGameObject
{
private:

public:
	MusicSelectPanel(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
};