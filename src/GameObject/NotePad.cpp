#include <NotePad.h>
NotePad::NotePad(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void NotePad::update()
{

}

void NotePad::PressIn(bool isPress)
{
	if (!isPressIn) return;
	isPressIn = false;
	isPressOut = true;

	m_currentRow = isPress;
}
void NotePad::PressOut(bool isPress)
{
	if (!isPressOut) return;
	isPressOut = false;
	isPressIn = true;

	m_currentRow = isPress;
}