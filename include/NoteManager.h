#pragma once
#include <iostream> 
#include<sstream>
#include <fstream> //json ������� ���� ���� ����� ���̺귯��
#include <string>
#include <queue> //���پ� ������ �����͸� �̸� ��������, ���پ� ���� �ٽ� �Ľ��մϴ� (�Ľ� --> ������, ��Ʈ Ÿ��, �����Ǵ� ��ġ)

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

#include <Spawn.h>
#include <Timer.h>

using namespace std;

class NoteManager //��Ʈ ������ �޾ƿ���, ��� ���� 
{
public:
	static NoteManager* GetInstance() //���̳��� �̱���. ���������� �ʱ�ȭ���� �����Ƿ�, �޸𸮸� Ȯ���� �� �ִ� 
	{
		if (s_pInstance == 0)
			s_pInstance = new NoteManager();
		return s_pInstance;
	}

	void ReadLineToTxt(string dataPath);
	void ReadSpawnNotes();
	void SpawnNotes();
	queue<string> GetSpawnQueue();
private:
	int point;
	float nextSpawnDelay = 1;
	float speed;

	double m_curTime = 0;

	queue<Spawn> spawnQueue;
	queue<string> spawnQueue_test;

	static NoteManager* s_pInstance; //���� ������� ����
};
