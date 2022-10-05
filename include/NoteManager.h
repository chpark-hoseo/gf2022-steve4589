#pragma once
//NoteManager
#include <iostream> 
#include<sstream>
#include <fstream> //json ������� ���� ���� ����� ���̺귯��
#include <string>
#include <queue> //���پ� ������ �����͸� �̸� ��������, ���پ� ���� �ٽ� �Ľ��մϴ� (�Ľ� --> ������, ��Ʈ Ÿ��, �����Ǵ� ��ġ)
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <Spawn.h>

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
	void SpawnNotes();
	queue<string> GetSpawnQueue();
private:
	int point;
	float nextSpawnDelay;
	float speed;

	float curSpawnDelay;

	queue<Spawn> spawnQueue;
	queue<string> spawnQueue_test;

	static NoteManager* s_pInstance; //���� ������� ����
};
