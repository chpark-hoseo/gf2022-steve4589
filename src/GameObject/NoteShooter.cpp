#include <NoteShooter.h>

NoteShooter::NoteShooter(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NoteShooter::draw()
{
	SDLGameObject::draw();
}
void NoteShooter::update()
{
	if (!onOff) return;
	SDLGameObject::update();
}