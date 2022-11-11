#include <StageControl.h>

bool StageControl::SelectMusic()
{
	return false;
	//배경음도 바꾸기 
}
void StageControl::NextMusic()
{
	if (stringData->length()) return;
	++passMusicIndex;
	selectMusic_music->SetSpriteRow(passMusicIndex);
}
void StageControl::PreviousMusic()
{
	if (stringData->size() == 0) return;
	--passMusicIndex;
	selectMusic_music->SetSpriteRow(passMusicIndex);
}
void StageControl::Select()
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
void StageControl::OnOffPanel(bool onOff)
{
	selectMusic->SetActive(onOff);
	selectMusic_music->SetActive(onOff);
}