#pragma once
#include <SDLGameObject.h>

class Note : public SDLGameObject, public INoteType
{
public:
	Note(const LoaderParams* pParams, const char* name);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

private:
	void OnDisable() override;

	void move() override;
};
