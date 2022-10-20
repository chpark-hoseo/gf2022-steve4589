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
	bool activeSelf()
	{
		if (onOff) return true;
		return false;
	}

	virtual void SetPosition(Vector2D getPos) = 0;
	virtual const Vector2D GetPosition() = 0; //SDL_Rect x, y값 초기화

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
		//나중에 getX랑 Y는 m_Position에서 받아와야 됨 
		//초기값 
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
};