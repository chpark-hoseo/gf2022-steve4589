#pragma once
#include <SDLGameObject.h>

//need for A+_notesPad
class NotePad : public SDLGameObject //public ICLICK
{
private:
	bool isPressIn = true;
	bool isPressOut = false;
	//SpecialNotesPad
public:
	NotePad(const LoaderParams* pParams);
	virtual void draw() { SDLGameObject::draw(); }
	virtual void update();
	virtual void clean() {}

	//Interface
	void PressIn(bool);
	void PressOut(bool);
	void IsPressed(bool _isPush)
	{
		PressIn(_isPush);
	}

	void Collision2D()
	{

	}
};