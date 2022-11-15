#include <NoteShooter.h>
#include <State_Play.h>
#include <PowerNote.h>

NoteShooter::NoteShooter(const LoaderParams* pParams, vector<NoteShooter *> noteShooters) : SDLGameObject(pParams)
{
	m_animation->SetProp(m_textureID, 0.01f, m_currentRow, 2);
	m_animation->SetAnimPause(false);

	noteShooters.emplace_back(this);
}

void NoteShooter::draw()
{
	if (!onOff) return;
	m_animation->Draw(m_position.getX(), m_position.getY(), m_width, m_height);
}
void NoteShooter::update()
{
	if (!onOff) return;

	m_animation->Update();
	SDLGameObject::update();
}
void NoteShooter::Shot(float speed, Vector2D disPos) { dirShot(speed, m_position, disPos, "PowerNote"); }
void NoteShooter::dirShotAct() 
{
	State_Play::GetInstance()->GetObject(m_position, "PowerNoteStartBoom");
	SetPop();
}

void NoteShooter::SetIdle()
{
	m_animation->SetProp(m_textureID, 0.01f, m_currentRow, 2);

	m_animation->SetAnimPause(false);
	m_animation->StartAnimation(); 
}
void NoteShooter::SetPop()
{
	m_animation->SetProp("noteShooter_stage1_pop_sprite", 0.01f, 0, 6);

	m_animation->SetAnimPause(true);

	m_animation->AnimationOnce(true); //Æ®¸®°Å 
	m_animation->StartAnimation();
}
