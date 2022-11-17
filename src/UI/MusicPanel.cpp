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

	while (getline(readQueue, line, '/')) //막줄을 가수이름
	{
		TextureManager::GetInstance()->drawFont(wsongName.c_str(), 815, 610 + textHeight * index);
		index++;
	}
	//w_char ==> 멀티바이트 언어 (다른언어 표현가능)
}