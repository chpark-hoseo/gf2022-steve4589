#pragma once
#include "NoteManager.h"
#include "ObjManager.h"
#include "Vector2D.h"

using namespace std;

NoteManager* NoteManager::s_pInstance = NULL;

typedef struct NotePos //1 ~ 4 -> 기본 루트, 5, 6 -> 에너지루트 
                       //SpawnSheet 두번째 파싱을 통해 사용
{
	Vector2D notePos = Vector2D(362, -64);
	Vector2D notePos1 = Vector2D(462, -64);
	Vector2D notePos2 = Vector2D(562, -64);
	Vector2D notePos3 = Vector2D(662, -64);
	//Vector2D EnergyPos = Vector2D(500, 0);
	//Vector2D EnergyPos1 = Vector2D(500, 0);
}notePos;

//GameManager -> static int curStage;
void NoteManager::ReadLineToTxt(string data) //스테이지 시트 리필 1. 게임이 시작될때 (모든 시트) 2. 각 스테이지가 끝날때 (해당 시트만)
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
	if (curSpawnDelay != NULL /*&& Player::GetInstance()->GetHp() > 0*/) // curSpawnDelay != NULL ==> 노트시트가 모두 비었을때 (게임오버하지않고 게임 클리어 시)
	{
		if (m_curTime > curSpawnDelay) //시트가 비지 않았고, 스폰 타이밍일때 
		{
			std::cout << "Left Notes : [ " << spawnQueue_test.size() << " ]\n";

			ReadSpawnNote(); //다음 한줄을 받아옵니다 
			Timer::GetInstance()->WaitTime(); //m_curTime 초기화
			/*게임시작 누를때 Timer::GetInstance()->WaitTime(); 호출필요*/
		}
	}
}
void NoteManager::ReadSpawnNote() //한줄씩 호출
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
	if (spawnQueue_test.size() == 0) { nextSpawnDelay = NULL; } //게임 클리어 - 모든 노트 소모  
}

void NoteManager::spawnNotes(float nextSpawnDelay, int point, float speed)
{
	//Vector2D spawnPos = NULL;

	//ObjectManager.GetInstance()->Spawn
}
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
