#pragma once
#include "NoteManager.h"
#include "Vector2D.h"
#include <State_Play.h>
#include <Timer.h>

using namespace std;

NoteManager* NoteManager::s_pInstance = NULL;

typedef struct NoteData //1 ~ 4 -> �⺻ ��Ʈ, 5, 6 -> ��������Ʈ 
{
	Vector2D pos = Vector2D(SCREEN_WIDTH * 0.5f - 250, -96);
	Vector2D pos1 = Vector2D(SCREEN_WIDTH * 0.5f - 100, -96);
	Vector2D pos2 = Vector2D(SCREEN_WIDTH * 0.5f + 50, -96);
	Vector2D pos3 = Vector2D(SCREEN_WIDTH * 0.5f + 200, -96);
}noteData;

//GameManager -> static int curStage;
void NoteManager::ReadLineToTxt(string data) //�������� ��Ʈ ���� 1. ������ ���۵ɶ� (��� ��Ʈ) 2. �� ���������� ������ (�ش� ��Ʈ��)
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

			if (allNoteNum == 0) { //ù��° ��Ʈ�� ������ �ʿ� ( if (m_curTime > curSpawnDelay) ������ �ƿ� �۵� ���ϱ� ������ )
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
	if (curSpawnDelay != NULL) // curSpawnDelay != NULL ==> ��Ʈ��Ʈ�� ��� ������� (���ӿ��������ʰ� ���� Ŭ���� ��)
	{
		if (m_curTime > curSpawnDelay) //��Ʈ�� ���� �ʾҰ�, ���� Ÿ�̹��϶� 
		{
			std::cout << "Left Notes : [ " << spawnQueue_test.size() - 1 << " ]\n";

			ReadSpawnNote(); //���� ������ �޾ƿɴϴ� 

			Timer::GetInstance()->WaitTime(); //m_curTime �ʱ�ȭ
			/*���ӽ��� ������ Timer::GetInstance()->WaitTime(); ȣ���ʿ�*/
		}
		return false;
	}
	else { return true; }
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

	//10���� ���� �� => ����Ʈ, ������ => ��ƺ��� ��ġ
	int point = getPoint / 10;
	int disPoint = getPoint % 10;

	switch (point) 
	{
	default:
		std::cout << "NoteTrigger\n"; //������ ����(�������� �����Ҷ� / ������)�� ����մϴ�
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
