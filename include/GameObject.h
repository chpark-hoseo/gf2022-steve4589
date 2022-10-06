#pragma once
#include<SDL2/SDL.h>
#include<string>
#include<Vector2D.h>
#include<LoaderParams.h>

class INoteType { //StrategePattern과는 거리가 멀듯 
public:
	virtual void move() = 0; //toPlayer || Fall
	virtual void crashEvent() = 0; //플레이어 / 미 적중시 이펙트 및 보상 / 패널티
};

class GameObject 
{

public:
	virtual  void load(int x, int y, int width, int height, int currentRow, int currentFrame, std::string textureID);
	virtual void draw(SDL_Renderer* pRenderer) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual ~GameObject() {}

protected:
	GameObject(const LoaderParams* pParams) {}

	std::string m_textureID;

	//Vector2D m_position;
	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;

	int m_x;
	int m_y;

	int speed;
};