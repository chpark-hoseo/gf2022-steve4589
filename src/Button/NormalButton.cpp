#include <NormalButton.h>
#include <State_Play.h>
#include <SoundEffect.h>

NormalButton::NormalButton(const LoaderParams* pParams, StageController* controller, bool upDown) : SDLGameObject(pParams)
{
	stageController = controller;
	isUpDown = upDown;
}

void NormalButton::PressInAct()
{
	if (onOff == false) return;
	dynamic_cast<SoundEffect*>(State_Play::GetInstance()->GetObject(Vector2D(0, 0), "SoundEffect"))->SoundSFX("pop");
	stageController->NextPreviousMusic(isUpDown);
	m_currentRow = 1;
}