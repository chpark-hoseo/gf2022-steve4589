#pragma once
#include <Vector2D.h>

class SDLGameObject;

class DirShot
{
public:
	virtual void dirShot(float speed, Vector2D originPos, Vector2D disPos, const char* getTag); //�˾Ƽ� ���� �Ŵ������� ������Ʈ�� �̾��ݴϴ�
protected:
	virtual void dirShotAct() {}
};
