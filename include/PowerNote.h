#pragma once
#include <SDLGameObject.h>

class PowerNote : public SDLGameObject, public INoteType
{
public:
	PowerNote(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

private:
	void OnDisable() override;

	void move() override;

	Vector2D disPos = Vector2D(0, 0); 
};