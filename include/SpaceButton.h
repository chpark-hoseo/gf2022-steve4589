#pragma once
#include <SDLGameObject.h>
#include <TemplateButton.h>

class StageController;

class SpaceButton : public SDLGameObject, public TemplateButton
{
public:
	SpaceButton(const LoaderParams* pParams, StageController* controller);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update() {}
	virtual void clean() {}

	virtual void IsPressed(bool isPress) { PressIn(isPress); }
	//TemplateButton
	virtual void PressInAct();
	virtual void PressOutAct() {}

	void ReturnSprite() { m_currentFrame = 0; }
private:
	StageController* stageController;
};