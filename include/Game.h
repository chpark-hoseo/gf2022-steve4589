#pragma once
//Basic
#include "iostream"
#include "string.h"
#include "algorithm"
#include <list>
//SDL
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
//Custom
#include <NoteManager.h>
#include <TextureManager.h>
#include <Timer.h>
#include <GameObject.h>
#include <InputHandler.h>
//Only ObjectPool
#include <Note.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800

typedef TextureManager TheTextureManager; //자료형 별칭 생성

class Pool //각각의 다른 게임오브젝트를 구별하기 위한 구조체처럼 사용합니다
{
public:
	Pool(const char name[20], int size) : m_name(name), m_size(size) {}
	const char* m_name;
	int m_size;
};

class Game
{
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

	vector<GameObject*> m_gameObjects;
	map<const char*, vector<GameObject* >> objects; //모든 오브젝트
public:
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
	void Prepare();

	void render();
	void update();
	bool running();
	void handleEvents();

	void clean();
	void quit() { m_bRunning = false; }

	/* Initialized */
	void Start_initialize();
	//else
	void DhrowBorder();

	//ObjectPool
	void InitPool(); //풀에 오브젝트를 집어넣고, game에 내보내는 역할 
	GameObject* CreateObjects(const char* tag);
	GameObject* GetObject(Vector2D spawnPos, const char* name);
	void ReturnPool(const char name[20], GameObject* getGameObject) {  objects[name].emplace_back(getGameObject); }; 
};

//enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
//enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };
