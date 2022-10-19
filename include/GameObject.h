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
	virtual const Vector2D GetPosition() = 0; //SDL_Rect x, y�� �ʱ�ȭ

	virtual const char* GetName() = 0;
	virtual void SetName(const char* getName) = 0;

	virtual float GetSpeed() = 0;
	virtual void SetSpeed(float getSpeed) = 0;

	SDL_Rect GetRect() { return getRect; }

protected:
	GameObject(const LoaderParams* pParams) 
	{
		//���߿� getX�� Y�� m_Position���� �޾ƿ;� �� 
		//�ʱⰪ 
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

	const char* name;
	bool onOff = true;
};