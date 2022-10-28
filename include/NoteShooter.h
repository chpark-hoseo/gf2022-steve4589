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

	virtual void OnEnable() { 
		m_animation->SetProp("noteShooter_stage1_pop_sprite", 0.01f, m_currentRow, 2);
		m_animation->SetAnimPause(false);
	}
	virtual void DisEnable() { isAnim = false; }

	void Shot(float speed);
	//Anim
	void SetIdle();
	void SetPop();

	void SetSetPos(Vector2D shotPos) {} //파워노트 나오는 곳, 생성자나 Awake()로 초기화 필요
private:
	Animation* m_animation = new Animation();
	Vector2D shotPos = Vector2D(0, 0);

	bool isAnim = false;
};