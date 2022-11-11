#pragma once
#include <SDLGameObject.h>
#include<sstream>
#include <fstream> 

enum Stage
{
	Stage0 = 0,
	State1,
	State2
};

class StageControl 
{
public :
	void OnOffPanel(bool onOff);
	bool SelectMusic(); //����, ���� �ٲٱ�, 

	void Select();
	void NextMusic();
	void PreviousMusic();

	void StageDataInit()
	{
		const char* dataPath = "Assets/StageData.txt";
		std::ifstream stageSheet(dataPath, std::ifstream::in);

		string line;
		if (stageSheet.is_open())
		{
			int index = 0;
			while (!stageSheet.eof())
			{
				getline(stageSheet, line); //getline(desline, buffer, '/');
				stringData[index] = line;
				std::cout << "Stage " << index << " Data ==> " << line << "\n";

				index++;
			}
			stageSheet.close();
		}
		// ex) Stage0 / 0 / stage0_back_sprite / stage0_sprite / stage0_back_frame_sprite
		//��������, ����, �� ��� 3���� 
		//���� 40�̸� or �׿��� -> F, ���� 40 -> B, ���� 75 -> A, ���� 90 -> A+
		//������ 0, 1, 2, 3 ���� 
	}
protected:
	StageControl(SDLGameObject * getSelectMusic, SDLGameObject * getSelectMusicPanel)
	{
		selectMusic = getSelectMusic;
		selectMusic_music = getSelectMusicPanel;
	};

	string stringData[3];
	SDLGameObject* selectMusic;
	SDLGameObject* selectMusic_music;

	int passMusicIndex = 0;
};