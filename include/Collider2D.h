#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <Vector2D.h>

class Collider2D //서로 처음 부딪치고 / 나갈때
{
private :
	std::string tag; 

	float parentX, parentY;
	float m_x, m_y;
	float width, height;

	bool isEnter = false;
	bool isExit = false;
	
	SDL_Rect * a;
	SDL_Rect * b; 

	Vector2D * p_getXY;
public :
	Collider2D(SDL_Rect* getA)
	{
		a = getA;
	};
	bool OnCollisionEnder2D();
	bool OnCollisionExit2D();

	void GetXY(Vector2D getVector) { p_getXY = &getVector; }
	void SetRectB(Vector2D * getXY, int width, int height) { b->x = p_getXY->getX(); b->y = p_getXY->getY(); b->w = width;  b->h = height; }
	//update

	void SetPosition(float x, float y)
	{
		m_x = parentX;
		m_y = parentY;
	}
	static bool CheckAABB(const SDL_Rect& m_AABB, const SDL_Rect& d_AABB);
	//float m_x, float m_y, int m_width, int m_height, float d_x, float d_y, int d_width, int d_height
};