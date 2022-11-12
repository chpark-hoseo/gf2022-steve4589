#include <NormalButton.h>

NormalButton::NormalButton(const LoaderParams* pParams, StageController* controller, bool upDown) : SDLGameObject(pParams)
{
	stageController = controller;
	isUpDown = upDown;
}

void NormalButton::PressInAct()
{
	stageController->NextPreviousMusic(isUpDown);
	m_currentRow = 1;
}