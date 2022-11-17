#pragma once
#include <SDLGameObject.h>

class MusicPanel : public SDLGameObject //�����гο� ���õ� �۾��� (�뷡 ���� ���..), 
{
public:
	MusicPanel(const LoaderParams* pParams);
	virtual void draw();
	virtual void update() {}
	virtual void clean() {}

	void ChangeSongInfo(std::string getName)
	{
		songName = getName;
		wsongName.assign(songName.begin(), songName.end()); //���� : UTP-8 ���ڿ�(����� �ٸ� ����)�� �Ұ� 
	}
private:
	void SongInfo();

	string songName;
	std::wstring wsongName;

	int textHeight = 25;
};
