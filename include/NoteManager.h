#pragma once
//NoteManager
#include <iostream> 
#include<sstream>
#include <string>
#include<list>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include "ExcelFormat.h"

using namespace ExcelFormat;
using namespace std;

class NoteManager
{
public:
	void ReadLineToXls();
	void test();
private:
	float nextSpawnDelay;
	float curSpawnDelay;

	BasicExcel xls;
};