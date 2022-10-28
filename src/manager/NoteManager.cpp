#pragma once
#include "NoteManager.h"
#include "Vector2D.h"
#include <Game.h>
#include <Timer.h>

using namespace std;

NoteManager* NoteManager::s_pInstance = NULL;

typedef struct NoteData //1 ~ 4 -> 기본 루트, 5, 6 -> 에너지루트 
{
	Vector2D pos = Vector2D(SCREEN_WIDTH * 0.5f - 200, -96);
	Vector2D pos1 = Vector2D(SCREEN_WIDTH * 0.5f - 100, -96);
	Vector2D pos2 = Vector2D(SCREEN_WIDTH * 0.5f, -96);
	Vector2D pos3 = Vector2D(SCREEN_WIDTH * 0.5f + 100, -96);
}noteData;

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
	if (curSpawnDelay != NULL) // curSpawnDelay != NULL ==> 노트시트가 모두 비었을때 (게임오버하지않고 게임 클리어 시)
	{
		if (m_curTime > curSpawnDelay) //시트가 비지 않았고, 스폰 타이밍일때 
		{
			std::cout << "Left Notes : [ " << spawnQueue_test.size() - 1 << " ]\n";

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
	datas.pop();

	point = stoi(datas.front());
	datas.pop();

	speed = stof(datas.front());
	datas.pop();

	spawnNotes();
	spawnQueue_test.pop();

	if (spawnQueue_test.size() == 0) { nextSpawnDelay = NULL; } //게임 클리어 - 모든 노트 소모  
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

	switch (point)
	{
	default:
		return;
	case 4:
		noteShooter = noteShooters[0];
		break;
	case 5:
		noteShooter = noteShooters[1];
		break;
	}
	//speed == 0 ==> 파워노트 처음쏠때
	//speed == -1 ==> 파워노트를 이제 안쏜다는 뜻 
	if (speed == 0) noteShooter->SetPop();
	else if (speed == -1)noteShooter->SetIdle();
	else noteShooter->Shot(speed);
}
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
