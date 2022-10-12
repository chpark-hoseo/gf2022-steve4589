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

	const char* GetName() { return name; }
	void SetName(const char* getName) { name = getName; }

	bool GetOnOff() { return onOff;  }

protected:
	GameObject(const LoaderParams* pParams) {}

	std::string m_textureID;

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;

	const char* name;
	bool onOff = true;
};