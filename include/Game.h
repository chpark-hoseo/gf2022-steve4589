#pragma once
//Basic
#include "iostream"
#include "string.h"
#include "algorithm"
#include <list>
//SDL
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
//Manager
#include <NoteManager.h>
#include <TextureManager.h>
//GameObject
#include <GameObject.h>
//Controller
#include <InputHandler.h>
//#include <PlayController.h>
//Only ObjectPool
#include <Note.h>
#include <PowerNote.h>
#include <NoteBoom.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800

typedef TextureManager TheTextureManager; //�ڷ��� ��Ī ����

class Pool //������ �ٸ� ���ӿ�����Ʈ�� �����ϱ� ���� ����üó�� ����մϴ�
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
	//object Manage
	vector<GameObject*> collisionObjects; //�浹�� �� �ִ� ������Ʈ 
	map<const char*, vector<GameObject* >> objects; //��� ������Ʈ
	//NotePads
	NotePad* notePad = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 0, "notesPad_sprite"));
	NotePad* notePad1 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 1, "notesPad_sprite"));
	NotePad* notePad2 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 2, "notesPad_sprite"));
	NotePad* notePad3 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 3, "notesPad_sprite"));
	//Back
	GameObject* back1 = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "stage1_sprite"));

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
	//Input
	void handleInput();
	void Input_Note();
	void Input_Menu() {}
	//else
	void DhrowBorder();
	vector<GameObject*> GetColliders() { return collisionObjects; } 

	//ObjectPool
	void InitPool(); //Ǯ�� ������Ʈ�� ����ְ�, game�� �������� ���� 
	GameObject* CreateObjects(const char* tag);
	GameObject* GetObject(Vector2D spawnPos, const char* name);
	void ReturnPool(const char name[20], GameObject* getGameObject) { objects[name].emplace_back(getGameObject); }
};

//enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
//enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };
