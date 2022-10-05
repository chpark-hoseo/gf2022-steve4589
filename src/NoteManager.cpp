#pragma once
#include "NoteManager.h"

using namespace std;

NoteManager* NoteManager::s_pInstance = 0;
//GameManager -> static int curStage;
void NoteManager::ReadLineToTxt(string data)
{
	string dataPath = "Assets/" + data + ".txt";
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
void NoteManager::SpawnNotes()
{
	string line;
	queue<string> datas;
	int limit = spawnQueue_test.size();

	for (int i = 0; i < limit; i++)
	{
		stringstream readQueue(spawnQueue_test.front());
		while (getline(readQueue, line, '/')) //한줄
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
		cout << "speed => " << speed << "    ";
		datas.pop();

		//delay만큼 쉬기

		cout << "\n";
		spawnQueue_test.pop();
	}
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
