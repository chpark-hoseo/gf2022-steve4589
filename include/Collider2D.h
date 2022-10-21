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

class Collider2D //서로 처음 부딪치고 / 나갈때
{
private:
	bool isEnter = false;
	bool isExit = true;

	A a;
	B b;

	vector<GameObject*> colliders;
public:
	Collider2D(float x, float y, int h, int w) //본게임에서 모든 원본(x)의 위치는 정적으로만 사용되므로 값만 세팅해줍니다
	{
		a.x = x;
		a.y = y;
		a.w = w;
		a.h = h;
	};
	void SetPosition(float x, float y, int h, int w);
	//본게임에서 모든 원본(x)의 위치는 정적으로만 사용되므로 값만 세팅해줍니다
	   //생성한뒤 위치를 잡기때문에 함수로 받습니다 

	void OnCollision2D();
	bool OnCollisionExit2D();
	static bool CheckAABB(a_AABB m_AABB, b_AABB d_AABB);
};