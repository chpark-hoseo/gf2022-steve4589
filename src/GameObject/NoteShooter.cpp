#include <NoteShooter.h>
#include <Game.h>

NoteShooter::NoteShooter(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NoteShooter::draw()
{
	m_animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height);
	SDLGameObject::draw();
}
void NoteShooter::update()
{
	if (!onOff) return;
	m_animation->Update();
	SDLGameObject::update();
	SetState();
}
void NoteShooter::Shot()
{
	//if(getState() == false) //애니작동
	Game::GetInstance()->GetObject(m_position, "PowerNote");
}
//State
void NoteShooter::AnimationState()
{
	
}
void NoteShooter::SetState()
{
	switch (state)
	{
	default:
		break;
	case State_idle:

		break;
	case State_idle1:

		break;
	case State_pop:

		break;
	}
}