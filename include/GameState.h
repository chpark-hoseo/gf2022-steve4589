#pragma once
#include <SDL2/SDL.h>
#include <Game.h>

class GameState
{
public:
	//virtual bool init(const char* title, int, int, int, int, int flags) = 0;
	virtual void Awake() = 0;

	virtual void render(Game* game) = 0;
	virtual void update(Game* game) = 0;
	virtual void handleEvents(Game* game) = 0;

	virtual void clean() = 0;
	virtual void quit() = 0;

	//Input
	virtual void handleInput() = 0;

	void ChangeState(Game* game,
		GameState* state) {
		game->ChangeState(state);
	}
};