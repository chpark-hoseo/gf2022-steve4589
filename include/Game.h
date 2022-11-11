#pragma once
//Basic
#include "iostream"
#include "string.h"
#include <vector>
//SDL
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1536
#define SCREEN_HEIGHT 1080

class GameState;

class Game
{
private:
	static Game* s_pInstance;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	SDL_RendererFlip curFlip;

public:
	Game() { }
	~Game() { }

	static Game* GetInstance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }

	/* Main Frame */
	bool init(const char* title, int, int, int, int, int flags);

	void render();
	void update();
	bool running();
	void handleEvents();

	void clean();

	void quit() { m_bRunning = false; }

	void PopState();
	void PushState(GameState*);
	void ChangeState(GameState*);

	std::vector<GameState*> m_gameStates;
};

//enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
//enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };
