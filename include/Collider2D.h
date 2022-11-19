#pragma once
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <Vector2D.h>
#include <stack>
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

	A a;
	B b;
	vector<GameObject*> colliders;
	vector<GameObject*> collidedObjects;  

	bool CheckAABB(a_AABB m_AABB, b_AABB d_AABB);
public:
	Collider2D(float x, float y, int h, int w) //�����ӿ��� ��� ����(x)�� ��ġ�� �������θ� ���ǹǷ� ���� �������ݴϴ�
	{
		a.x = x;
		a.y = y;
		a.w = w;
		a.h = h;
	};
	void EnterNotesPop();
	void SetPosition(float x, float y, int h, int w);
	//�����ӿ��� ��� ����(x)�� ��ġ�� �������θ� ���ǹǷ� ���� �������ݴϴ�
	   //�����ѵ� ��ġ�� ��⶧���� �Լ��� �޽��ϴ� 

	GameObject* OnCollision2D(std::string tag);
	vector <GameObject*> OnCollisionExit2D(std::string tag);
};