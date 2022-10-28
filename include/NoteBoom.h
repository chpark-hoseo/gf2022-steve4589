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
	Animation* m_animation = new Animation();

	void OnEnable() override 
	{ 
		Animation_Once();
		/*m_animation->SetProp(m_textureID, 0.01f, 0, 6, true);*/ 
	}
	void OnDisable() override;
	void OnceAnimation();
};