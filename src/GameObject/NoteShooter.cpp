#include <NoteShooter.h>
#include <Game.h>

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
void NoteShooter::Shot()
{
	//if(getState() == false) //�ִ��۵�
	//else 
	Game::GetInstance()->GetObject(m_position, "PowerNote");
}