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

class Collider2D //���� ó�� �ε�ġ�� / ������
{
private:
	bool isEnter = false;
	bool isExit = true;

	A a;
	B bb;

	SDL_Rect* b;

	Vector2D* p_getXY;
public:
	Collider2D(float x, float y, int h, int w) //�����ӿ��� ��� ����(x)�� ��ġ�� �������θ� ���ǹǷ� ���� �������ݴϴ�
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