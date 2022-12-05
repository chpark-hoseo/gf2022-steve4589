#pragma once
#include <SDL2/SDL.h>
#include <GameState.h>
//Basic
#include "iostream"
#include "string.h"
#include "algorithm"
#include<sstream>
#include <fstream> 
//SDL
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
//Manager
#include <NoteManager.h>
#include <TextureManager.h>
//GameObject
#include <PowerNotePadButton.h>
#include <GameObject.h>
#include <Player.h>
#include <SpaceButton.h>
#include <BoomTrash.h>
//UI
#include <Command.h>
#include <LerpPanel.h>
#include <HealthBar.h>
#include <BackScroll.h>
#include <MusicPanel.h>
//Controller
#include <InputHandler.h>
//Only ObjectPool
#include <Note.h>
#include <PowerNote.h>
#include <NoteBoom.h>
//StageData
#include <StageController.h>
//Timer
#include <Timer.h>

#define MAX_HP 50;
#define MAX_ENERGY 50;

#define SCREEN_WIDTH 1536
#define SCREEN_HEIGHT 1080

class Game;
using namespace std;

struct AllBackGroundsID
{
	string stage_back_spriteID;
	string stage_spriteID;
	string stage_back_frame_spriteID;
}typedef allBackID;

class Pool //각각의 다른 게임오브젝트를 구별하기 위한 구조체처럼 사용합니다
{
public:
	Pool(const char name[20], int size) : m_name(name), m_size(size) {}
	const char* m_name;
	int m_size;
};

class State_Play : public GameState
{
public:
	static State_Play* GetInstance() {
		if (instance == 0) {
			instance = new State_Play();
			return instance;
		}
		return instance;
	}
	virtual void Awake();
	virtual void render(Game* game);
	virtual void update(Game* game);
	virtual void handleEvents(Game* game);
	virtual void clean();

	//Input
	virtual void handleInput();

	void Input_Play();
	void Input_Menu() {}

	void PopState();
	void PushState(GameState*);
	void ChangeState(GameState*);

	//StageStart
	void StateStart();
	void StateEnd();

	//void DhrowBorder();
	vector<GameObject*> GetColliders() { return collisionObjects; }

	//ObjectPool
	void InitPool(); //풀에 오브젝트를 집어넣고, game에 내보내는 역할 
	GameObject* CreateObjects(const char* tag);
	GameObject* GetObject(Vector2D spawnPos, const char* name);
	void ReturnPool(const char name[20], GameObject* getGameObject) { objects[name].emplace_back(getGameObject); }
	void OffObjects()
	{
		for (GameObject* gameObject : allObjects)
		{
			if (gameObject->activeSelf()) gameObject->SetActive(false);
		}
	}
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
		if (energy - damagedEnergy < 0)
		{
			player->PanicOn();
			isKeyStop = true;
			energy = 0;
		}
		else { energy -= damagedEnergy; }
	}
	void HealEnergy(int heal)
	{
		if (energy + heal > max_Energy) { energy = MAX_ENERGY; }
		else { energy += heal; }
	}

	void OnOffStageSetting(bool onOff)
	{
		if (onOff)
		{
			OnOffStage_Main_Objects(false);
			OnOffStage_Play_Objects(true);
		}
		else
		{
			OnOffStage_Main_Objects(true);
			OnOffStage_Play_Objects(false);

			//for (NoteShooter* noteShooter : noteShooters) { noteShooter->SetIdle(); }
		}
		player->PosTrigger(onOff);
	}
	void OnOffStage_Main_Objects(bool onOff)
	{
		musicSelect->SetActive(onOff);
		musicSelect_music->SetActive(onOff);
		mainScore_grade->SetActive(onOff);

		normalButton1->SetActive(onOff);
		normalButton2->SetActive(onOff);
		spaceButton1->SetActive(onOff);
	}
	void OnOffStage_Play_Objects(bool onOff)
	{
		hpBar_Back->SetActive(onOff);
		hpBar->SetActive(onOff);
		energyBar->SetActive(onOff);

		notePad->SetActive(onOff);
		notePad1->SetActive(onOff);
		notePad2->SetActive(onOff);
		notePad3->SetActive(onOff);

		powerNotePad1->SetActive(onOff);
		powerNotePad2->SetActive(onOff);

		playScore_grade->SetActive(onOff);
	}

	void StageStart(string stageName);
	void StageEnd();

	//::작동 방식::Fade패널은 생성될때 코루틴 함수를 작동시킵니다, Fade패널을 삭제하고 다시 생성해 FadeOutIn 합니다
	//함수내 코루틴 함수를 작동시키고자 했지만, 호출된 함수 외부에서 코루틴을 재개할 방법을 못찾았습니다
	//c++ 코루틴 관련해서 자료를 더 찾아봤지만 전부 main문 내에서 호출하는 코드밖에 못봐서 
	//어쩔 수 없이 삭제하고 생성해서 재작동하게 만들었습니다 

	//Notice : 코루틴 함수내의 m_handle을 삭제해야 하는데 무슨 이유에선지 삭제되지 않아서
	//시간상 이번 게임에서는 초기화하지 않았습니다
	void FadeOutIn(float fadeOut, float fadeIn /*, float fadeIn*/) 
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			if (m_gameObjects[i]->getTag() == "FadeOut")
			{
				m_gameObjects.erase(m_gameObjects.begin() + i);
				std::cout << "FadeOut 삭제\n";
				break;
			}
		}
		delete lerpPanel;
		lerpPanel = new LerpPanel(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "fadePanel_sprite"), fadeOut, fadeIn);
		m_gameObjects.emplace_back(lerpPanel);
	}
	void SetKeyStop(bool onOff) { isKeyStop = onOff; }

