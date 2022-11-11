#pragma once
class TemplateButton //≈€«√∏¥ ∆–≈œ
{
public :
	virtual void IsPressed(bool _isPush) { PressIn(_isPush); }

	void PressIn(bool isPress)
	{
		if (!isPressIn) return;
		isPressIn = false;
		isPressOut = true;

		PressInAct();
	}
	void PressOut(bool isPress)
	{
		if (!isPressOut) return;
		isPressOut = false;
		isPressIn = true;

		PressOutAct();
	}
	virtual void PressInAct() = 0;
	virtual void PressOutAct() = 0;
private:
	bool isPressIn = true;
	bool isPressOut = false;
};
