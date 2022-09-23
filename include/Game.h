﻿#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

	bool init(const char* title, int, int, int, int, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();
	Sprite* GetSprite(const char*, int x, int y, int w, int h);
	void MoveSprite();
	void DhrowBorder();
	void MoveSprite(int width);

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
	int xInterval = 1;
	int tick = 0;;
};