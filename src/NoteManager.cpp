#pragma once
#include "NoteManager.h"
#include "json.h"

using namespace std;
using namespace Json;

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
queue<string> NoteManager::GetSpawnQueue() { return spawnQueue_test; }

//nextSpawnDelay = stof(buffer);
	/*
	float startTime;
	startTime = SDL_GetTicks();
	do {
		curSpawnDelay = SDL_GetTicks() - startTime;
		nextSpawnDelay -= curSpawnDelay;
	} while (curSpawnDelay < nextSpawnDelay);*/
