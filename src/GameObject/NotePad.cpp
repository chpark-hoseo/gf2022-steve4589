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
void NotePad::DetectCollider()
{
	//Enter
	EntergameObject = collision.OnCollision2D();
	//Exit
	
	GameObject* ExitgameObject = collision.OnCollisionExit2D();

	if (ExitgameObject != NULL)
	{
		Game::GetInstance()->GetObject(ExitgameObject->GetPosition(), "WinBoom");
		ExitgameObject->SetActive(false);
	}
}
void NotePad::PressIn(bool isPress) //누른순간 for문으로 collisionObject에 있는 애들을 넘겨주기  
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