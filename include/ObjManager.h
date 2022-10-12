#pragma once
#include <iostream> 
#include <map> 
#include <queue>
#include <vector>
#include <string>        
#include <TextureManager.h>
#include <Note.h>

class Pool //������ �ٸ� ���ӿ�����Ʈ�� �����ϱ� ���� ����üó�� ����մϴ�
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
	vector<GameObject*> InitPool(); //Ǯ�� ������Ʈ�� ����ְ�, game�� �������� ���� 
	SDLGameObject * CreateObjects(const char* tag, SDLGameObject * getGameObject);
	SDLGameObject* GetObject(Vector2D spawnPos, const char name[20]);
private:
	static ObjManager* instance;
	map<string, queue<SDLGameObject>> obj; //�������� ���ӿ�����Ʈ ==> note, effect

	SDLGameObject* m_note = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	SDLGameObject* m_note1 = new Note(new LoaderParams(0, 0, 96, 96, 32, 0, "notes_sprite"));  //Up
	SDLGameObject* m_note2 = new Note(new LoaderParams(0, 0, 96, 96, 64, 0, "notes_sprite"));  //Down
	SDLGameObject* m_note3 = new Note(new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Right
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else1
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else2
};