private:
	SDL_Renderer* m_pRenderer = Game::GetInstance()->getRenderer();
	SDL_Window* m_pWindow = Game::GetInstance()->getWindow();
	SDL_RendererFlip curFlip;

	static State_Play* instance;

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

	bool isStageStart = false;
	bool isStageEnd = false;
	bool isKeyStop = false;

	//StateData
	string stageName = "";
	//MainCharacter 
	Player* player = new Player(new LoaderParams(0, 0, 240, 240, 0, 0, "mainCharacter_sprite"));
	//HpSet
	SDLGameObject* hpBar_Back = new SDLGameObject(new LoaderParams(0, 0, 48, 192, 1, 0, "healthBarPack_sprite"));
	HealthBar* hpBar = new HealthBar(new LoaderParams(0, 0, 48, 192, 0, 0, "healthBarPack_sprite"), "HpBar", 12);
	HealthBar* energyBar = new HealthBar(new LoaderParams(0, 0, 48, 192, 2, 0, "healthBarPack_sprite"), "EnergyBar", 1);

	//NotePads
	NotePad* notePad = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 0, "notesPad_sprite"), "NotePad", "Note");
	NotePad* notePad1 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 1, "notesPad_sprite"), "NotePad", "Note");
	NotePad* notePad2 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 2, "notesPad_sprite"), "NotePad", "Note");
	NotePad* notePad3 = new NotePad(new LoaderParams(0, 0, 144, 144, 0, 3, "notesPad_sprite"), "NotePad", "Note");
	//PowerNotePads
	PowerNotePad* powerNotePad1 = new PowerNotePad(new LoaderParams(0, 0, 144, 144, 0, 0, "powerNotesPad_sprite"), "PowerNotePad", "PowerNote");
	PowerNotePad* powerNotePad2 = new PowerNotePad(new LoaderParams(0, 0, 144, 144, 0, 0, "powerNotesPad_sprite"), "PowerNotePad", "PowerNote");
	PowerNotePadButton* powerNotePadButton = new PowerNotePadButton(2, powerNotePad1, powerNotePad1, powerNotePad2);
	//NoteShooter
	NoteShooter* NoteShooter1 = new NoteShooter(new LoaderParams(0, 0, 192, 192, 0, 0, "noteShooter_stage1_idle_sprite"), noteShooters);
	//Backs  selectMenu_music_sprite
	SDLGameObject* back_stage1 = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "stage1_sprite"));
	SDLGameObject* back_stage_back1 = new SDLGameObject(new LoaderParams(0, 0, 384, SCREEN_HEIGHT, 0, 0, "stage1_back_sprite"));
	SDLGameObject* back_stage_back2 = new SDLGameObject(new LoaderParams(0, 0, 384, SCREEN_HEIGHT, 0, 1, "stage1_back_sprite")); //stage1_back_frame_sprite
	//BackFrame, UI
	SDLGameObject* back_stage_back_frame = new SDLGameObject(new LoaderParams(0, 0, 1152, 432, 0, 0, "stage1_back_frame_sprite"));
	SDLGameObject* back_stage_back_frame1 = new SDLGameObject(new LoaderParams(0, 0, 1152, 432, 0, 1, "stage1_back_frame_sprite"));
	SDLGameObject* back_stage_back_frame2 = new SDLGameObject(new LoaderParams(0, 0, 1152, 432, 0, 2, "stage1_back_frame_sprite"));
	SDLGameObject* musicSelect_music = new SDLGameObject(new LoaderParams(0, 0, 672, 384, 0, 0, "selectMenu_music_sprite"));

	LerpPanel* lerpPanel = new LerpPanel(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "fadePanel_sprite"), 0, 0);
	SDLGameObject* gameOverPanel = new SDLGameObject(new LoaderParams(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, "fadePanel_sprite"));

	MusicPanel* musicSelect = new MusicPanel(new LoaderParams(0, 0, 720, 720, 0, 0, "selectMenu_sprite"));
	BackScroll* backScroll = new BackScroll(new LoaderParams(0, 0, 0, 0, 0, 0, ""), back_stage_back_frame, back_stage_back_frame1, back_stage_back_frame2);
	//StageControl
	SDLGameObject* mainScore_grade = new SDLGameObject(new LoaderParams(0, 0, 240, 240, 0, 0, "grade_sprite"));
	SDLGameObject* playScore_grade = new SDLGameObject(new LoaderParams(0, 0, 144, 192, 0, 0, "play_grade_sprite"));
	StageController* stageController = new StageController(new LoaderParams(0, 0, 0, 0, 0, 0, ""), musicSelect, musicSelect_music, mainScore_grade, back_stage1, back_stage_back1, back_stage_back2,
		back_stage_back_frame, back_stage_back_frame1, back_stage_back_frame2);
	//Button
	NormalButton* normalButton1 = new NormalButton(new LoaderParams(0, 0, 96, 96, 0, 0, "nomalButton_sprite"), stageController, true);
	NormalButton* normalButton2 = new NormalButton(new LoaderParams(0, 0, 96, 96, 0, 1, "nomalButton_sprite"), stageController, false);
	SpaceButton* spaceButton1 = new SpaceButton(new LoaderParams(0, 0, 96, 96, 0, 0, "spaceButton_sprite"), stageController);

	//InputCommand
	Command* nullCommand = new NULLCommand();
	Command* upCommand = new UpCommand(normalButton1);
	Command* downCommand = new DownCommand(normalButton2);
	Command* spaceCommand = new SpaceCommand(spaceButton1);

	Command* up_NoteCommand = new Up_NoteCommand(notePad1, player);
	Command* down_NoteCommand = new Down_NoteCommand(notePad2, player);
	Command* right_NoteCommand = new Right_NoteCommand(notePad3, player);
	Command* left_NoteCommend = new Left_NoteCommand(notePad, player);
	Command* space_NoteCommand = new Space_NoteCommand(powerNotePadButton, player);

	Button* upButton = new Button(upCommand);
	Button* downButton = new Button(downCommand);
	Button* rightButton = new Button(nullCommand);
	Button* leftButton = new Button(nullCommand);
	Button* spaceButton = new Button(spaceCommand);

	//Timer
	Timer timer;

	vector<GameObject*> m_gameObjects;
	//object Manager SetIdle();
	vector<NoteShooter*> noteShooters;
	vector<GameObject*> collisionObjects; //충돌할 수 있는 오브젝트 
	vector<GameObject*> allObjects;
	map<const char*, vector<GameObject* >> objects; //모든 오브젝트

	void SetCommand(Command* left, Command* up, Command* down, Command* right, Command* space)
	{
		leftButton = new Button(left);
		upButton = new Button(up);
		downButton = new Button(down);
		rightButton = new Button(right);
		spaceButton = new Button(space);
	}
	void GameOver();	
};
