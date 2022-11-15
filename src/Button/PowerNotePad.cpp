#include <PowerNotePad.h>
#include <State_Play.h>

PowerNotePad::PowerNotePad(const LoaderParams* pParams, string thisTag, string noteTag) : SDLGameObject(pParams)
{
	getTag = noteTag;
	tag = thisTag;
}

void PowerNotePad::update()
{
	if (onOff == false) return;
	DetectCollider();
}
void PowerNotePad::SetPosition(Vector2D getPos)
{
	SDLGameObject::SetPosition(getPos);
	collision.SetPosition(m_position.getX(), m_position.getY() - 15, m_width, m_height - 95);
}

//Collider
void PowerNotePad::DetectCollider()
{
	bool isDetect = false;
	//Enter
	EntergameObject = collision.OnCollision2D(getTag);
	//Exit
	vector <GameObject*> ExitgameObject = collision.OnCollisionExit2D(getTag);

	for (int i = 0; i < ExitgameObject.size(); i++)
	{
		if (ExitgameObject[i]->activeSelf())
		{
			State_Play::GetInstance()->GetObject(ExitgameObject[i]->GetPosition(), "MissBoom");
			ExitgameObject[i]->SetActive(false);

			State_Play::GetInstance()->DamagedEnergy(17);
		}
	}
}
bool PowerNotePad::OffNote()
{
	bool isDetect = false;
	if (EntergameObject != NULL)
	{
		State_Play::GetInstance()->HealEnergy(2);
		State_Play::GetInstance()->GetObject(EntergameObject->GetPosition(), "WinBoom");
		EntergameObject->SetActive(false);

		isDetect = true;
	}
	return isDetect;
}