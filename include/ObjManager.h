#pragma once
#include <iostream> 
#include <map> 
#include <queue>
#include <vector>
#include <string>        
#include <TextureManager.h>
#include <Note.h>

class Pool //각각의 다른 게임오브젝트를 구별하기 위한 구조체처럼 사용합니다
{
public:
	Pool(const char name[20], SDLGameObject* note, int size) : m_name(name), m_gameObj(note), m_size(size) {}
	const char* m_name;
	SDLGameObject* m_gameObj;
	int m_size;
};

class ObjManager
{
public:
	static ObjManager* GetInstance()
	{
		if (instance == 0)
		{
			instance = new ObjManager();
		}
		return instance;
	}
	vector<GameObject*> InitPool(); //풀에 오브젝트를 집어넣고, game에 내보내는 역할 
	SDLGameObject * CreateObjects(const char* tag, SDLGameObject * getGameObject);
	SDLGameObject* GetObject(Vector2D spawnPos, const char name[20]);
private:
	static ObjManager* instance;
	map<string, queue<SDLGameObject>> obj; //한종류의 게임오브젝트 ==> note, effect

	SDLGameObject* m_note = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	SDLGameObject* m_note1 = new Note(new LoaderParams(0, 0, 96, 96, 32, 0, "notes_sprite"));  //Up
	SDLGameObject* m_note2 = new Note(new LoaderParams(0, 0, 96, 96, 64, 0, "notes_sprite"));  //Down
	SDLGameObject* m_note3 = new Note(new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Right
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else1
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else2
};