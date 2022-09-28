#pragma once
#include "NoteManager.h"

using namespace std;

//GameManager -> static int curStage;
void NoteManager::ReadLineToTxt(const char* dataPath)
{
	ifstream spawnSheet(dataPath, std::ifstream::in);

	string line;
	if (spawnSheet.is_open())
	{
		while (!spawnSheet.eof())
		{
			getline(spawnSheet, line); //getline(desline, buffer, '/');
			spawnQueue_test.push(line);
		}
		spawnSheet.close();
	}
}
void NoteManager::SpawnNotes()
{
	string line;
	stringstream readQueue(spawnQueue_test.front());

	queue<string> datas;
	while (getline(readQueue, line, '/'))
	{
		datas.push(line);
	}
	int limit = datas.size();
	for (int i = 0; i < limit; i++) //한줄에 데이터 3개
	{
		switch (i)
		{
		case 0:
			nextSpawnDelay = stof(datas.front());
			cout << "nextSpawnDelay =>" << nextSpawnDelay << "    ";
			break;
		case 1:
			type = datas.front();
			cout << "type" << type << "    ";
			break;
		case 2:
			point = stoi(datas.front());
			cout << "point" << point << "    ";
			break;
		}
		datas.pop();
	}
	spawnQueue_test.pop();
}
//nextSpawnDelay = stof(buffer);
	/*
	float startTime;
	startTime = SDL_GetTicks();
	do {
		curSpawnDelay = SDL_GetTicks() - startTime;
		nextSpawnDelay -= curSpawnDelay;
	} while (curSpawnDelay < nextSpawnDelay);*/
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }
//nextSpawnDelay = stof(buffer);
	/*
	float startTime;
	startTime = SDL_GetTicks();
	do {
		curSpawnDelay = SDL_GetTicks() - startTime;
		nextSpawnDelay -= curSpawnDelay;
	} while (curSpawnDelay < nextSpawnDelay);*/
