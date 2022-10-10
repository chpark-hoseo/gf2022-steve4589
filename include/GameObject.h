#pragma once
#include<SDL2/SDL.h>
#include<string>
#include<Vector2D.h>
#include<LoaderParams.h>
#include <Game.h>
#include <TextureManager.h>

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual ~GameObject() {}

protected:
	GameObject(const LoaderParams* pParams) {}

	std::string m_textureID;

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;
};