#pragma once
//NoteManager
#include <iostream> 
#include<sstream>
#include <fstream> //json ������� ���� ���� ����� ���̺귯��
#include <string>
#include <queue>; //���پ� ������ �����͸� �̸� ��������, ���پ� ���� �ٽ� �Ľ��մϴ� (�Ľ� --> ������, ��Ʈ Ÿ��, �����Ǵ� ��ġ)
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <Spawn.h>

using namespace std;

class NoteManager //��Ʈ ������ �޾ƿ���, ��� ���� 
{
public:
	void ReadLineToTxt(const char* dataPath);
	queue<string> GetSpawnQueue();
private:
	float nextSpawnDelay;
	float curSpawnDelay;

	queue<Spawn> spawnQueue;
	queue<string> spawnQueue_test;

	//BasicExcel xls;
};