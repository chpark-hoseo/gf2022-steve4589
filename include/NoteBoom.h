#pragma once
#include <SDLGameObject.h>
#include <Vector2D.h>
#include <Animation.h>

class NoteBoom : public SDLGameObject
{
public :
	NoteBoom(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}

	//make if interface?
	void Animation_Once() { startTimer = SDL_GetTicks(); }
private :
	Uint32 startTimer;
	void OnEnable() override { Animation_Once(); }
	void OnDisable() override;
	void AnimationState();

	Animation* m_animation = new Animation();
};