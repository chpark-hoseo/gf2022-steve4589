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
	void OnEnable() override;
	void OnDisable() override;

	void move() override;
	void SetShotPos();
	void SetStartPos(Vector2D getPos) { disPos = getPos; }

	Vector2D dirVec = Vector2D(0, 0);
	Vector2D disPos = Vector2D(0, 0); 
};