#pragma once
#include <SDL2/SDL.h>
#include <TextureManager.h>

class GameObject {
public:
	virtual  void load(float x, float y, int width, int height,
		std::string textureID);
	virtual  void draw(SDL_Renderer* pRenderer);
	virtual  void update() {};
	virtual  void clean() {};

protected:
	std::string m_textureID;

	double m_x;
	double m_y;
	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;
};