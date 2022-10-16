#pragma once
#include<SDL2/SDL.h>
#include<string>
#include<Vector2D.h>
#include<LoaderParams.h>
#include <TextureManager.h>

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual ~GameObject() {}

	virtual void OnEnable() {};
	void SetActive(bool isOn) {
		if (isOn)
		{
			onOff = true;
			OnEnable();
		}
		else onOff = false;
	}

	virtual void SetPosition(Vector2D getPos) = 0;

	virtual const char* GetName() = 0;
	virtual void SetName(const char* getName) = 0;

	virtual float GetSpeed() = 0;
	virtual void SetSpeed(float getSpeed) = 0;

protected:
	GameObject(const LoaderParams* pParams) {}

	std::string m_textureID;
	int m_width;
	int m_height;
	int m_currentFrame;
	int m_currentRow;

	float speed = 0.5;

	const char* name;
	bool onOff = true;
};