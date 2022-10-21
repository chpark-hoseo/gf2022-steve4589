#pragma once
#include <SDLGameObject.h>

class NoteBoom : public SDLGameObject
{
public :
	NoteBoom(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
	//make if interface?
	void Animation_On(); 

private :

};