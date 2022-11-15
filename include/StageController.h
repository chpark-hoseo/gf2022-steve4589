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

struct StageInfoData
{
	string Info_Name;
	string Info_Explan;
}typedef stageInfoData;

class StageController //스테이지 데이터 / 이미지 저장 및 관리 및 변경 
{
public:
	StageController(SDLGameObject* getSelectMusic, SDLGameObject* getSelectMusicPanel,
		SDLGameObject* getMainScore_Grade, SDLGameObject* getBack_stage1,
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
				getline(stageSheet, line); //getline(desline, buffer, '/'); 한줄씩 받아옴
				stringData[musicIndex] = line;
				std::cout << line << "\n";
				musicIndex++;
			}
			stageSheet.close();
		}
		ChangeStageData();
	}
	void NextPreviousMusic(bool isUp)
	{
		if (isUp == true) NextMusic();
		else PreviousMusic();
	}
	void NextMusic();
	void PreviousMusic();
	void SelectMusic(); //음악, 사진 바꾸기, 
	/*
	Stage0/0/stage0_back_sprite/stage0_sprite/stage0_back_frame_sprite
	Stage1/3/stage1_back_sprite/stage1_sprite/stage1_back_frame_sprite
	Stage2/4/stage2_back_sprite/stage2_sprite/stage2_back_frame_sprite
	*/
	void SaveGrade(string stageName, int grade) //파일 중간만 바꿀 수 없기에, 고칠 부분만 수정하고 처음부터 다시 삽입합니다
	{
		//성적을 변경할 해당 스테이지 번호만 가져옵니다 
		int index = 0;
		const char* stagename = stageName.c_str();
		for (int i = 0; i < strlen(stagename); i++)
		{
			if (stagename[i] >= 48 && stagename[i] <= 57) // 0 - 9
			{
				index = (int)stagename[i] - 48;
				break;
			}
		}

		string line;
		vector<string> datas;
		string data;

		stringstream readQueue(stringData[index]);

		while (getline(readQueue, line, '/')) datas.emplace_back(line);
		datas[1] = std::to_string(grade);

		for (int i = 0; i < datas.size(); i++)
		{
			data += datas[i];
			if (i != datas.size() - 1) {
				data += "/";
			}
		}
		stringData[index] = data;
		std::cout << "바뀐 성적 값 : " << stringData[index] << "\n";

		//바꾼 성적값을 데이터에 저장합니다
		std::ofstream stageSheet("Assets/StageData.txt");
		if (stageSheet.is_open()) {
			for (int i = 0; i < musicIndex; i++)
			{
				stageSheet << stringData[i];
				if (i != musicIndex - 1) { stageSheet << "\n"; } //eof
			}
			stageSheet.close();
			std::cout << ":: 성적 수정 완료! :: \n";
		}
	}
	void ChangeStageData()
	{
		string line;
		queue<string> datas;

		stringstream readQueue(stringData[passMusicIndex]);
		while (getline(readQueue, line, '/'))
		{
			datas.push(line);
		}
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
		ChangeGradeSprite();
		//std::cout << stageData.stageName << "\n" << stageData.Grade << "\n" << stageData.stage_back_sprite << "\n" << stageData.stage_sprite << "\n" << stageData.stage_back_frame_sprite << "\n";
	}
	void ChangeSprites();
private:
	string stringData[3];
	string stringInfoData[3]; 

	SDLGameObject* selectMusic;
	SDLGameObject* selectMusic_music;

	SDLGameObject* mainScore_Grade;

	SDLGameObject* back_stage1;
	SDLGameObject* back_stage_back1;
	SDLGameObject* back_stage_back2;
	SDLGameObject* back_stage_back_frame;
	SDLGameObject* back_stage_back_frame1;
	SDLGameObject* back_stage_back_frame2;

	stageData stageData;
	stageInfoData stageInfoData;

	int musicIndex = 0;
	int passMusicIndex = 0;

	void ChangeGradeSprite();
};
// ex) Stage0 / 0 / stage0_back_sprite / stage0_sprite / stage0_back_frame_sprite
		//스테이지, 점수, 뒷 배경 3형제 
		//점수 40미만 or 겜오버 -> F, 점수 40 -> B, 점수 75 -> A, 점수 90 -> A+
		//점수는 0, 1, 2, 3 순서 