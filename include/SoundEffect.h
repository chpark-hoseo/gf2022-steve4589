#pragma once
#include <SDLGameObject.h>
#include <SDL2/SDL_mixer.h>

/*template <class T>*/
class SoundEffect : public SDLGameObject
{
public:
	SoundEffect(const LoaderParams* pParams);
	virtual void draw() {}
	virtual void update() {}
	virtual void clean() {}
	void SoundSFX(string soundName)
	{
		string songData = "./assets/SFX/" + soundName + ".wav";
		const char* SongdataPath = songData.c_str();

		soundEffect = Mix_LoadWAV(SongdataPath);
		Uint32 length = soundEffect->alen;
		if (soundEffect == NULL)
		{
			SDL_Log("SFX is NULL, need initialized SFX, use SoundSFX();  : %s\n", Mix_GetError());
			return;
		}
		Mix_PlayChannel(-1, soundEffect, 0);
		SetActive(false);
	}
private:
	virtual void OnDisable();

	Mix_Chunk* soundEffect;
};
