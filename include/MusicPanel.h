#pragma once
#include <SDLGameObject.h>

class MusicPanel : public SDLGameObject //�����гο� ���õ� �۾��� (�뷡 ���� ���..), 
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
