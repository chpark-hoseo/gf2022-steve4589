#pragma once
#include "NoteManager.h"

using namespace std;

NoteManager* NoteManager::s_pInstance = 0;
//GameManager -> static int curStage;
void NoteManager::ReadLineToTxt(string data) //�������� ��Ʈ ���� 1. ������ ���۵ɶ� (��� ��Ʈ) 2. �� ���������� ������ (�ش� ��Ʈ��)
{
	string dataPath = "Assets/SpawnSheet_" + data + ".txt";
	ifstream spawnSheet(dataPath.c_str(), std::ifstream::in);

	string line;
	if (spawnSheet.is_open())
	{
		while (!spawnSheet.eof())
		{
			getline(spawnSheet, line); //getline(desline, buffer, '/');
			spawnQueue_test.push(line);
		}
		spawnSheet.close();
		cout << "SpawnSheet Size ==> " << spawnQueue_test.size() << "\n";
	}
}
void NoteManager::ReadSpawnNotes()
{
	float curSpawnDelay = nextSpawnDelay;
	m_curTime = Timer::GetInstance()->StartTimer();
	if (curSpawnDelay != NULL /*&& Player::GetInstance()->GetHp() > 0*/) // curSpawnDelay != NULL ==> ��Ʈ��Ʈ�� ��� ������� (���ӿ��������ʰ� ���� Ŭ���� ��)
	{
		if (m_curTime > curSpawnDelay) //��Ʈ�� ���� �ʾҰ�, ���� Ÿ�̹��϶� 
		{
			std::cout << "Left Notes : [ " << spawnQueue_test.size() << " ]\n";

			SpawnNotes(); //���� ������ �޾ƿɴϴ� 
			Timer::GetInstance()->WaitTime(); //m_curTime �ʱ�ȭ
			/*���ӽ��� ������ Timer::GetInstance()->WaitTime(); ȣ���ʿ�*/
		}
		else {  }
	}
}
void NoteManager::SpawnNotes() //���پ� ȣ��
{
	string line;
	queue<string> datas;

	stringstream readQueue(spawnQueue_test.front());
	while (getline(readQueue, line, '/')) 
	{
		datas.push(line);
	}

	nextSpawnDelay = stof(datas.front());
	cout << "nextSpawnDelay => " << nextSpawnDelay << "    ";
	datas.pop();

	point = stoi(datas.front());
	cout << "point => " << point << "    ";
	datas.pop();

	speed = stof(datas.front());
	cout << "speed => " << speed << "\n\n";
	datas.pop();

	spawnQueue_test.pop();
	if (spawnQueue_test.size() == 0) { nextSpawnDelay = NULL; } //���� Ŭ����  
}
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
//nextSpawnDelay = stof(buffer);
	/*
	float startTime;
	startTime = SDL_GetTicks();
	do {
		curSpawnDelay = SDL_GetTicks() - startTime;
		nextSpawnDelay -= curSpawnDelay;
	} while (curSpawnDelay < nextSpawnDelay);*/
