#pragma once
#include <SDLGameObject.h>

class MusicPanel : public SDLGameObject //뮤직패널에 관련된 작업만 (노래 제목 등등..), 
{
public:
	MusicPanel(const LoaderParams* pParams);
	virtual void draw();
	virtual void update() {}
	virtual void clean() {}

	void ChangeSongInfo(std::string getName) { songName = getName; }
private:
	void SongInfo();

	string songName;
	std::wstring wsongName;

	int textHeight = 30;
};
