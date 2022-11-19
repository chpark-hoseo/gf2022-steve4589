#include <SpaceButton.h>
#include <StageController.h>

SpaceButton::SpaceButton(const LoaderParams* pParams, StageController* controller) : SDLGameObject(pParams) { stageController = controller; }

void SpaceButton::PressInAct()
{
	if (onOff == false) return;
	stageController->SelectMusic();
	m_currentFrame = 1;
}
void SpaceButton::PressOutAct()
{
	if (onOff == false) return;
	m_currentFrame = 0;
}
