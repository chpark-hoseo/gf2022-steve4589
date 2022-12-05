#pragma once
#include <NoteManager.h>
#include <State_Play.h>

using namespace std;

NoteManager* NoteManager::s_pInstance = NULL;

typedef struct NoteData //1 ~ 4 -> 기본 루트, 5, 6 -> 에너지루트 
{
	Vector2D pos = Vector2D(SCREEN_WIDTH * 0.5f - 250, -96);
	Vector2D pos1 = Vector2D(SCREEN_WIDTH * 0.5f - 100, -96);
	Vector2D pos2 = Vector2D(SCREEN_WIDTH * 0.5f + 50, -96);
	Vector2D pos3 = Vector2D(SCREEN_WIDTH * 0.5f + 200, -96);
}noteData;

//GameManager -> static int curStage;
void NoteManager::ReadLineToTxt(string data) //스테이지 시트 리필 1. 게임이 시작될때 (모든 시트) 2. 각 스테이지가 끝날때 (해당 시트만)
{
	string dataPath = "Assets/SpawnSheet_" + data + ".txt";
	ifstream spawnSheet(dataPath.c_str(), std::ifstream::in);

	allNoteNum = 0;
	spawnQueue_test = queue<string>();
	string line;
	if (spawnSheet.is_open())
	{
		//nextSpawnDelay = 1f;
		while (!spawnSheet.eof())
		{
			getline(spawnSheet, line); //getline(desline, buffer, '/');
			spawnQueue_test.push(line);

			if (allNoteNum == 0) { //첫번째 노트의 딜레이 필요 ( if (m_curTime > curSpawnDelay) 때문에 아예 작동 안하기 때문에 )
				const char* n = &line[0];
				nextSpawnDelay = atof(n); 
			}
			allNoteNum++;
		}
		spawnSheet.close();
		cout << "SpawnSheet Size ==> " << spawnQueue_test.size() << "\n";
	}
}
bool NoteManager::ReadSpawnNotes()
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
		return false;
	}
	else { return true; }
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
		gameObject = State_Play::GetInstance()->GetObject(spawnPos, "LeftNote");
		break;
	case 1:
		spawnPos = noteData.pos1;
		gameObject = State_Play::GetInstance()->GetObject(spawnPos, "UpNote");
		break;
	case 2:
		spawnPos = noteData.pos2;
		gameObject = State_Play::GetInstance()->GetObject(spawnPos, "DownNote");
		break;
	case 3:
		spawnPos = noteData.pos3;
		gameObject = State_Play::GetInstance()->GetObject(spawnPos, "RightNote");
		break;
	}
	gameObject->SetSpeed(speed);
}
void NoteManager::SpawnPowerNote(int getPoint)
{
	NoteShooter* noteShooter = NULL;
	PowerNotePad* notePad = NULL;

	Vector2D disPos = Vector2D(0, 0);

	//10으로 나눈 값 => 포인트, 나머지 => 쏘아보낼 위치
	int point = getPoint / 10;
	int disPoint = getPoint % 10;

	switch (point) 
	{
	default:
		std::cout << "NoteTrigger\n"; //구별용 더미(스테이지 시작할때 / 끝날때)로 사용합니다
		return;
	case 4:
		notePad = powerNotePads[disPoint];
		noteShooter = noteShooters[0];
		break;
	case 5:
		notePad = powerNotePads[disPoint];
		noteShooter = noteShooters[1];
		break;
	/*case 6:
		notePad = powerNotePads[disPoint];
		noteShooter = noteShooters[0];
		break;
	case 7:
		notePad = powerNotePads[disPoint];
		noteShooter = noteShooters[1];
		break;*/
	}
	disPos = notePad->GetPosition();
	noteShooter->Shot(speed, disPos);
}
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
