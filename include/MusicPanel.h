#pragma once
#include <SDLGameObject.h>

class MusicPanel : public SDLGameObject //뮤직패널에 관련된 작업만 (노래 제목 등등..), 
{
public:
	MusicPanel(const LoaderParams* pParams);
	virtual void draw();
	virtual void update() {}
	virtual void clean() {}

	void ChangeSongInfo(std::string getName)
	{
		songName = getName;
		wsongName.assign(songName.begin(), songName.end()); //단점 : UTP-8 문자열(영어외 다른 언어들)은 불가 
	}
private:
	void SongInfo();

	string songName;
	std::wstring wsongName;

	int textHeight = 25;
};
