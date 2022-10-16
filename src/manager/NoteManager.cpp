#pragma once
#include "NoteManager.h"
#include "Vector2D.h"
#include <Game.h>

using namespace std;

NoteManager* NoteManager::s_pInstance = NULL;

typedef struct NoteData //1 ~ 4 -> �⺻ ��Ʈ, 5, 6 -> ��������Ʈ 
{
	Vector2D pos = Vector2D(SCREEN_WIDTH * 0.5f - 200, 0);
	Vector2D pos1 = Vector2D(SCREEN_WIDTH * 0.5f - 100, 0);
	Vector2D pos2 = Vector2D(SCREEN_WIDTH * 0.5f, 0);
	Vector2D pos3 = Vector2D(SCREEN_WIDTH * 0.5f + 100, 0);
	//Vector2D EnergyPos = Vector2D(500, 0);
	//Vector2D EnergyPos1 = Vector2D(500, 0);
}noteData;

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
			std::cout << "Left Notes : [ " << spawnQueue_test.size() - 2 << " ]\n";

			ReadSpawnNote(); //���� ������ �޾ƿɴϴ� 

			Timer::GetInstance()->WaitTime(); //m_curTime �ʱ�ȭ
			/*���ӽ��� ������ Timer::GetInstance()->WaitTime(); ȣ���ʿ�*/
		}
	}
}
void NoteManager::ReadSpawnNote() //���پ� ȣ��
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

	spawnNotes();

	spawnQueue_test.pop();
	if (spawnQueue_test.size() == 1) { nextSpawnDelay = NULL; } //���� Ŭ���� - ��� ��Ʈ �Ҹ�  
}

void NoteManager::spawnNotes()
{
	noteData noteData;
	Vector2D spawnPos = Vector2D(0, 0);
	//string type;
	switch (point)
	{
	default:
		break;
	case 0:
		spawnPos = noteData.pos;
		Game::GetInstance()->GetObject(spawnPos, "LeftNote")->SetSpeed(speed);
		break;
	case 1:
		spawnPos = noteData.pos1;
		Game::GetInstance()->GetObject(spawnPos, "UpNote")->SetSpeed(speed);
		break;
	case 2:
		spawnPos = noteData.pos2;
		Game::GetInstance()->GetObject(spawnPos, "DownNote")->SetSpeed(speed);
		break;
	case 3:
		spawnPos = noteData.pos3;
		Game::GetInstance()->GetObject(spawnPos, "RightNote")->SetSpeed(speed);
		break;
	}
	//gameObject->SetSpeed(speed);
}
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
