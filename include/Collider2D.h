#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <Vector2D.h>

struct a_AABB
{
	float x;
	float y;
	int w;
	int h;
}typedef A;

struct b_AABB
{
	float x;
	float y;
	int w;
	int h;
}typedef B;

class Collider2D //서로 처음 부딪치고 / 나갈때
{
private:
	bool isEnter = false;
	bool isExit = true;

	A a;
	B bb;

	SDL_Rect* b;

	Vector2D* p_getXY;
public:
	Collider2D(float x, float y, int h, int w) //본게임에서 모든 원본(x)의 위치는 정적으로만 사용되므로 값만 세팅해줍니다
	{
		a.x = x;
		a.y = y;
		a.w = w;
		a.h = h;
	};
	bool OnCollision2D();
	bool OnCollisionExit2D();

	void SetPosition(float x, float y, int h, int w)
	{
		a.x = x;
		a.y = y;
		a.w = w;
		a.h = h;
	}

	static bool CheckAABB(struct a_AABB m_AABB, const SDL_Rect& d_AABB);
	//float m_x, float m_y, int m_width, int m_height, float d_x, float d_y, int d_width, int d_height
};