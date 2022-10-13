#pragma once
#include <SDLGameObject.h>

class NoteControl : public SDLGameObject
{
public :
	NoteControl(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
private :

};