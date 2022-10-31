#pragma once
#include <iostream>

class Animation
{
public :
	void Update();
	void Draw(float x, float y, int width, int height);

	bool GetAnimationOnce() { return m_animationOnce; }

	void SetProp(std::string textureID, float speed, int spriteRow, int frameCount);
	void SetAnimPause(bool onOff);
	void AnimationOnce(bool onOff);

	void StartAnimation();
private :
	float m_speed;
	int m_frameCount;
	int m_spriteRow;
	int m_currentFrame;

	bool m_animRunning = false;
	bool m_animationOnce = false;

	double startTimer = 0;

	std::string m_textureID;
};