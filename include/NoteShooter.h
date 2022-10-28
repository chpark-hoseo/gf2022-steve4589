#pragma once
#include <SDLGameObject.h>
#include <Animation.h>
#include <Vector2D.h>

class NoteShooter : public SDLGameObject
{
public:
	NoteShooter(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void Shot(float speed, Vector2D disPos);
	//Anim
	void SetIdle();
	void SetPop();

	void SetSetPos(Vector2D shotPos) {} //파워노트 나오는 곳, 생성자나 Awake()로 초기화 필요
private:
	Animation* m_animation = new Animation();

	Vector2D dispos = Vector2D(0, 0);
	Vector2D shotPos = Vector2D(0, 0);
};