#pragma once
#include <SDLGameObject.h>
#include <Timer.h>
//#include <Coroutine>

class LerpPanel : public SDLGameObject
{
public:
	LerpPanel(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean() {}

	//�ð� ������ �ڷ�ƾ �Ἥ ���� 
	void startLerp(float r, float g, float b, float a, float time) {}
	void FadeOut(float time) {}
	void FadeIn(float time) {}
private:
	float curTime;
};