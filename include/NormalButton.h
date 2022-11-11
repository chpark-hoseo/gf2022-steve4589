#pragma once
#include <TemplateButton.h>
#include <SDLGameObject.h>

class StageController;

class NormalButton : public SDLGameObject, public TemplateButton
{
public:
	NormalButton(const LoaderParams* pParams, StageController * stageController);/*, StageController * controller*/
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update() {}
	virtual void clean() {}

	virtual void IsPressed(bool isPress) { PressIn(isPress); }
	//TemplateButton
	virtual void PressInAct()
	{
		//stageController->NextMusic();
		m_currentRow = 1;
	}
	virtual void PressOutAct() { m_currentRow = 0; };
private:
	StageController* stageController;
};