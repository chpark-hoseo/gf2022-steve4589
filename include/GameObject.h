#pragma once
#include<SDL2/SDL.h>
#include<string>
#include<Vector2D.h>
#include<LoaderParams.h>
#include <TextureManager.h>
#include <iostream>

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual ~GameObject() {}

	virtual void OnEnable() {};
	virtual void OnDisable() {};
	void SetActive(bool isOn) {
		if (isOn)
		{
			onOff = true;
			OnEnable();
		}
		else
		{
			if (!onFirst) OnDisable(); //생성될때 작동 방지 (초기화 여러번 방지)
			onOff = false;
			onFirst = false;
		}
	}
	bool activeSelf()
	{
		if (onOff) return true;
		return false;
	}

	virtual void SetPosition(Vector2D getPos) = 0;
	virtual const Vector2D GetPosition() = 0; //SDL_Rect x, y값 초기화
	virtual void SetDirVec(Vector2D getVec) { dirVec = getVec; }

	virtual const char* GetName() = 0;
	virtual void SetName(const char* getName) = 0;

	virtual float GetSpeed() = 0;
	virtual void SetSpeed(float getSpeed) = 0;

	string getTag() { return tag; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:
	GameObject(const LoaderParams* pParams) 
	{
		getRect.x = (int)pParams->getX();
		getRect.y = (int)pParams->getY();
		getRect.w = pParams->getWidth();
		getRect.h = pParams->getHeight();
	}

	std::string m_textureID;
	int m_width;
	int m_height;
	int m_currentFrame;
	int m_currentRow;

	float speed = 0.5;

	SDL_Rect getRect;

	std::string tag = "";  

	const char* name;
	bool onOff = true;
	bool onFirst = true;

	Vector2D dirVec = Vector2D(0, 0);
};