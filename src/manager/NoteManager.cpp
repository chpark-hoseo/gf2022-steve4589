#pragma once
#include "NoteManager.h"
#include "ObjManager.h"
#include "Vector2D.h"

using namespace std;

NoteManager* NoteManager::s_pInstance = NULL;

typedef struct NotePos //1 ~ 4 -> �⺻ ��Ʈ, 5, 6 -> ��������Ʈ 
                       //SpawnSheet �ι�° �Ľ��� ���� ���
{
	Vector2D notePos = Vector2D(362, -64);
	Vector2D notePos1 = Vector2D(462, -64);
	Vector2D notePos2 = Vector2D(562, -64);
	Vector2D notePos3 = Vector2D(662, -64);
	//Vector2D EnergyPos = Vector2D(500, 0);
	//Vector2D EnergyPos1 = Vector2D(500, 0);
}notePos;

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
	
	spawnQueue_test.pop();
	if (spawnQueue_test.size() == 0) { nextSpawnDelay = NULL; } //���� Ŭ���� - ��� ��Ʈ �Ҹ�  
}

void NoteManager::spawnNotes(float nextSpawnDelay, int point, float speed)
{
	//Vector2D spawnPos = NULL;

	//ObjectManager.GetInstance()->Spawn
}
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
