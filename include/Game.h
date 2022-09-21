#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct Sprite
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect m_sourceRectangle; //���� �簢��
	SDL_Rect m_destinationRectangle; //��� �簢��
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
	void DhrowBorder();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	SDL_Texture* m_pTexture;
	SDL_Texture* ui_pTexture;
	SDL_Rect m_sourceRectangle; //���� �簢��
	SDL_Rect m_destinationRectangle; //��� �簢��

	Sprite* sprite;
	Sprite* sprite1;

	int xInterval = 1;
};