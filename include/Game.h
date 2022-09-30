#pragma once
//Animation
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include "NoteManager.h"
#include <TextureManager.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

typedef TextureManager TheTextureManager; //자료형 별칭 생성

//enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
//enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };

class Game
{
public:
	Game() { }
	~Game() { }
	/* Main Frame */
	bool init(const char* title, int, int, int, int, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();

	/* Initialized */
	void Start_initialize();

	void DhrowBorder();
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	SDL_RendererFlip curFlip;

	int transform_x = SCREEN_WIDTH / 2;
	int transform_y = 500;

	int m_curFrame = 0;
	float m_curTime = 0;
};