#pragma once
//Basic
#include "iostream"
#include "string.h"
#include "algorithm"
//SDL
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
//Custom
#include <NoteManager.h>
#include <TextureManager.h>
#include <ObjManager.h>
#include <Timer.h>
#include <Note.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800

typedef TextureManager TheTextureManager; //�ڷ��� ��Ī ����

class SDLGameObject; //SDLGameObject.h�� ���������� �Ǽ� �̷����߽��ϴ� 
class GameObject; //SDLGameObject.h�� ���������� �Ǽ� �̷����߽��ϴ� 
class Game
{
public:
	GameObject* gameObject;
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
	/* Main Frame */
	bool init(const char* title, int, int, int, int, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();
	void Prepare();

	/* Initialized */
	void Start_initialize();
	//else
	void DhrowBorder();
private:
	static Game* s_pInstance;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	SDL_RendererFlip curFlip;

	int transform_x = SCREEN_WIDTH / 2;
	int transform_y = 500;

	int m_curFrame = 0;
	double m_curTime = 0;
	int startTimer;
	bool isTimer = true;

	std::vector<SDLGameObject*> m_gameObjects; //GameManager �迭 ����, main���� ��ü�� ������ ��ȯ���� �ʱ� ����?
};