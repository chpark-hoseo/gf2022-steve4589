#pragma once
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <Vector2D.h>
#include <SDLGameObject.h>

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
	B b;

	vector<GameObject*> colliders;
public:
	Collider2D(float x, float y, int h, int w) //�����ӿ��� ��� ����(x)�� ��ġ�� �������θ� ���ǹǷ� ���� �������ݴϴ�
	{
		a.x = x;
		a.y = y;
		a.w = w;
		a.h = h;
	};
	void SetPosition(float x, float y, int h, int w);
	//�����ӿ��� ��� ����(x)�� ��ġ�� �������θ� ���ǹǷ� ���� �������ݴϴ�
	   //�����ѵ� ��ġ�� ��⶧���� �Լ��� �޽��ϴ� 

	void OnCollision2D();
	bool OnCollisionExit2D();
	static bool CheckAABB(a_AABB m_AABB, b_AABB d_AABB);
};