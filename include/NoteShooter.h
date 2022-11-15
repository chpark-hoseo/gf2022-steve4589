#pragma once
#include <SDLGameObject.h>
#include <Animation.h>
#include <DirShot.h>
#include <vector>

class NoteShooter : public SDLGameObject, public DirShot
{
public:
	NoteShooter(const LoaderParams* pParams, vector<NoteShooter*> noteShooters);

	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void Shot(float speed, Vector2D disPos);
	//Anim
	void SetIdle();
	void SetPop();
private:
	Animation* m_animation = new Animation();

	virtual void dirShotAct();
};