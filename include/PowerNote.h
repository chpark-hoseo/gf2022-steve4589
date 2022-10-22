#pragma once
#include <SDLGameObject.h>

class PowerNote : public SDLGameObject, public INoteType
{
public :
	PowerNote(const LoaderParams* pParams);
	virtual void draw() {}
	virtual void update() {}
	virtual void clean() {}
private :
private:
	void OnEnable() override {}
	void OnDisable() override {}

	void move() override {}
};