#pragma once
#include <Vector2D.h>

class SDLGameObject;

class DirShot
{
public:
	virtual void dirShot(float speed, Vector2D originPos, Vector2D disPos, const char* getTag); //알아서 옵젝 매니저에서 오브젝트를 뽑아줍니다
protected:
	virtual void dirShotAct() {}
};
