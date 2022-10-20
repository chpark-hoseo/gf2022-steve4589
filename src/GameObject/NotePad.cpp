#include <NotePad.h>

NotePad::NotePad(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NotePad::update() {}
void NotePad::SetPosition(Vector2D getPos)
{
	SDLGameObject::SetPosition(getPos);
	collision.SetPosition(m_position.getX(), m_position.getY(), m_width, m_height);
}

void NotePad::PressIn(bool isPress) //누른순간 for문으로 collisionObject에 있는 애들을 넘겨주기  
{
	if (!isPressIn) return;
	isPressIn = false;
	isPressOut = true;

	collision.OnCollision2D();

	m_currentRow = isPress;
}
void NotePad::PressOut(bool isPress)
{
	if (!isPressOut) return;
	isPressOut = false;
	isPressIn = true;

	m_currentRow = isPress;
}
void NotePad::UpdateCollider()
{

}