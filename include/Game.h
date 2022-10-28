#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <TextureManager.h>
#include <Player.h>
#include <Monster.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

typedef TextureManager TheTextureManager; //자료형 별칭 생성

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

	//void DhrowBorder();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	GameObject m_go;

	Player m_player;
	Monster m_Monster;
	Monster m_Monster1;

	int m_currentFrame;
};