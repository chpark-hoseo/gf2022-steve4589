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

	while (getline(readQueue, line, '/')) //���� => �����̸�
	{
		wsongName.assign(line.begin(), line.end()); //���� : UTP-8 ���ڿ�(����� �ٸ� ����)�� �Ұ� 
		TextureManager::GetInstance()->drawFont(wsongName.c_str(), 815, 615 + textHeight * index);
		index++;
	}
	//w_char ==> ��Ƽ����Ʈ ��� (�ٸ���� ǥ������)
}