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
	class Pool //������ �ٸ� ���ӿ�����Ʈ�� �����ϱ� ���� ����üó�� ����մϴ�
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
	vector< SDLGameObject*>  InitPool(); //Ǯ�� ������Ʈ�� ����ְ�, game�� �������� ���� 
	SDLGameObject CreateObjects(const char* tag, SDLGameObject prefab);
	SDLGameObject GetObject();
private:
	ObjManager();
	static ObjManager* instance;
	map<string, queue<SDLGameObject>> obj; //�������� ���ӿ�����Ʈ ==> note, effect

	//�����Ǵ� ������Ʈ�� �� ���� -> 4 ����
	Pool* pools[4] = { new Pool("LeftNote", m_note, 15), new Pool("UpNote", m_note1, 15), new Pool("DownNote", m_note2, 15), new Pool("RightNote", m_note3, 15) };
	//new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite");  //Left
	SDLGameObject* m_note = new Note(new LoaderParams(0, 0, 96, 96, 0, 0, "notes_sprite"));
	SDLGameObject* m_note1 = new Note(new LoaderParams(0, 0, 96, 96, 32, 0, "notes_sprite"));  //Up
	SDLGameObject* m_note2 = new Note(new LoaderParams(0, 0, 96, 96, 64, 0, "notes_sprite"));  //Down
	SDLGameObject* m_note3 = new Note(new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Right
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else1
	//Note note3 = (new LoaderParams(0, 0, 96, 96, 96, 0, "notes_sprite")); //Else2
};*/