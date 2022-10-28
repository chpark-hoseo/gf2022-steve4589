#include <NoteShooter.h>
#include <Game.h>
#include <PowerNote.h>

NoteShooter::NoteShooter(const LoaderParams* pParams) : SDLGameObject(pParams) 
{
	m_animation->SetProp(m_textureID, 0.01f, m_currentRow, 2);
	m_animation->SetAnimPause(false);
}

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
void NoteShooter::Shot(float speed, Vector2D disPos)
{
	SetPop();

	GameObject* gameObject = Game::GetInstance()->GetObject(m_position, "PowerNote");

	Vector2D shotPos = gameObject->GetPosition();

	float x = disPos.getX() - shotPos.getX();
	float y = disPos.getY() - shotPos.getY();

	Vector2D setDirVec = Vector2D(x, y);
	setDirVec.normalize();

	gameObject->SetSpeed(speed);
	gameObject->SetDirVec(setDirVec);

	Game::GetInstance()->GetObject(m_position, "PowerNoteStartBoom");
}
void NoteShooter::SetIdle()
{
	m_animation->SetProp("noteShooter_stage1_idle_sprite", 0, 0, 2);

	m_animation->StartAnimation(); 
	m_animation->SetAnimPause(false);
}
void NoteShooter::SetPop()
{
	m_animation->SetProp("noteShooter_stage1_pop_sprite", 0.01f, 0, 6);

	m_animation->SetAnimPause(true);
	m_animation->AnimationOnce(); //Æ®¸®°Å 
}
