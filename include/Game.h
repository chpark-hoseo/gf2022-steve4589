#pragma once
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
	Sprite* GetSprite(const char*);
	void MoveSprite();
	void DhrowBorder()
	{
		SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
		//SDL_RenderClear(m_pRenderer);

		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
		SDL_RenderFillRect(m_pRenderer, &fillRect);

		SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
		SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(m_pRenderer, &outlineRect);

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
		SDL_RenderDrawLine(m_pRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

		SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 0, 255);
		for (int i = 0; i < SCREEN_HEIGHT; i += 4)
		{
			SDL_RenderDrawPoint(m_pRenderer, SCREEN_WIDTH / 2, i);
		}
	}

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	SDL_Texture* m_pTexture;
	SDL_Texture* ui_pTexture;
	SDL_Rect m_sourceRectangle; //원본 사각형
	SDL_Rect m_destinationRectangle; //대상 사각형

	Sprite* sprite;
	Sprite* sprite1;

	int xInterval = 1;
};