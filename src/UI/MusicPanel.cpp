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

	while (getline(readQueue, line, '/')) //막줄 => 가수이름
	{
		wsongName.assign(line.begin(), line.end()); //단점 : UTP-8 문자열(영어외 다른 언어들)은 불가 
		TextureManager::GetInstance()->drawFont(wsongName.c_str(), 815, 615 + textHeight * index);
		index++;
	}
	//w_char ==> 멀티바이트 언어 (다른언어 표현가능)
}