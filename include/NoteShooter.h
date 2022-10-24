#pragma once
#include <SDLGameObject.h>

class State
{

};

class NoteShooter : public SDLGameObject
{
public :
	NoteShooter(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void Shot();
private :
	/*
	void AniStart();
	void AninEnd();
	void AniPop();

	void State()
	{
		SetState(State statue)
	}

	void SetState()
	{

	}*/
};