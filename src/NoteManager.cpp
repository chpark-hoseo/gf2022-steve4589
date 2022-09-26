#pragma once
#include <iostream>
#include <iostream> 
#include <vector>
#include <string>
#include <list>
#include<fstream>
#include <regex>
#include "ExcelFormat.h"

using namespace ExcelFormat;
using namespace std;

enum Menu { INPUT_MODE = 1, SEARCH_MODE, EXIT };
enum SearchMenu { PRINT_NAME = 1, PRINT_GRADE, PRINT_AVG, PRINT_TEL, PRINT_ALL };

class NoteManager
{
private:
	float nextSpawnDelay;
	float curSpawnDelay;

};