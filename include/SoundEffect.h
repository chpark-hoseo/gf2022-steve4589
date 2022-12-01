#pragma once
#include <SDLGameObject.h>
#include <SDL2/SDL_mixer.h>

/*template <class T>*/
class SoundEffect : public SDLGameObject //SFX는 빈 게임 오브젝트에서 호출합니다 (중첩해서 나오게 하기 위해)
{
public:
	explicit SoundEffect(const LoaderParams* pParams);
	virtual void draw() {}
	virtual void update() {}
	virtual void clean() {}
	void SoundSFX(string soundName)
	{
		string songData = "./assets/SFX/" + soundName + ".wav";
		const char* SongdataPath = songData.c_str();

		soundEffect = Mix_LoadWAV(SongdataPath);
		if (soundEffect == NULL)
		{
			SDL_Log("SFX is NULL, need initialized SFX, use SoundSFX();  : %s\n", Mix_GetError());
			return;
		}

		Uint32 length = soundEffect->alen; //wav 파일 길이
		
		Mix_PlayChannel(-1, soundEffect, 0);
		SetActive(false); //바로 비활성화 합니다
	}
private:
	virtual void OnDisable();

	Mix_Chunk* soundEffect;
};
