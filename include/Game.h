#pragma once
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <TextureManager.h>
#include <Player.h>
#include <Monster.h>
#include <vector>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

typedef TextureManager TheTextureManager; //자료형 별칭 생성

class Game
{
public:
	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	bool init(const char* title, int, int, int, int, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();

	//void DhrowBorder();

private:
	Game() { }
	~Game() { }

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	int m_currentFrame;

	std::vector<GameObject*> m_gameObjects;

	Player* m_go = new Player(3);
	Player* m_player = new Player(-3); //Monster

	Monster* m_Monster_diagonal = new Monster();
	Monster* m_Monster_swim = new Monster();
	Monster* m_Monster_wave = new Monster();

	static Game* s_pInstance; // 정적 멤버변수 
};
typedef Game TheGame;