#pragma once
#include <iostream>

class Animation
{
public :
	void Update();
	void Draw(float x, float y, int width, int height, std::string texture);

	void SetProp(std::string m_texture, int speed, int spriteRow, int frameCount, bool ionOff);
private :
	int m_speed;
	int m_frameCount;
	int m_spriteRow;
	int m_currentFrame;

	bool m_animRunning;

	double startTimer = 0;

	std::string m_textureID;

	void StartAnimation(bool onOff);
};