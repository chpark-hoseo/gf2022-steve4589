#pragma once
#include<sstream>
#include <fstream> 
#include <string>
#include <queue>
#include <iostream>
#include <SDL2/SDL_mixer.h>

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

class StageController //�������� ������ / �̹��� ���� �� ���� �� ���� 
{
public:
	StageController(MusicPanel* getSelectMusic, SDLGameObject* getSelectMusicPanel,
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
	void SelectMusic(); //����, ���� �ٲٱ�, 
	/*
	Stage0/0/stage0_back_sprite/stage0_sprite/stage0_back_frame_sprite
	Stage1/3/stage1_back_sprite/stage1_sprite/stage1_back_frame_sprite
	Stage2/4/stage2_back_sprite/stage2_sprite/stage2_back_frame_sprite
	*/
	void SaveGrade(string stageName, int grade) //���� �߰��� �ٲ� �� ���⿡, ��ĥ �κи� �����ϰ� ó������ �ٽ� �����մϴ�
	{
		//������ ������ �ش� �������� ��ȣ�� �����ɴϴ� 
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
		datas[1] = std::to_string(grade); //���� �ٲ�ġ�� 

		for (int i = 0; i < datas.size(); i++)
		{
			data += datas[i];
			if (i != datas.size() - 1) {
				data += "/";
			}
		}
		if (stringData[index] > data) //�Ź� ���� ���� ���� (�ְ����� �Ѿ�� ����)
		{
			std::cout << "����� ����.. : " << "\n";
			return;
		}

		stringData[index] = data;
		std::cout << "�ٲ� ���� �� : " << stringData[index] << "\n";

		//�ٲ� �������� �����Ϳ� �����մϴ�
		std::ofstream stageSheet("Assets/StageData.txt");
		if (stageSheet.is_open()) {
			for (int i = 0; i < musicIndex; i++)
			{
				stageSheet << stringData[i];
				if (i != musicIndex - 1) { stageSheet << "\n"; } //make eof
			}
			stageSheet.close();
			std::cout << ":: ���� ���� �Ϸ�! :: \n";
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
	}
	void ChangeSprites();
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

	stageData stageData;
	stageInfoData stageInfoData;

	int musicIndex = 0;
	int passMusicIndex = 0;

	void ChangeGradeSprite();
};
// ex) Stage0 / 0 / stage0_back_sprite / stage0_sprite / stage0_back_frame_sprite
		//��������, ����, �� ��� 3���� 
		//���� 40�̸� or �׿��� -> F, ���� 40 -> B, ���� 75 -> A, ���� 90 -> A+
		//������ 0, 1, 2, 3 ���� 
/*
string���� wstring���� ��ȯ�ϴ� ����� =>

�⺻ ���ڿ��� UTF-8�� ���ڵ� �� ��� �۵����� �ʽ��ϴ� 
std::wstring widestr = std::wstring(str.begin(), str.end());
const wchar_t* widecstr = widestr.c_str();

::������ ����:: /
#include <atlconv.h>
...
std::string str = "Hello, world!";
CA2W pszWide(str.c_str());
loadU(pszWide);

::Linux / Unix
mbstowcs () �� wcstombs ()
*/