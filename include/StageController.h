#pragma once
#include<sstream>
#include <fstream> 
#include <string>
#include <queue>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <Timer.h>
#include <SDLGameObject.h>

using namespace std;
class SDLGameObject;
class MusicPanel;

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

class StageController : public SDLGameObject //스테이지 데이터 / 이미지 저장 및 관리 및 변경 
{
public:
	StageController(const LoaderParams* pParams, MusicPanel* getSelectMusic, SDLGameObject* getSelectMusicPanel,
		SDLGameObject* getMainScore_Grade, SDLGameObject* getBack_stage1,
		SDLGameObject* getBack_stage_back1, SDLGameObject* getBack_stage_back2, SDLGameObject* getStage_back_frame_sprite,
		SDLGameObject* getStage_back_frame_sprite1, SDLGameObject* getStage_back_frame_sprite2);

	virtual void draw() {}
	virtual void update() 
	{
		timer.StartTimer(); 
		StartMusic();
	}

	virtual void clean() {}

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
				std::cout << line.c_str() << "\n";
				musicIndex++;
			}
			stageSheet.close();
		}
		dataPath = "Assets/StageInfoData.txt";
		std::ifstream stageSheet1(dataPath, std::ifstream::in);

		if (stageSheet1.is_open())
		{
			int index = 0;
			while (!stageSheet1.eof())
			{
				getline(stageSheet1, line);
				stringInfoData[index] = line;
				index++;
			}
			stageSheet1.close();
		}
		ChangeSongInfo(0);
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
	/* stageData 양식
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
		datas[1] = std::to_string(grade); //성적 바꿔치기 

		for (int i = 0; i < datas.size(); i++)
		{
			data += datas[i];
			if (i != datas.size() - 1) {
				data += "/";
			}
		}
		if (stringData[index] > data) //매번 점수 갱신 방지 (최고점수 넘어야 가능)
		{
			std::cout << "재수강 실패.. : " << "\n";
			return;
		}

		stringData[index] = data;
		std::cout << "바뀐 성적 값 : " << stringData[index] << "\n";

		//바꾼 성적값을 데이터에 저장합니다
		std::ofstream stageSheet("Assets/StageData.txt");
		if (stageSheet.is_open()) {
			for (int i = 0; i < musicIndex; i++)
			{
				stageSheet << stringData[i];
				if (i != musicIndex - 1) { stageSheet << "\n"; } //make eof
			}
			stageSheet.close();
			std::cout << ":: 성적 수정 완료! :: \n";
		}
		ChangeGradeSprite(grade);
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

		ChangeBackSprites();
		ChangeGradeSprite(NULL);
	}
	void ChangeBackSprites();
	void ChangeGradeSprite(int getGrade);
	void ChangeSongInfo(int i);
	void ChangeBFX();
private:
	string stringData[3];
	string stringInfoData[3];

	Mix_Music* stageMusic;

	MusicPanel* selectMusic;
	SDLGameObject* selectMusic_music;

	SDLGameObject* mainScore_Grade;

	SDLGameObject* back_stage1;
	SDLGameObject* back_stage_back1;
	SDLGameObject* back_stage_back2;
	SDLGameObject* back_stage_back_frame;
	SDLGameObject* back_stage_back_frame1;
	SDLGameObject* back_stage_back_frame2;

	Timer timer;

	stageData stageData;
	stageInfoData stageInfoData;

	int musicIndex = 0;
	int passMusicIndex = 0;

	bool musicStart = false;

	void StartMusic();
};
// ex) Stage0 / 0 / stage0_back_sprite / stage0_sprite / stage0_back_frame_sprite
		//스테이지, 점수, 뒷 배경 3형제 
		//점수 40미만 or 겜오버 -> F, 점수 40 -> B, 점수 75 -> A, 점수 90 -> A+
		//점수는 0, 1, 2, 3 순서 
/*
string에서 wstring으로 변환하는 방법들 =>

기본 문자열이 UTF-8로 인코딩 된 경우 작동하지 않습니다 
std::wstring widestr = std::wstring(str.begin(), str.end());
const wchar_t* widecstr = widestr.c_str();

::윈도우 전용:: /
#include <atlconv.h>
...
std::string str = "Hello, world!";
CA2W pszWide(str.c_str());
loadU(pszWide);

::Linux / Unix
mbstowcs () 및 wcstombs ()
*/