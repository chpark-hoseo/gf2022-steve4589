#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum State {
	idle = 0,
	walk,
	run,
};
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
	SDL_Rect m_sourceRectangle; //���� �簢��
	SDL_Rect m_destinationRectangle; //��� �簢��
	//���� ���� ���鶩 �� ���� �����ϱ� 
	Sprite* sprite;
	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	Sprite* sprite4;

	SDL_RendererFlip curFlip;
	State curState = idle;
	int xInterval = 1;
};