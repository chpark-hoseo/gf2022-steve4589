#pragma once
#include <iostream> 
#include <vector>
#include <string>
#include <list>
#include<fstream>
#include <regex>
#include "ExcelFormat.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include<sstream>

using namespace ExcelFormat;
using namespace std;

enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };

class NoteManager
{
private:
	float nextSpawnDelay;
	float curSpawnDelay;

	BasicExcel xls;

	//GameManager -> static int curStage;

	void ReadLineToXls()
	{
		BasicExcelWorksheet* sheet = nullptr;
		sheet = xls.GetWorksheet(0); //어차피 1개만 계속 쓰기 때문에

		for (int i = 1; i < sheet->GetTotalCols(); ++i)
		{
			string line = sheet->Cell(1, i)->GetString(); 
			string buffer;
			istringstream desline(line);

			getline(desline, buffer, '/');
			nextSpawnDelay = stof(buffer);
			
			cout << nextSpawnDelay;
			/*
			while (getline(desline, buffer, ' '))
			{

			}*/
			float startTime;
			startTime = SDL_GetTicks();

			do {
				curSpawnDelay = SDL_GetTicks() - startTime;
				nextSpawnDelay -= curSpawnDelay;
			} while (curSpawnDelay < nextSpawnDelay);
		}
	}

};