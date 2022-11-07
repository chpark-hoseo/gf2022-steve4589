#pragma once
#include <SDL2/SDL.h>
#include <GameState.h>

class State_StartLogo : public GameState
{
public:
	virtual void Awake();

	virtual void render();
	virtual void update();
	virtual bool running();
	virtual void handleEvents();

	virtual void clean();
	virtual void quit();

	//Input
	virtual void handleInput();

private:
	SDL_Renderer* m_Renderer;
};