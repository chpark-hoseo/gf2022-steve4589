#include <NotePad.h>
#include <Game.h>

NotePad::NotePad(const LoaderParams* pParams, string noteTag) : SDLGameObject(pParams) { getTag = noteTag; }

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
			Game::GetInstance()->GetObject(ExitgameObject[i]->GetPosition(), "BoomTrashA");
			Game::GetInstance()->GetObject(ExitgameObject[i]->GetPosition(), "MissBoom");
			ExitgameObject[i]->SetActive(false);
		}
	}
}
//Button
void NotePad::PressIn(bool isPress)   
{
	if (!isPressIn) return;
	isPressIn = false;
	isPressOut = true;

	OffNote();

	m_currentRow = isPress;
}
void NotePad::PressOut(bool isPress)
{
	if (!isPressOut) return;
	isPressOut = false;
	isPressIn = true;

	m_currentRow = isPress;
}
void NotePad::OffNote()
{
	if (EntergameObject != NULL)
	{
		Game::GetInstance()->GetObject(EntergameObject->GetPosition(), "WinBoom");
		EntergameObject->SetActive(false);
	}
}