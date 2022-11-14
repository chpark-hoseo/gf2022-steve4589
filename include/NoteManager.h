#pragma once
#include <iostream> 
#include<sstream>
#include <fstream> //json 입출력을 위한 파일 입출력 라이브러리
#include <string>
#include <queue> //한줄씩 가져온 데이터를 미리 저장한후, 한줄씩 빼내 다시 파싱합니다 (파싱 --> 딜레이, 노트 타입, 생성되는 위치)
#include <map>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

#include <NoteShooter.h>
#include <PowerNotePad.h>
#include <Spawn.h>

using namespace std;

class NoteManager //노트 정보를 받아오고, 쏘는 역할 
{
public:
	static NoteManager* GetInstance() //다이나믹 싱글턴. 전역변수로 초기화하지 않으므로, 메모리를 확보할 수 있다 
	{
		if (s_pInstance == NULL)
			s_pInstance = new NoteManager();
		return s_pInstance;
	}
	void ReadLineToTxt(string dataPath);
	void ReadSpawnNotes();

	void SetNoteShooters(NoteShooter* noteShooter) { noteShooters.emplace_back(noteShooter); }
	void SetPowerNotePads(PowerNotePad* powerNotePad) { powerNotePads.emplace_back(powerNotePad); }

	queue<string> GetSpawnQueue();
	map<int, string*> GetSpawnQueue_; //int -> n번째 스테이지

	int GetAllNoteNum() { return allNoteNum; }
private:
	NoteManager() { }
	~NoteManager() { }

	void ReadSpawnNote();
	//NoteSpawn
	void spawnNotes();
	void SpawnPowerNote(int point);

	int point;
	float nextSpawnDelay = 1;
	float speed;

	double m_curTime = 0;

	int allNoteNum;

	vector<NoteShooter*> noteShooters;
	vector<PowerNotePad*> powerNotePads;

	queue<Spawn> spawnQueue;
	queue<string> spawnQueue_test;

	static NoteManager* s_pInstance; //정적 멤버변수 선언
};
