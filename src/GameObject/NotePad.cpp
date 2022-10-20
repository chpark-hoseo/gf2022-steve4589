#include <NotePad.h>

NotePad::NotePad(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NotePad::update() {}

void NotePad::SetPosition(Vector2D getPos) 
{
	SDLGameObject::SetPosition(getPos);
	collision.SetPosition(m_position.getX(), m_position.getY(), m_width, m_height);
}

void NotePad::PressIn(bool isPress)
{
	if (!isPressIn) return;
	isPressIn = false;
	isPressOut = true;

	std::cout << "   " << m_position.getX();
	UpdateColliderData();
	//collision.CollisionEnder();

	m_currentRow = isPress;
}
void NotePad::PressOut(bool isPress)
{
	if (!isPressOut) return;
	isPressOut = false;
	isPressIn = true;

	m_currentRow = isPress;
}