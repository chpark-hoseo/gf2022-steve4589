#pragma once
#include <SDLGameObject.h>
#include <Animation.h>

class NoteShooter : public SDLGameObject
{
public:
	NoteShooter(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void Shot();
private:

	/*
	void AniStart();
	void AninEnd();
	void AniPop();

*/
};