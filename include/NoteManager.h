#pragma once
#include <iostream> 
#include<sstream>
#include <fstream> //json ������� ���� ���� ����� ���̺귯��
#include <string>
#include <queue> //���پ� ������ �����͸� �̸� ��������, ���پ� ���� �ٽ� �Ľ��մϴ� (�Ľ� --> ������, ��Ʈ Ÿ��, �����Ǵ� ��ġ)
#include <map>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

#include <NoteShooter.h>
#include <Spawn.h>

using namespace std;

class NoteManager //��Ʈ ������ �޾ƿ���, ��� ���� 
{
public:
	static NoteManager* GetInstance() //���̳��� �̱���. ���������� �ʱ�ȭ���� �����Ƿ�, �޸𸮸� Ȯ���� �� �ִ� 
	{
		if (s_pInstance == NULL)
			s_pInstance = new NoteManager();
		return s_pInstance;
	}
	void ReadLineToTxt(string dataPath);
	void ReadSpawnNotes();

	void SetNoteShooters(NoteShooter* noteShooter) { noteShooters.emplace_back(noteShooter); }
	void SetPowerNotePads(NotePad* powerNotePad) { powerNotePads.emplace_back(powerNotePad); }

	queue<string> GetSpawnQueue();
	map<int, string*> GetSpawnQueue_; //int -> n��° ��������
private:
	NoteManager() { }
	~NoteManager() { }

	void ReadSpawnNote();
	//NoteSpawn
	void spawnNotes();
	void SpawnPowerNote(int point);

	int point;
	float nextSpawnDelay = 1;
	float speed;

	double m_curTime = 0;

	vector<NoteShooter*> noteShooters;
	vector<NotePad*> powerNotePads;

	queue<Spawn> spawnQueue;
	queue<string> spawnQueue_test;

	static NoteManager* s_pInstance; //���� ������� ����
};
