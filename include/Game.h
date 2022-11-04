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
#include <Player.h>
#include <HealthBar.h>
//Controller
#include <InputHandler.h>
//#include <PlayController.h>
//Only ObjectPool
#include <Note.h>
#include <PowerNote.h>
#include <NoteBoom.h>

#define SCREEN_WIDTH 1536
#define SCREEN_HEIGHT 1080

#define MAX_HP 50;
#define MAX_ENERGY 50;

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

	const int max_Hp = MAX_HP;
	const int max_Energy = MAX_ENERGY;
	int hp = max_Hp;
	int energy = max_Energy;
 
	//MainCharacter 
	Player* player = new Player(new LoaderParams(0, 0, 240, 240, 0, 0, "mainCharacter_sprite"));
	//HpSet
	SDLGameObject* hpBar_Back = new SDLGameObject(new LoaderParams(0, 0, 48, 192, 1, 0, "healthBarPack_sprite"));
	HealthBar* hpBar = new HealthBar(new LoaderParams(0, 0, 48, 192, 0, 0, "healthBarPack_sprite"), "HpBar", 12);
	HealthBar* energyBar = new HealthBar(new LoaderParams(0, 0, 48, 192, 2, 0, "healthBarPack_sprite"), "EnergyBar", 1);
	//HealthBar* energyBar = new HealthBar(new LoaderParams(0, 0, 48, 192, 0, 0, "healthBarPack_sprite"));

	//NotePads
	NotePad* notePad = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 0, "notesPad_sprite"), "Note");
	NotePad* notePad1 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 1, "notesPad_sprite"), "Note");
	NotePad* notePad2 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 2, "notesPad_sprite"), "Note");
	NotePad* notePad3 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 3, "notesPad_sprite"), "Note");
	//PowerNotePads
	NotePad* powerNotePad1 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 0, "powerNotesPad_sprite"), "PowerNote");
	NotePad* powerNotePad2 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 0, "powerNotesPad_sprite"), "PowerNote");
	//NoteShooter
	NoteShooter* NoteShooter1 = new NoteShooter(new LoaderParams(0, 0, 192, 192, 0, 0, "noteShooter_stage1_idle_sprite"));
	//NoteShooter* NoteShooter3 = new NoteShooter(new LoaderParams(0, 0, 144, 144, 0, 3, "notesPad_sprite"));
	//Back
	GameObject* back_stage1 = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "stage1_sprite"));
	GameObject* back_stage1_back1 = new SDLGameObject(new LoaderParams(0, 0, 384, SCREEN_HEIGHT, 0, 0, "stage1_back_sprite"));
	GameObject* back_stage1_back2 = new SDLGameObject(new LoaderParams(0, 0, 384, SCREEN_HEIGHT, 0, 1, "stage1_back_sprite"));

	//GameObject* back2 = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "stage1_sprite"));

	vector<GameObject*> m_gameObjects;
	//object Manage
	vector<GameObject*> collisionObjects; //충돌할 수 있는 오브젝트 
	map<const char*, vector<GameObject* >> objects; //모든 오브젝트

	void GameOver();
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
	void Awake();

	void render();
	void update();
	bool running();
	void handleEvents();

	void clean();
	void quit() { m_bRunning = false; }

	//Input
	void handleInput();
	void Input_Play();
	void Input_Menu() {}

	//else
	//void DhrowBorder();
	vector<GameObject*> GetColliders() { return collisionObjects; }

	//ObjectPool
	void InitPool(); //풀에 오브젝트를 집어넣고, game에 내보내는 역할 
	GameObject* CreateObjects(const char* tag);
	GameObject* GetObject(Vector2D spawnPos, const char* name);
	void ReturnPool(const char name[20], GameObject* getGameObject) { objects[name].emplace_back(getGameObject); }

	//Hp, Energy
	int GetHp() { return hp; }
	void DamagedHp(int damagedHp) 
	{
		if (hp - damagedHp < 0) { hp = 0; }
		else { hp -= damagedHp; }
	}
	void HealHp(int heal) 
	{
		if (hp + heal > max_Hp) { hp = MAX_HP; }
		else { hp += heal; }
	}

	int GetEnergy() { return energy; }
	void DamagedEnergy(int damagedEnergy)
	{
		if (energy - damagedEnergy < 0) { energy = 0; }
		else { energy -= damagedEnergy; }
	}
	void HealEnergy(int heal)
	{
		if (energy + heal > max_Energy) { hp = MAX_ENERGY; }
		else { energy += heal; }
	}

	/*void DamagedEnergy(int damagedEnergy) { energy -= damagedEnergy; }
	void HealEnergy(int heal) { energy += heal; }*/
};

//enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
//enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };
