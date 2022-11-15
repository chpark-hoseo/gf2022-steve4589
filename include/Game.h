#pragma once
//Basic
#include "iostream"
#include "string.h"
#include <vector>
//SDL
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 1536
#define SCREEN_HEIGHT 1080

class GameState;

class Game
{
private:
	static Game* s_pInstance;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_Texture* m_pTexureText;
	SDL_Rect m_RectText;

	TTF_Font* g_pFont;
	/*static*/ Mix_Chunk* g_pChunk;

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

	TTF_Font* getFont() const { return g_pFont; }

	SDL_Texture* getTextureText() const { return m_pTexureText; }

	/* Main Frame */
	bool init(const char* title, int, int, int, int, int flags);

	void render();
	void update();
	bool running();
	void handleEvents();

	void clean();

	void quit()
	{
		Mix_CloseAudio();
		Mix_Quit();
		TTF_CloseFont(g_pFont);
		TTF_Quit();
		SDL_Quit();
	}

	void PopState();
	void PushState(GameState*);
	void ChangeState(GameState*);

	std::vector<GameState*> m_gameStates;
};

//enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
//enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };
