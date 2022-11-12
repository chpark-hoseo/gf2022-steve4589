#include <StageController.h>
#include <SDLGameObject.h>

StageController::StageController(SDLGameObject* getSelectMusic, SDLGameObject* getSelectMusicPanel, SDLGameObject* getBack_stage1,
	SDLGameObject* getBack_stage_back1, SDLGameObject* getBack_stage_back2, SDLGameObject* getStage_back_frame1,
	SDLGameObject* getStage_back_frame2, SDLGameObject* getStage_back_frame3)
{
	selectMusic = getSelectMusic;
	selectMusic_music = getSelectMusicPanel;

	back_stage1 = getBack_stage1;
	back_stage_back1 = getBack_stage_back1;
	back_stage_back2 = getBack_stage_back2;
	back_stage_back_frame = getStage_back_frame1;
	back_stage_back_frame1 = getStage_back_frame2;
	back_stage_back_frame2 = getStage_back_frame3;
}

bool StageController::SelectMusic()
{
	return false;
	//배경음 다시 시작 
}
void StageController::NextMusic()
{
	if (passMusicIndex == musicIndex - 1) return;

	++passMusicIndex;

	ChangeStageData();
	selectMusic_music->SetSpriteRow(passMusicIndex);
	//배경음 바꾸기
}
void StageController::PreviousMusic()
{
	if (passMusicIndex == 0) return;

	--passMusicIndex;

	ChangeStageData();
	selectMusic_music->SetSpriteRow(passMusicIndex);
	//배경음 바꾸기
}
void StageController::Select()
{
	/*
	const char* stagename = getStageName.c_str();
	int index = 0;

	for (int i = 0; i < strlen(stagename); i++)
	{
		if (stagename[i] >= 48 && stagename[i] <= 57) // 0 - 9
		{
			index = (int)stagename[i] - 48;
			break;
		}
	}
	selectMusic_music->SetSpriteRow(index);
	*/
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
void StageController::OnOffPanel(bool onOff)
{
	selectMusic->SetActive(onOff);
	selectMusic_music->SetActive(onOff);
}