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

	//Input
	virtual void handleInput() = 0;

	void ChangeState(Game* game,
		GameState* state) {
		game->ChangeState(state);
	}
protected:
	TTF_Font* g_pFont;
	Mix_Chunk* g_pChunk;

	SDL_Texture* m_pTexureText;
	SDL_Rect m_RectText;
};