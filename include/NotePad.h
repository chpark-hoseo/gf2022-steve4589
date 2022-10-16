#pragma once
#include <SDLGameObject.h>

//need for A+_notesPad
class NotePad : public SDLGameObject //public ICLICK
{
private:
	bool isCrash = false;
	//SpecialNotesPad
public:
	NotePad(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void ChangeSprites(bool isCrash)
	{

	}
	void Collision2D()
	{

	}
};