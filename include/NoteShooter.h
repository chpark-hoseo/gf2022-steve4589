#pragma once
#include <SDLGameObject.h>
#include <Animation.h>
#include <Vector2D.h>

enum State
{
	State_idle = 0,
	State_idle1,
	State_pop
};

class NoteShooter : public SDLGameObject
{
public:
	NoteShooter(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	virtual void OnEnable() { m_animation->SetProp(m_textureID, 0.01f, m_currentRow, 6); }

	void Shot();
	void SetSetPos(Vector2D shotPos) {} //파워노트 나오는 곳, 생성자나 Awake()로 초기화 필요
private:
	Animation* m_animation = new Animation();

	void AnimationState();
	void SetState();

	State state = State_idle;

	Vector2D shotPos = Vector2D(0, 0);

	/*
	void AniStart();
	void AninEnd();
	void AniPop();
*/
};