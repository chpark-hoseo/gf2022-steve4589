#include <StageController.h>
#include <SDLGameObject.h>
#include <State_Play.h>
#include <ScoreManager.h>
#include <NoteManager.h>
#include <MusicPanel.h>

StageController::StageController(MusicPanel* getSelectMusic, SDLGameObject* getSelectMusicPanel,
	SDLGameObject* getMainScore_Grade, SDLGameObject* getBack_stage1,
	SDLGameObject* getBack_stage_back1, SDLGameObject* getBack_stage_back2, SDLGameObject* getStage_back_frame1,
	SDLGameObject* getStage_back_frame2, SDLGameObject* getStage_back_frame3)
	: selectMusic(getSelectMusic), selectMusic_music(getSelectMusicPanel), mainScore_Grade(getMainScore_Grade),
	back_stage1(getBack_stage1), back_stage_back1(getBack_stage_back1), back_stage_back2(getBack_stage_back2),
	back_stage_back_frame(getStage_back_frame1), back_stage_back_frame1(getStage_back_frame2), back_stage_back_frame2(getStage_back_frame3),
	stageMusic(Game::GetInstance()->getBFX())
{
	StageDataInit();
}
void StageController::SelectMusic()
{
	State_Play::GetInstance()->StageStart(stageData.stageName);

	int allNoteNum = NoteManager::GetInstance()->GetAllNoteNum(); //ReadLineToTxt 작동하고 호출해야 가져옴
	ScoreManager::GetInstance()->SetScoreGrade(allNoteNum);
	//배경음 다시 시작 
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
void StageController::ChangeGradeSprite()
{
	mainScore_Grade->SetSpriteFrame(stageData.Grade);
}
void StageController::ChangeSongInfo(int i)
{
	selectMusic->ChangeSongInfo(stringInfoData[i]);
}
void StageController::ChangeBFX()
{
	string songData = "./assets/BFX/Stage" + to_string(passMusicIndex) + ".mp3";
	const char* SongdataPath = songData.c_str();
	//Mix_HaltMusic(); 멈추기

	stageMusic = Mix_LoadMUS(SongdataPath);
	if (stageMusic == NULL)
	{
		std::cout << "stageMusic" << passMusicIndex << "is NULL\n";
		return;
	}
	Mix_PlayMusic(stageMusic, 1); //Loop BGM
}
void StageController::ChangeSprites()
{
	back_stage1->SetSpriteId(stageData.stage_sprite);
	back_stage_back1->SetSpriteId(stageData.stage_back_sprite);
	back_stage_back2->SetSpriteId(stageData.stage_back_sprite);
	back_stage_back_frame->SetSpriteId(stageData.stage_back_frame_sprite);
	back_stage_back_frame1->SetSpriteId(stageData.stage_back_frame_sprite);
	back_stage_back_frame2->SetSpriteId(stageData.stage_back_frame_sprite);
}