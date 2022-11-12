#pragma once
#include <TemplateButton.h>
#include <SDLGameObject.h>
#include <StageController.h>

class NormalButton : public SDLGameObject, public TemplateButton
{
public:
	NormalButton(const LoaderParams* pParams, StageController * controller, bool upDown);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update() {}
	virtual void clean() {}

	void NoPassButtonSprite(bool isTrue) 
	{ 
		if (isTrue) m_currentRow = 2;
		else m_currentRow = 0;
	};

	virtual void IsPressed(bool isPress) { PressIn(isPress); }
	//TemplateButton
	virtual void PressInAct();
	virtual void PressOutAct() { m_currentRow = 0; };
private:
	StageController* stageController;

	bool isPass = true;
	bool isUpDown = true;
};