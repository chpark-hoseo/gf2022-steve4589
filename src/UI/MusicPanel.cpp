#include <MusicPanel.h>
#include <TextureManager.h>
#include <sstream>  

MusicPanel::MusicPanel(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void MusicPanel::draw()
{
	if (onOff == false) return;
	SDLGameObject::draw();
	SongInfo();
}

void MusicPanel::SongInfo()
{
	int index = 0;
	string line;
	stringstream readQueue(songName);

	while (getline(readQueue, line, '/')) //������ �����̸�
	{
		TextureManager::GetInstance()->drawFont(wsongName.c_str(), 815, 610 + textHeight * index);
		index++;
	}
	//w_char ==> ��Ƽ����Ʈ ��� (�ٸ���� ǥ������)
}