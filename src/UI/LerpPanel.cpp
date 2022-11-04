#include <LerpPanel.h>
#include <CustomPhysics.h>

LerpPanel::LerpPanel(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	Timer::GetInstance()->WaitTime();
	SetActive(false); 
}

void LerpPanel::draw()
{
	SDLGameObject::draw();
}

void LerpPanel::update()
{
	if (!onOff) return;

	//float a = CustomPhysics::GetInstance() -> Lerp(1, 50, 25);
	//std::cout << a << "::";
	//curTime = Timer::GetInstance()->StartTimer();
	SDLGameObject::update();
}