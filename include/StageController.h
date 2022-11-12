#pragma once
#include<sstream>
#include <fstream> 
#include <string>
#include <queue>
#include <iostream>

using namespace std;
class SDLGameObject;

struct StageData
{
	// ex) Stage0 / 0 / stage0_back_sprite / stage0_sprite / stage0_back_frame_sprite
	string stageName;
	int Grade;
	string stage_back_sprite;
	string stage_sprite;
	string stage_back_frame_sprite;
}typedef stageData;

class StageController //스테이지 데이터 저장 및 변경 / 스테이지 이미지 관리 및 변경
{
public:
	StageController(SDLGameObject* getSelectMusic, SDLGameObject* getSelectMusicPanel, SDLGameObject* getBack_stage1,
		SDLGameObject* getBack_stage_back1, SDLGameObject* getBack_stage_back2, SDLGameObject* getStage_back_frame_sprite,
		SDLGameObject* getStage_back_frame_sprite1, SDLGameObject* getStage_back_frame_sprite2);

	void StageDataInit()
	{
		const char* dataPath = "Assets/StageData.txt";
		std::ifstream stageSheet(dataPath, std::ifstream::in);

		string line;
		if (stageSheet.is_open())
		{
			musicIndex = 0;
			while (!stageSheet.eof())
			{
				getline(stageSheet, line); //getline(desline, buffer, '/');
				stringData[musicIndex] = line;
				musicIndex++;
			}
			stageSheet.close();
		}
		ChangeStageData();
	}
	void OnOffPanel(bool onOff);

	bool SelectMusic(); //음악, 사진 바꾸기, 
	void Select();

	void NextPreviousMusic(bool isUp)
	{
		if (isUp == true) NextMusic();
		else PreviousMusic();
	}
	void NextMusic();
	void PreviousMusic();

	void ChangeStageData()
	{
		string line;
		queue<string> datas;

		stringstream readQueue(stringData[passMusicIndex]);
		while (getline(readQueue, line, '/'))
		{
			datas.push(line);
		}
		// ex) Stage0 / 0 / stage0_back_sprite / stage0_sprite / stage0_back_frame_sprite
		stageData.stageName = datas.front();
		datas.pop();
		stageData.Grade = stoi(datas.front());
		datas.pop();
		stageData.stage_back_sprite = datas.front();
		datas.pop();
		stageData.stage_sprite = datas.front();
		datas.pop();
		stageData.stage_back_frame_sprite = datas.front();
		datas.pop();

		ChangeSprites();
		//std::cout << stageData.stageName << "\n" << stageData.Grade << "\n" << stageData.stage_back_sprite << "\n" << stageData.stage_sprite << "\n" << stageData.stage_back_frame_sprite << "\n";
	}
	void ChangeSprites();
private:
	string stringData[3];

	SDLGameObject* selectMusic;
	SDLGameObject* selectMusic_music;

	SDLGameObject* back_stage1;
	SDLGameObject* back_stage_back1;
	SDLGameObject* back_stage_back2;
	SDLGameObject* back_stage_back_frame;
	SDLGameObject* back_stage_back_frame1;
	SDLGameObject* back_stage_back_frame2;


	stageData stageData;

	int musicIndex = 0;
	int passMusicIndex = 0;
};
// ex) Stage0 / 0 / stage0_back_sprite / stage0_sprite / stage0_back_frame_sprite
		//스테이지, 점수, 뒷 배경 3형제 
		//점수 40미만 or 겜오버 -> F, 점수 40 -> B, 점수 75 -> A, 점수 90 -> A+
		//점수는 0, 1, 2, 3 순서 