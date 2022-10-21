#include <NoteBoom.h>

NoteBoom::NoteBoom(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NoteBoom::draw()
{
	SDLGameObject::draw();
}
void NoteBoom::update()  
{
	SDLGameObject::update();
	Animation_On();
}

void NoteBoom::Animation_On()
{

}