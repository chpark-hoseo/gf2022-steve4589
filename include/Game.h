#pragma once
//Animation
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include "NoteManager.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 640

//enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
//enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };

enum State {
	idle = 0,
	walk,
	run,
};
typedef struct Sprite
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect m_sourceRectangle; //원본 사각형
	SDL_Rect m_destinationRectangle; //대상 사각형
}sprite;

class Game
{
public:
	Game() { }
	~Game() { }
	//프레임 
	bool init(const char* title, int, int, int, int, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();
	//초기화 
	void Start_initialize();

	Sprite* GetSprite(const char*, int x, int y, int w, int h);
	void MainMove(State curState);
	void DhrowBorder();
	void MainAnimation(State state);

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	SDL_Texture* m_pTexture;
	SDL_Texture* ui_pTexture;
	SDL_Rect m_sourceRectangle; //원본 사각형
	SDL_Rect m_destinationRectangle; //대상 사각형
	//실제 게임 만들땐 꼭 동적 생성하기 
	Sprite* sprite;
	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	Sprite* sprite4;

	SDL_RendererFlip curFlip;
	State curState = idle;
	int xInterval = 1;

	int transform_x = SCREEN_WIDTH / 2;
	int transform_y = 500;
};