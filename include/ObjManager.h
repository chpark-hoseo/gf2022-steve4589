/*
#pragma once
#include <map> 
#include <queue>
#include <vector>
#include <string>        
#include <TextureManager.h>
#include <SDLGameObject.h>
#include <Note.h>

class ObjManager 
{
public:
	class Pool //각각의 다른 게임오브젝트를 구별하기 위한 구조체처럼 사용합니다
	{
	public:
		Pool(const char name[20], SDLGameObject* note, int size) : m_name(name), m_gameObj(*note), m_size(size) {}
		const char* m_name;
		SDLGameObject m_gameObj;
		int m_size;
	};
	static ObjManager* GetInstance()
	{
		if (instance == 0)
			instance = new ObjManager();
		return instance;
	}
	vector< SDLGameObject*>  InitPool(); //풀에 오브젝트를 집어넣고, game에 내보내는 역할 
	SDLGameObject CreateObjects(const char* tag, SDLGameObject prefab);
	SDLGameObject GetObject();
private:
	ObjManager();
	static ObjManager* instance;
	map<string, queue<SDLGameObject>> obj; //한종류의 게임오브젝트 ==> note, effect

	//스폰되는 오브젝트의 총 종류 -> 4 종류
	Pool* pools[4] = { new Pool("LeftNote", m_note, 15), new Pool("UpNote", m_note1, 15), new Pool("DownNote", m_note2, 15), new Pool("RightNote", m_note3, 15) };
	//new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite");  //Left
	SDLGameObject* m_note = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	SDLGameObject* m_note1 = new Note(new LoaderParams(0, 0, 96, 96, 32, 0, "notes_sprite"));  //Up
	SDLGameObject* m_note2 = new Note(new LoaderParams(0, 0, 96, 96, 64, 0, "notes_sprite"));  //Down
	SDLGameObject* m_note3 = new Note(new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Right
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else1
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else2
};*/