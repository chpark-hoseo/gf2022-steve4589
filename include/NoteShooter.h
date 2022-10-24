#pragma once
#include <SDLGameObject.h>

class NoteShooter : public SDLGameObject
{
public :
	NoteShooter(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
private :

};