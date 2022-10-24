#pragma once
#include "NoteManager.h"
#include "Vector2D.h"
#include <Game.h>
#include <Timer.h>

using namespace std;

NoteManager* NoteManager::s_pInstance = NULL;

typedef struct NoteData //1 ~ 4 -> �⺻ ��Ʈ, 5, 6 -> ��������Ʈ 
{
	Vector2D pos = Vector2D(SCREEN_WIDTH * 0.5f - 200, -96);
	Vector2D pos1 = Vector2D(SCREEN_WIDTH * 0.5f - 100, -96);
	Vector2D pos2 = Vector2D(SCREEN_WIDTH * 0.5f, -96);
	Vector2D pos3 = Vector2D(SCREEN_WIDTH * 0.5f + 100, -96);
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
	if (curSpawnDelay != NULL) // curSpawnDelay != NULL ==> ��Ʈ��Ʈ�� ��� ������� (���ӿ��������ʰ� ���� Ŭ���� ��)
	{
		if (m_curTime > curSpawnDelay) //��Ʈ�� ���� �ʾҰ�, ���� Ÿ�̹��϶� 
		{
			std::cout << "Left Notes : [ " << spawnQueue_test.size() - 1 << " ]\n";

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
	datas.pop();

	point = stoi(datas.front());
	datas.pop();

	speed = stof(datas.front());
	datas.pop();

	spawnNotes();
	spawnQueue_test.pop();

	if (spawnQueue_test.size() == 0) { nextSpawnDelay = NULL; } //���� Ŭ���� - ��� ��Ʈ �Ҹ�  
}

void NoteManager::spawnNotes()
{
	noteData noteData;
	Vector2D spawnPos = Vector2D(0, 0);
	GameObject* gameObject = NULL;
	//string type;
	switch (point)
	{
	default:
		SpawnPowerNote(point);
		return;
	case 0:
		spawnPos = noteData.pos;
		gameObject = Game::GetInstance()->GetObject(spawnPos, "LeftNote");
		break;
	case 1:
		spawnPos = noteData.pos1;
		gameObject = Game::GetInstance()->GetObject(spawnPos, "UpNote");
		break;
	case 2:
		spawnPos = noteData.pos2;
		gameObject = Game::GetInstance()->GetObject(spawnPos, "DownNote");
		break;
	case 3:
		spawnPos = noteData.pos3;
		gameObject = Game::GetInstance()->GetObject(spawnPos, "RightNote");
		break;
	}
	gameObject->SetSpeed(speed);
}
void NoteManager::SpawnPowerNote(int point)
{
	NoteShooter* noteShooter = NULL;
	Vector2D spawnPos = Vector2D(0, 0); 
	switch (point)
	{
	default:
		return;
	case 4:
		noteShooter = noteShooters[0];
		spawnPos = noteShooter->GetPosition();
		noteShooter->Shot();
		break;
	case 5:
		noteShooter = noteShooters[1];
		spawnPos = noteShooter->GetPosition();
		noteShooter->Shot();
		break;
	}
}
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
