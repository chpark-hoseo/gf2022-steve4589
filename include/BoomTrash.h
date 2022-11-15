#pragma once
#include <SDLGameObject.h>
#include <DirShot.h>

class BoomTrash : public SDLGameObject
{
public:
	BoomTrash(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

private:
	void OnDisable() override;

	void move();

	Vector2D disPos = Vector2D(0, 0);
};