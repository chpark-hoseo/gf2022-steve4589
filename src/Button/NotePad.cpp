#include <NotePad.h>
#include <State_Play.h>
#include <algorithm>
#include <ScoreManager.h>
#include <SoundEffect.h>

NotePad::NotePad(const LoaderParams* pParams, string thisTag, string noteTag) : SDLGameObject(pParams)
{
	getTag = noteTag;
	tag = thisTag;
}

void NotePad::update()
{
	DetectCollider();
}
void NotePad::SetPosition(Vector2D getPos)
{
	SDLGameObject::SetPosition(getPos);
	collision.SetPosition(m_position.getX(), m_position.getY() - 15, m_width, m_height - 95);
}
//Collider
void NotePad::DetectCollider()
{
	//Enter
	EntergameObject = collision.OnCollision2D(getTag);
	//Exit
	vector <GameObject*> ExitgameObject = collision.OnCollisionExit2D(getTag);

	for (int i = 0; i < ExitgameObject.size(); i++)
	{
		if (ExitgameObject[i]->activeSelf())
		{
			Shot("BoomTrashF");
			State_Play::GetInstance()->GetObject(ExitgameObject[i]->GetPosition(), "MissBoom");

			dynamic_cast<SoundEffect*>(State_Play::GetInstance()->GetObject(Vector2D(0, 0), "SoundEffect"))->SoundSFX("miss");

			ExitgameObject[i]->SetActive(false);

			State_Play::GetInstance()->DamagedHp(8);
		}
	}
}
void NotePad::OffNote()
{
	if (EntergameObject != NULL)
	{
		ScoreManager::GetInstance()->AddScore();
		Shot("BoomTrashA");
		dynamic_cast<SoundEffect*>(State_Play::GetInstance()->GetObject(Vector2D(0, 0), "SoundEffect"))->SoundSFX("pop");
		State_Play::GetInstance()->GetObject(EntergameObject->GetPosition(), "WinBoom");
		EntergameObject->SetActive(false);

		State_Play::GetInstance()->HealHp(1);
	}
	else
	{
		ScoreManager::GetInstance()->MinusScore();
		State_Play::GetInstance()->GetObject(playerPos, "PlayerMiss");
		State_Play::GetInstance()->DamagedHp(4);
	}
}
void NotePad::PressInAct()
{
	OffNote();
	m_currentRow = true;
}
void NotePad::PressOutAct()
{
	m_currentRow = false;
}