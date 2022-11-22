#include <LerpPanel.h>
#include <CustomPhysics.h>

LerpPanel::LerpPanel(const LoaderParams* pParams, coro_handle handle) : SDLGameObject(pParams), m_handle(handle)
{
	std::cout << pParams->getHeight();
	Fadeout();
}

void LerpPanel::draw()
{
	if (!onOff) return;
	SDLGameObject::draw();
}

void LerpPanel::update()
{
	if (!onOff) return;
	std::cout << timer.getTimer() << "\n";
	timer.StartTimer();
}