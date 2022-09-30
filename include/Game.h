#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <TextureManager.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

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

	bool init(const char* title, int, int, int, int, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();

	void DhrowBorder();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	TextureManager m_textureManager;
	int m_currentFrame;
};