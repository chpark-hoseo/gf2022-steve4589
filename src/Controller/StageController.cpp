#include <StageController.h>
#include <State_Play.h>
#include <ScoreManager.h>
#include <SoundEffect.h>

StageController::StageController(const LoaderParams* pParams, MusicPanel* getSelectMusic, SDLGameObject* getSelectMusicPanel,
	SDLGameObject* getMainScore_Grade, SDLGameObject* getBack_stage1,
	SDLGameObject* getBack_stage_back1, SDLGameObject* getBack_stage_back2, SDLGameObject* getStage_back_frame1,
	SDLGameObject* getStage_back_frame2, SDLGameObject* getStage_back_frame3)
	: selectMusic(getSelectMusic), selectMusic_music(getSelectMusicPanel), mainScore_Grade(getMainScore_Grade),
	back_stage1(getBack_stage1), back_stage_back1(getBack_stage_back1), back_stage_back2(getBack_stage_back2),
	back_stage_back_frame(getStage_back_frame1), back_stage_back_frame1(getStage_back_frame2), back_stage_back_frame2(getStage_back_frame3),
	stageMusic(Game::GetInstance()->getBFX()), SDLGameObject(pParams)
{
	StageDataInit();
}
void StageController::SelectMusic()
{
	if (stageData.stageName == "Stage0")
	{
		dynamic_cast<SoundEffect*>(State_Play::GetInstance()->GetObject(Vector2D(0, 0), "SoundEffect"))->SoundSFX("miss");

		std::cout << "Tutorial Music, can't play\n";
		return;
	}
	dynamic_cast<SoundEffect*>(State_Play::GetInstance()->GetObject(Vector2D(0, 0), "SoundEffect"))->SoundSFX("start");
	Mix_HaltMusic();

	State_Play::GetInstance()->FadeOutIn(0.01f, 0.01f);

	timer.WaitTime();
	musicStart = true;
	//키 작동 안되게 추가할것 + 시간나면 효과음도 
	State_Play::GetInstance()->SetKeyStop(true);
}

void StageController::StartMusic()
{
	if (musicStart == false) { return; }

	if (timer.getTimer() > 3.05f) {
		std::cout << "Music Start\n";

		State_Play::GetInstance()->StageStart(stageData.stageName);
		int allNoteNum = NoteManager::GetInstance()->GetAllNoteNum(); //ReadLineToTxt 작동하고 호출해야 가져옴
		ScoreManager::GetInstance()->SetScoreGrade(allNoteNum);
		musicStart = false;
	}
}
void StageController::NextMusic()
{
	if (passMusicIndex == musicIndex - 1) return;

	++passMusicIndex;

	ChangeStageData();
	ChangeBFX();
	ChangeSongInfo(passMusicIndex);
	selectMusic_music->SetSpriteRow(passMusicIndex);
	//배경음 upper
}
void StageController::PreviousMusic()
{
	if (passMusicIndex == 0) return;

	--passMusicIndex;

	ChangeStageData();
	ChangeBFX();
	ChangeSongInfo(passMusicIndex);
	selectMusic_music->SetSpriteRow(passMusicIndex);
	//배경음 lower
}
void StageController::ChangeGradeSprite(int getGrade)
{
	if (getGrade == NULL) { mainScore_Grade->SetSpriteFrame(stageData.Grade); }
	else { mainScore_Grade->SetSpriteFrame(getGrade); }
}
void StageController::ChangeSongInfo(int i) { selectMusic->ChangeSongInfo(stringInfoData[i]); }
void StageController::ChangeBFX()
{
	string songData = "./assets/BFX/Stage" + to_string(passMusicIndex) + ".mp3";
	const char* SongdataPath = songData.c_str();

	stageMusic = Mix_LoadMUS(SongdataPath);
	if (stageMusic == NULL)
	{
		std::cout << "stageMusic" << passMusicIndex << "is NULL\n";
		return;
	}
	Mix_PlayMusic(stageMusic, 0); //Loop BGM
}
void StageController::ChangeBackSprites()
{
	back_stage1->SetSpriteId(stageData.stage_sprite);
	back_stage_back1->SetSpriteId(stageData.stage_back_sprite);
	back_stage_back2->SetSpriteId(stageData.stage_back_sprite);
	back_stage_back_frame->SetSpriteId(stageData.stage_back_frame_sprite);
	back_stage_back_frame1->SetSpriteId(stageData.stage_back_frame_sprite);
	back_stage_back_frame2->SetSpriteId(stageData.stage_back_frame_sprite);
}
void StageController::GetPowerNotesPadPos()
{
	const char* dataPath = "Assets/PowerNotePadPosData.txt";
	std::ifstream dataSheet(dataPath, std::ifstream::in);

	string line;
	if (dataSheet.is_open())
	{
		std::cout << "::PowerNotePadPosData::\n";
		int Index = 0;
		while (!dataSheet.eof())
		{
			getline(dataSheet, line);
			stringPowerNotePadPosData[Index] = line;
			std::cout << line.c_str() << "\n";
			Index++;
		}
		dataSheet.close();
	}
}

vector<Vector2D> StageController::SetPowerNotesPadPos()
{
	string line;
	queue<string> padsDatas;
	queue<string> padDatas;

	stringstream readQueue(stringPowerNotePadPosData[passMusicIndex]);
	while (getline(readQueue, line, '/'))
	{
		padsDatas.push(line);
	}

	vector<Vector2D> pads;
	string pad;

	float x = 0;
	float y = 0;

	while (padsDatas.size() != 0)
	{
		pad = padsDatas.front();
		padsDatas.pop();
		std::cout << pad << "\n";
		int index = 0;
		stringstream readQueue(pad);
		while (getline(readQueue, line, ','))
		{
			//x, y값 가져오기 (2번 작동)
			if (index == 0) { x = stof(line); }
			else { y = stof(line); } //가독성 죄송합니다
			index++;
		}
		Vector2D padPos = Vector2D(x, y);
		pads.emplace_back(padPos);
	}
	return pads;
}