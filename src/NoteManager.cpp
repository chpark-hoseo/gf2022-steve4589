#pragma once
#include "NoteManager.h"

//GameManager -> static int curStage;
void NoteManager::ReadLineToXls()
{
	BasicExcelWorksheet* sheet = nullptr;
	//xls.Load("Assets/NeedForA+_SpawnSheet.xls");
	xls.New(1);
	sheet = xls.GetWorksheet(0); //어차피 1개만 계속 쓰기 때문에

	for (int i = 1; i < sheet->GetTotalCols(); i++)
	{
		string line = sheet->Cell(1, i)->GetString();
		string buffer;

		istringstream desline(line);
		getline(desline, buffer, '/');

		nextSpawnDelay = stof(buffer);
		cout << "\n\n";
		cout << nextSpawnDelay << "\n";

		float startTime;
		startTime = SDL_GetTicks();

		do {
			curSpawnDelay = SDL_GetTicks() - startTime;
			nextSpawnDelay -= curSpawnDelay;
		} while (curSpawnDelay < nextSpawnDelay);
	}
}

void NoteManager::test()
{
	cout << "xlstest";
}
/*
		while (getline(desline, buffer, ' '))
		{

		}*/