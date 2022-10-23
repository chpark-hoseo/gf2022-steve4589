#include <NotePad.h>
#include <Game.h>

NotePad::NotePad(const LoaderParams* pParams) : SDLGameObject(pParams) {}

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
	EntergameObject = collision.OnCollision2D();
	//Exit
	vector <GameObject*> ExitgameObject = collision.OnCollisionExit2D();

	for (int i = 0; i < ExitgameObject.size(); i++)
	{
		if (ExitgameObject[i]->activeSelf())
		{ 
			std::cout << ExitgameObject[i] << "        Size         \n";
			Game::GetInstance()->GetObject(ExitgameObject[i]->GetPosition(), "WinBoom");
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