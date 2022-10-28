#include <NoteShooter.h>
#include <Game.h>

NoteShooter::NoteShooter(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NoteShooter::draw()
{
	m_animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height);
}
void NoteShooter::update()
{
	if (!onOff) return;

	m_animation->Update();
	SDLGameObject::update();
}
void NoteShooter::Shot(float speed)
{
	SetPop();

	GameObject* gameObject = Game::GetInstance()->GetObject(m_position, "PowerNote");
	gameObject->SetSpeed(speed);

	Game::GetInstance()->GetObject(m_position, "PowerNoteStartBoom");
}
void NoteShooter::SetIdle()
{
	m_animation->SetProp("noteShooter_stage1_idle_sprite", 0.01f, 0, 6);

	m_animation->StartAnimation(); 
	m_animation->SetAnimPause(false);
}
void NoteShooter::SetPop()
{
	m_animation->SetProp("noteShooter_stage1_pop_sprite", 0.01f, 0, 6);

	m_animation->SetAnimPause(true);
	m_animation->AnimationOnce(); //Æ®¸®°Å 
}
