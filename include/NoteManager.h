#pragma once
//NoteManager
#include <iostream> 
#include<sstream>
#include <fstream> //json 입출력을 위한 파일 입출력 라이브러리
#include <string>
#include <queue> //한줄씩 가져온 데이터를 미리 저장한후, 한줄씩 빼내 다시 파싱합니다 (파싱 --> 딜레이, 노트 타입, 생성되는 위치)
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <Spawn.h>

using namespace std;

class NoteManager //노트 정보를 받아오고, 쏘는 역할 
{
public:
	static NoteManager* GetInstance() //다이나믹 싱글턴. 전역변수로 초기화하지 않으므로, 메모리를 확보할 수 있다 
	{
		if (s_pInstance == 0)
			s_pInstance = new NoteManager();
		return s_pInstance;
	}

	void ReadLineToTxt(string dataPath);
	void SpawnNotes();
	queue<string> GetSpawnQueue();
private:
	int point;
	float nextSpawnDelay;
	float speed;

	float curSpawnDelay;

	queue<Spawn> spawnQueue;
	queue<string> spawnQueue_test;

	static NoteManager* s_pInstance; //정적 멤버변수 선언
};
